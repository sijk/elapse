#include <QCoreApplication>
#include <QMetaClassInfo>
#include <QJsonObject>
#include <QPluginLoader>
#include <QStandardItemModel>
#include <QxtLogger>
#include "plugin.h"
#include "pluginfilterproxymodel.h"
#include "pluginmanager_p.h"
#include "pluginmanager.h"
#include "ui_pluginmanager.h"


template<class ElementType>
void loadElement(ElementType &element, PluginManager::ClassInfo info);


namespace {
const QString pathSetting("elements/%1/plugin-path");
const QString classSetting("elements/%1/class-name");
}


struct PluginManager::ClassInfo {
    QString pluginPath;
    QString className;
};


/*!
 * Construct a PluginManager as a child of the given \a parent.
 *
 * The default plugin search path is set to the "plugins" subdirectory of the
 * directory containing the application executable.
 */
PluginManager::PluginManager(QWidget *parent) :
    QDialog(parent),
    model(new QStandardItemModel(this)),
    ui(new Ui::PluginManager)
{
    ui->setupUi(this);
    QString defaultPath(QDir(qApp->applicationDirPath()).absoluteFilePath("plugins"));
    setSearchPath(QSettings().value("plugins-path", defaultPath).toString());
    connect(this, SIGNAL(accepted()), SLOT(loadSelectedElements()));
}

/*!
 * Destroy this PluginManager.
 */
PluginManager::~PluginManager()
{
    // Delete PluginFilterProxyModels
    delete ui->treeSource->model();
    delete ui->treeDecoderEeg->model();
    delete ui->treeDecoderVideo->model();
    delete ui->treeDecoderImu->model();
    delete ui->treeFeatEeg->model();
    delete ui->treeFeatVideo->model();
    delete ui->treeFeatImu->model();
    delete ui->treeClassifier->model();

    delete ui;
}

/*!
 * \page pluginmanager-model PluginManager Data Model
 *
 * This page describes the structure of the PluginManager's internal data model.
 *
 * Suppose that we have two plugins, \c FooPlugin and \c BarPlugin. They each
 * provide several classes implementing DataSource and SampleDecoder element
 * types. This hypothetical situation is illustrated below.
 *
 * @startuml{pluginmanager-model-classes.png}
 *
 * package libfooplugin.so {
 *     FooPlugin o-- FooTcpDataSource
 *     FooPlugin o-- FooUdpDataSource
 *     FooPlugin o-- FooEegDecoder
 * }
 * package libbarplugin.so {
 *     BarPlugin o-- BarEegDecoder
 *     BarPlugin o-- BarVideoDecoder
 * }
 *
 * BarEegDecoder    --|> SampleDecoder
 * BarVideoDecoder  --|> SampleDecoder
 * FooEegDecoder    --|> SampleDecoder
 * FooTcpDataSource --|> DataSource
 * FooUdpDataSource --|> DataSource
 *
 * FooEegDecoder : SampleType : "EEG"
 * BarEegDecoder : SampleType : "EEG"
 * BarVideoDecoder : SampleType : "VIDEO"
 *
 * @enduml
 *
 * Given these plugins, the structure of the PluginManager's data model would be
 * as follows:
 *
 * \code
 * [Root]
 *      DataSource
 *          FooPlugin
 *              FooTcpDataSource
 *              FooUdpDataSource
 *
 *      SampleDecoder
 *          FooPlugin
 *              FooEegDecoder
 *          BarPlugin
 *              BarEegDecoder
 *              BarVideoDecoder
 * \endcode
 *
 * If a PluginFilterProxyModel was defined with the arguments
 * \c elementType = "SampleDecoder" and \c sampleType = "EEG", then the filtered
 * model would have the following structure:
 *
 * \code
 * SampleDecoder
 *      FooPlugin
 *          FooEegDecoder
 *      BarPlugin
 *          BarEegDecoder
 * \endcode
 *
 * That is, it would include all of the classes implementing \c SampleDecoder
 * which apply to the \c sampleType "EEG".
 */

/*!
 * \property PluginManager::searchPath
 * The directory in which to search for plugins.
 */

/*!
 * Set the plugin search path to \a newPath and scan that directory for plugins.
 */
void PluginManager::setSearchPath(QDir newPath)
{
    qxtLog->info("Searching for plugins in", newPath.absolutePath());

    if (newPath == path) {
        qxtLog->debug("PluginManager search path was set to the current value. "
                      "Not doing anything...");
        return;
    }

    path = newPath;
    model->clear();
    auto rootItem = model->invisibleRootItem();

    foreach (QFileInfo file, newPath.entryInfoList(QDir::Files)) {
        QPluginLoader loader(file.absoluteFilePath());
        QObject *plugin = loader.instance();
        auto factory = static_cast<Plugin*>(plugin);

        if (factory) {
            QString pluginName = loader.metaData()["className"].toString();

            foreach (const QMetaObject &obj, factory->classes()) {
                QString elementName = baseClass(&obj)->className();

                // Find or create element item
                auto elementItem = childWithText(rootItem, elementName);
                if (!elementItem) {
                    elementItem = createElementItem(elementName);
                    rootItem->appendRow(elementItem);
                }

                // Find or create plugin item
                auto pluginItem = childWithText(elementItem, pluginName);
                if (!pluginItem) {
                    pluginItem = createPluginItem(pluginName, file);
                    elementItem->appendRow(pluginItem);
                }

                // Create class item
                auto classItem = createClassItem(obj);
                pluginItem->appendRow(classItem);
            }
        } else {
            qxtLog->error(loader.errorString());
        }

        loader.unload();
    }

    attachViews();
}

/*!
 * Show the Pluginmanager window, allowing the user to select the set of
 * elements they would like to load from plugins.
 */
void PluginManager::loadPlugins()
{
    show();
}

/*!
 * Called when the PluginManager window is closed with OK. Create a new
 * ElementSet and load the selected classes from plugins to populate it.
 */
void PluginManager::loadSelectedElements()
{
    qxtLog->info("Loading the selected set of elements");
    if (doLoadElements(&PluginManager::loadElementSetFromSelection))
        saveSelectedElements();
}

/*!
 * Create a new element set and populate it with the classes that are saved in
 * the settings file.
 *
 * \return \c true if either all necessary plugins were loaded successfully or
 * if there were no elements saved in the settings file.
 * Returns \c false if there was an error loading plugins.
 */
bool PluginManager::loadPluginsFromSettings()
{
    if (!QSettings().childGroups().contains("elements")) {
        qxtLog->debug("No saved elements to load");
        return true;
    }

    qxtLog->info("Loading the saved set of elements");
    bool success = doLoadElements(&PluginManager::loadElementSetFromSettings);

    if (success)
        selectSavedElements();

    return success;
}

/*!
 * Load elements with the given \a loader and check whether it succeeded.
 * If so, emit the pluginsLoaded() signal.
 */
bool PluginManager::doLoadElements(ElementLoader loader)
{
    auto elements = ElementSetPtr::create();

    // Populate the ElementSet
    (this->*loader)(elements);

    if (!elements->dataSource ||
        !elements->sampleDecoders[EEG] ||
        !elements->sampleDecoders[VIDEO] ||
        !elements->sampleDecoders[IMU] ||
        !elements->featureExtractors[EEG] ||
        !elements->featureExtractors[VIDEO] ||
        !elements->featureExtractors[IMU] ||
        !elements->classifier) {
        qxtLog->warning("Failed to load all elements from plugins.");
        return false;
    }

    qxtLog->info("Successfully loaded all elements from plugins.");
    emit pluginsLoaded(elements);
    return true;
}

/*!
 * \fn PluginManager::pluginsLoaded(ElementSetPtr)
 * Emitted when an ElementSet has been loaded.
 *
 * The lifetime of the created ElementSet is managed automatically by virtue of
 * using a QSharedPointer to refer to it. As soon as the last reference to the
 * ElementSet is dropped it will be deleted automatically.
 */

/*!
 * Populate the given \a elements with the classes selected in the tree-views.
 *
 * \see loadElement()
 */
void PluginManager::loadElementSetFromSelection(ElementSetPtr elements)
{
    loadElement(elements->dataSource,               getSelectedElement(ui->treeSource));
    loadElement(elements->sampleDecoders[EEG],      getSelectedElement(ui->treeDecoderEeg));
    loadElement(elements->sampleDecoders[VIDEO],    getSelectedElement(ui->treeDecoderVideo));
    loadElement(elements->sampleDecoders[IMU],      getSelectedElement(ui->treeDecoderImu));
    loadElement(elements->featureExtractors[EEG],   getSelectedElement(ui->treeFeatEeg));
    loadElement(elements->featureExtractors[VIDEO], getSelectedElement(ui->treeFeatVideo));
    loadElement(elements->featureExtractors[IMU],   getSelectedElement(ui->treeFeatImu));
    loadElement(elements->classifier,               getSelectedElement(ui->treeClassifier));
}

/*!
 * Populate the given \a elements with the classes saved in the settings file.
 *
 * \see loadElement()
 */
void PluginManager::loadElementSetFromSettings(ElementSetPtr elements)
{
    loadElement(elements->dataSource,               getSavedElement("data-source"));
    loadElement(elements->sampleDecoders[EEG],      getSavedElement("eeg-decoder"));
    loadElement(elements->sampleDecoders[VIDEO],    getSavedElement("video-decoder"));
    loadElement(elements->sampleDecoders[IMU],      getSavedElement("imu-decoder"));
    loadElement(elements->featureExtractors[EEG],   getSavedElement("eeg-featex"));
    loadElement(elements->featureExtractors[VIDEO], getSavedElement("video-featex"));
    loadElement(elements->featureExtractors[IMU],   getSavedElement("imu-featex"));
    loadElement(elements->classifier,               getSavedElement("classifier"));
}

/*!
 * Load the plugin from \a info.pluginPath and instantiate an object of class
 * \a info.className. If the plugin cannot be loaded, the class cannot be
 * instantiated, or casting the instance to the requested ElementType fails,
 * \a element will be \c NULL. Otherwise \a element will hold the newly-created
 * element.
 */
template<class ElementType>
void loadElement(ElementType &element, PluginManager::ClassInfo info)
{
    Q_STATIC_ASSERT(std::is_pointer<ElementType>::value);

    element = nullptr;

    if (info.pluginPath.isEmpty() || info.className.isEmpty())
        return;

    QPluginLoader loader(info.pluginPath);
    Plugin *plugin = static_cast<Plugin*>(loader.instance());

    if (!plugin) {
        qxtLog->debug("Could not load plugin", info.pluginPath);
        return;
    }

    foreach (const QMetaObject &obj, plugin->classes()) {
        if (obj.className() == info.className) {
            QObject *instance = obj.newInstance();
            element = qobject_cast<ElementType>(instance);
            if (instance && !element)
                delete instance;
            break;
        }
    }

    qxtLog->trace(element ? "Loaded" : "Failed to load", info.className,
                  "from", QFileInfo(info.pluginPath).fileName());
}

/*!
 * \return the details of the class that is selected in the given \a tree view.
 */
PluginManager::ClassInfo PluginManager::getSelectedElement(QTreeView *tree)
{
    ClassInfo info;

    QModelIndexList idxs = tree->selectionModel()->selection().indexes();
    Q_ASSERT(idxs.size() == 1);
    QModelIndex index = idxs.at(0);

    info.className = index.data().toString();
    info.pluginPath = index.parent().data(FILEPATH_ROLE).toString();

    return info;
}

/*!
 * \return the details of the saved class with the given \c elementName.
 */
PluginManager::ClassInfo PluginManager::getSavedElement(QString elementName)
{
    ClassInfo info;

    QSettings settings;
    info.pluginPath = settings.value(pathSetting.arg(elementName)).toString();
    info.className = settings.value(classSetting.arg(elementName)).toString();

    return info;
}

/*!
 * Inspect the tree views and save the details of the selected elements to
 * the settings file.
 */
void PluginManager::saveSelectedElements()
{
    QSettings settings;

    auto saveElement = [&](QTreeView *tree, const QString &name) {
        ClassInfo info = getSelectedElement(tree);
        settings.setValue(pathSetting.arg(name), info.pluginPath);
        settings.setValue(classSetting.arg(name), info.className);
    };

    saveElement(ui->treeSource,       "data-source");
    saveElement(ui->treeDecoderEeg,   "eeg-decoder");
    saveElement(ui->treeDecoderVideo, "video-decoder");
    saveElement(ui->treeDecoderImu,   "imu-decoder");
    saveElement(ui->treeFeatEeg,      "eeg-featex");
    saveElement(ui->treeFeatVideo,    "video-featex");
    saveElement(ui->treeFeatImu,      "imu-featex");
    saveElement(ui->treeClassifier,   "classifier");

    qxtLog->info("Saved current element selection");
}

/*!
 * Set the selections in the tree views to match the elements that are saved
 * in the settings file.
 */
void PluginManager::selectSavedElements()
{
    QSettings settings;

    auto selectSavedElement = [&](QTreeView *tree, const QString &name) {
        QAbstractItemModel *model = tree->model();
        QItemSelectionModel *selection = tree->selectionModel();
        PluginManager::ClassInfo info;

        info.pluginPath = settings.value(pathSetting.arg(name)).toString();
        info.className = settings.value(classSetting.arg(name)).toString();

        // Search the model for the item that matches the saved plugin/class
        // names and select it.

        auto element = model->index(0,0);
        for (int i = 0; i < model->rowCount(element); i++) {
            auto plugin = model->index(i, 0, element);

            if (model->data(plugin, FILEPATH_ROLE) != info.pluginPath)
                continue;

            for (int j = 0; j < model->rowCount(plugin); j++) {
                auto classIndex = model->index(j, 0, plugin);

                if (model->data(classIndex).toString() == info.className) {
                    selection->select(classIndex, QItemSelectionModel::SelectCurrent);
                    return;
                }
            }
        }
    };

    selectSavedElement(ui->treeSource,       "data-source");
    selectSavedElement(ui->treeDecoderEeg,   "eeg-decoder");
    selectSavedElement(ui->treeDecoderVideo, "video-decoder");
    selectSavedElement(ui->treeDecoderImu,   "imu-decoder");
    selectSavedElement(ui->treeFeatEeg,      "eeg-featex");
    selectSavedElement(ui->treeFeatVideo,    "video-featex");
    selectSavedElement(ui->treeFeatImu,      "imu-featex");
    selectSavedElement(ui->treeClassifier,   "classifier");
}

/*!
 * Helper function for building the internal plugin model.
 * \return a QStandardItem representing an element type with the given \a name.
 */
QStandardItem *PluginManager::createElementItem(const QString &name)
{
    auto item = new QStandardItem(name);

    QFont font;
    font.setBold(true);
    item->setFont(font);

    item->setSelectable(false);
    item->setEditable(false);

    return item;
}

/*!
 * Helper function for building the internal plugin model.
 * \return a QStandardItem representing a plugin with the given \a name at the
 * given \a file path.
 *
 * The absolute path to the plugin file is stored as item data with the role
 * FILEPATH_ROLE.
 */
QStandardItem *PluginManager::createPluginItem(const QString &name,
                                               const QFileInfo &file)
{
    auto item = new QStandardItem(name);

    item->setData(file.absoluteFilePath(), FILEPATH_ROLE);

    QFont font;
    font.setItalic(true);
    item->setFont(font);

    item->setSelectable(false);
    item->setEditable(false);

    return item;
}

/*!
 * Helper function for building the internal plugin model.
 * \return a QStandardItem representing a class provided by a plugin.
 *
 * If the class provides a Q_CLASSINFO entry with the key "SampleType", the
 * value of this entry is stored as item data with the role SAMPLETYPE_ROLE.
 */
QStandardItem *PluginManager::createClassItem(const QMetaObject &obj)
{
    auto item = new QStandardItem(obj.className());

    int typeIdx = obj.indexOfClassInfo("SampleType");
    if (typeIdx >= 0) {
        QString sampleType = obj.classInfo(typeIdx).value();
        item->setData(sampleType, SAMPLETYPE_ROLE);
    }

    item->setEditable(false);

    return item;
}

/*!
 * \return the first child of the given \a item with text \a name, or NULL.
 */
QStandardItem *PluginManager::childWithText(const QStandardItem *item,
                                            const QString &name)
{
    for (int i = 0; i < item->rowCount(); i++) {
        auto child = item->child(i);
        if (child->text() == name)
            return child;
    }
    return nullptr;
}

/*!
 * \return the base class of \a obj just before QObject.
 *
 * For instance, if there was an inheritance hierarchy of QObject <- A <- B <- C
 * then baseClass(C) == baseClass(B) == baseClass(A) == A.
 */
const QMetaObject *PluginManager::baseClass(const QMetaObject *obj)
{
    const QMetaObject *super = obj->superClass();
    if (super && super != &QObject::staticMetaObject)
        return baseClass(super);
    return obj;
}

/*!
 * Connect the QTreeViews in the PluginManager window to the corresponding parts
 * of the internal plugin model.
 */
void PluginManager::attachViews()
{
    auto setupTreeView = [this](QTreeView *tree, const QString &elementType,
                                const QString &sampleType = QString()) {
        // Filter model by element type and sample type
        auto filteredModel = new PluginFilterProxyModel(elementType, sampleType);
        filteredModel->setSourceModel(model);

        // Connect filtered model to view
        tree->setModel(filteredModel);
        // TODO: do this root item selection inside the proxy model
        tree->setRootIndex(tree->model()->index(0,0));
        tree->expandAll();

        // Select the first class by default
        tree->selectionModel()->select(tree->rootIndex().child(0,0).child(0,0),
                                       QItemSelectionModel::SelectCurrent);

        // Ensure that something is always selected from then on
        connect(tree->selectionModel(), &QItemSelectionModel::selectionChanged,
            [=](const QItemSelection &current, const QItemSelection &prev){
                if (current.indexes().isEmpty() && !prev.indexes().isEmpty())
                    tree->selectionModel()->select(prev, QItemSelectionModel::SelectCurrent);
            });
    };

    setupTreeView(ui->treeSource,       "DataSource");
    setupTreeView(ui->treeDecoderEeg,   "SampleDecoder",    "EEG");
    setupTreeView(ui->treeDecoderVideo, "SampleDecoder",    "VIDEO");
    setupTreeView(ui->treeDecoderImu,   "SampleDecoder",    "IMU");
    setupTreeView(ui->treeFeatEeg,      "FeatureExtractor", "EEG");
    setupTreeView(ui->treeFeatVideo,    "FeatureExtractor", "VIDEO");
    setupTreeView(ui->treeFeatImu,      "FeatureExtractor", "IMU");
    setupTreeView(ui->treeClassifier,   "Classifier");
}
