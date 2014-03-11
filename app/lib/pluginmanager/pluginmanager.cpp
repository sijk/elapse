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
 * FooEegDecoder : SignalType : "EEG"
 * BarEegDecoder : SignalType : "EEG"
 * BarVideoDecoder : SignalType : "VIDEO"
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
 * \c elementType = "SampleDecoder" and \c signalType = "EEG", then the filtered
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
 * which apply to the \c signalType "EEG".
 */


class PluginManagerPrivate
{
public:
    PluginManagerPrivate(PluginManager *q);
    ~PluginManagerPrivate();

    struct ClassInfo;
    typedef void (PluginManagerPrivate::*ElementLoader)(ElementSetPtr);

    void setSearchPath(QDir newPath);

    static QStandardItem *createElementTypeItem(const QString &name);
    static QStandardItem *createPluginItem(const QString &name,
                                           const QFileInfo &file);
    static QStandardItem *createElementItem(const QMetaObject &obj);
    static const QMetaObject *baseClass(const QMetaObject *obj);
    static QStandardItem *childWithText(const QStandardItem *item,
                                        const QString &name);
    void attachViews();

    ElementSetPtr loadSelectedElements();
    ElementSetPtr loadSavedElements();
    ElementSetPtr doLoadElements(ElementLoader loader);

    void loadElementSetFromSelection(ElementSetPtr elements);
    void loadElementSetFromSettings(ElementSetPtr elements);

    template<class ElementType>
    static void loadElement(ElementType &element, ClassInfo info);

    static ClassInfo getSelectedElement(QTreeView *tree);
    static ClassInfo getSavedElement(QString elementName);

    void saveSelectedElements();
    void selectSavedElements();

    Ui::PluginManager *ui;
    QDir path;
    QStandardItemModel *model;
    static const QString pathSetting;
    static const QString classSetting;
};

struct PluginManagerPrivate::ClassInfo {
    QString pluginPath;
    QString className;
};

const QString PluginManagerPrivate::pathSetting("elements/%1/plugin-path");
const QString PluginManagerPrivate::classSetting("elements/%1/class-name");

/*!
 * Create the private data for the given PluginManager. Set the search path to
 * the default and populate the plugin model from that path.
 */
PluginManagerPrivate::PluginManagerPrivate(PluginManager *q) :
    ui(new Ui::PluginManager),
    model(new QStandardItemModel)
{
    ui->setupUi(q);

    QString defaultPath(QDir(qApp->applicationDirPath()).absoluteFilePath("plugins"));
    setSearchPath(QSettings().value("plugins-path", defaultPath).toString());
}

PluginManagerPrivate::~PluginManagerPrivate()
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

    delete model;
    delete ui;
}

/*!
 * \see PluginManager::setSearchPath()
 */
void PluginManagerPrivate::setSearchPath(QDir newPath)
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
                    elementItem = createElementTypeItem(elementName);
                    rootItem->appendRow(elementItem);
                }

                // Find or create plugin item
                auto pluginItem = childWithText(elementItem, pluginName);
                if (!pluginItem) {
                    pluginItem = createPluginItem(pluginName, file);
                    elementItem->appendRow(pluginItem);
                }

                // Create class item
                auto classItem = createElementItem(obj);
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
 * Helper function for building the internal plugin model.
 * \return a QStandardItem representing an element type with the given \a name.
 */
QStandardItem *PluginManagerPrivate::createElementTypeItem(const QString &name)
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
QStandardItem *PluginManagerPrivate::createPluginItem(const QString &name,
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
 * \return a QStandardItem representing an element class provided by a plugin.
 *
 * If the class provides a Q_CLASSINFO entry with the key "SignalType", the
 * value of this entry is stored as item data with the role SIGNALTYPE_ROLE.
 */
QStandardItem *PluginManagerPrivate::createElementItem(const QMetaObject &obj)
{
    auto item = new QStandardItem(obj.className());

    int typeIdx = obj.indexOfClassInfo("SignalType");
    if (typeIdx >= 0) {
        const char *signalType = obj.classInfo(typeIdx).value();
        item->setData(Signal::fromString(signalType), SIGNALTYPE_ROLE);
    }

    item->setEditable(false);

    return item;
}

/*!
 * \return the first child of the given \a item with text \a name, or NULL.
 */
QStandardItem *PluginManagerPrivate::childWithText(const QStandardItem *item,
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
const QMetaObject *PluginManagerPrivate::baseClass(const QMetaObject *obj)
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
void PluginManagerPrivate::attachViews()
{
    auto setupTreeView = [this](QTreeView *tree, const QString &elementType,
                                Signal::Type signalType = Signal::INVALID) {
        // Filter model by element type and signal type
        auto filteredModel = new PluginFilterProxyModel(elementType, signalType);
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
        QObject::connect(tree->selectionModel(),
            &QItemSelectionModel::selectionChanged,
            [=](const QItemSelection &current, const QItemSelection &prev){
                if (current.indexes().isEmpty() && !prev.indexes().isEmpty())
                    tree->selectionModel()->select(prev, QItemSelectionModel::SelectCurrent);
            });
    };

    setupTreeView(ui->treeSource,       "DataSource");
    setupTreeView(ui->treeDecoderEeg,   "SampleDecoder",    Signal::EEG);
    setupTreeView(ui->treeDecoderVideo, "SampleDecoder",    Signal::VIDEO);
    setupTreeView(ui->treeDecoderImu,   "SampleDecoder",    Signal::IMU);
    setupTreeView(ui->treeFeatEeg,      "FeatureExtractor", Signal::EEG);
    setupTreeView(ui->treeFeatVideo,    "FeatureExtractor", Signal::VIDEO);
    setupTreeView(ui->treeFeatImu,      "FeatureExtractor", Signal::IMU);
    setupTreeView(ui->treeClassifier,   "Classifier");
}

/*!
 * \see PluginManager::loadPluginsFromSelection()
 */
ElementSetPtr PluginManagerPrivate::loadSelectedElements()
{
    qxtLog->info("Loading the selected set of elements");
    auto elements = doLoadElements(&PluginManagerPrivate::loadElementSetFromSelection);

    if (elements)
        saveSelectedElements();

    return elements;
}

/*!
 * \see PluginManager::loadPluginsFromSettings()
 */
ElementSetPtr PluginManagerPrivate::loadSavedElements()
{
    if (!QSettings().childGroups().contains("elements")) {
        qxtLog->debug("No saved elements to load");
        return ElementSetPtr();
    }

    qxtLog->info("Loading the saved set of elements");
    auto elements = doLoadElements(&PluginManagerPrivate::loadElementSetFromSettings);

    if (elements)
        selectSavedElements();

    return elements;
}

/*!
 * Load elements with the given \a loader and check whether it succeeded.
 * If so, return the ElementSet, otherwise return \c NULL.
 */
ElementSetPtr PluginManagerPrivate::doLoadElements(ElementLoader loader)
{
    auto elements = ElementSetPtr::create();

    // Populate the ElementSet
    (this->*loader)(elements);

    foreach (QObject *element, elements->allElements()) {
        if (!element) {
            qxtLog->warning("Failed to load all elements from plugins.");
            return ElementSetPtr();
        }
    }

    qxtLog->info("Successfully loaded all elements from plugins.");
    return elements;
}

/*!
 * Populate the given \a elements with the classes selected in the tree-views.
 *
 * \see loadElement()
 */
void PluginManagerPrivate::loadElementSetFromSelection(ElementSetPtr elements)
{
    loadElement(elements->dataSource,                       getSelectedElement(ui->treeSource));
    loadElement(elements->sampleDecoders[Signal::EEG],      getSelectedElement(ui->treeDecoderEeg));
    loadElement(elements->sampleDecoders[Signal::VIDEO],    getSelectedElement(ui->treeDecoderVideo));
    loadElement(elements->sampleDecoders[Signal::IMU],      getSelectedElement(ui->treeDecoderImu));
    loadElement(elements->featureExtractors[Signal::EEG],   getSelectedElement(ui->treeFeatEeg));
    loadElement(elements->featureExtractors[Signal::VIDEO], getSelectedElement(ui->treeFeatVideo));
    loadElement(elements->featureExtractors[Signal::IMU],   getSelectedElement(ui->treeFeatImu));
    loadElement(elements->classifier,                       getSelectedElement(ui->treeClassifier));
}

/*!
 * Populate the given \a elements with the classes saved in the settings file.
 *
 * \see loadElement()
 */
void PluginManagerPrivate::loadElementSetFromSettings(ElementSetPtr elements)
{
    loadElement(elements->dataSource,                       getSavedElement("data-source"));
    loadElement(elements->sampleDecoders[Signal::EEG],      getSavedElement("eeg-decoder"));
    loadElement(elements->sampleDecoders[Signal::VIDEO],    getSavedElement("video-decoder"));
    loadElement(elements->sampleDecoders[Signal::IMU],      getSavedElement("imu-decoder"));
    loadElement(elements->featureExtractors[Signal::EEG],   getSavedElement("eeg-featex"));
    loadElement(elements->featureExtractors[Signal::VIDEO], getSavedElement("video-featex"));
    loadElement(elements->featureExtractors[Signal::IMU],   getSavedElement("imu-featex"));
    loadElement(elements->classifier,                       getSavedElement("classifier"));
}

/*!
 * Load the plugin from \a info.pluginPath and instantiate an object of class
 * \a info.className. If the plugin cannot be loaded, the class cannot be
 * instantiated, or casting the instance to the requested ElementType fails,
 * \a element will be \c NULL. Otherwise \a element will hold the newly-created
 * element.
 */
template<class ElementType>
void PluginManagerPrivate::loadElement(ElementType &element, ClassInfo info)
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
PluginManagerPrivate::ClassInfo PluginManagerPrivate::getSelectedElement(QTreeView *tree)
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
PluginManagerPrivate::ClassInfo PluginManagerPrivate::getSavedElement(QString elementName)
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
void PluginManagerPrivate::saveSelectedElements()
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
void PluginManagerPrivate::selectSavedElements()
{
    QSettings settings;

    auto selectSavedElement = [&](QTreeView *tree, const QString &name) {
        QAbstractItemModel *model = tree->model();
        QItemSelectionModel *selection = tree->selectionModel();
        PluginManagerPrivate::ClassInfo info;

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

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

/*!
 * Construct a PluginManager as a child of the given \a parent.
 *
 * The default plugin search path is set to the "plugins" subdirectory of the
 * directory containing the application executable.
 */
PluginManager::PluginManager(QWidget *parent) :
    QDialog(parent),
    d_ptr(new PluginManagerPrivate(this))
{
    connect(this, SIGNAL(accepted()), SLOT(loadPluginsFromSelection()));
}

/*!
 * Destroy this PluginManager.
 */
PluginManager::~PluginManager()
{
    delete d_ptr;
}

/*!
 * \property PluginManager::searchPath
 * The directory in which to search for plugins.
 */
QDir PluginManager::searchPath() const
{
    Q_D(const PluginManager);
    return d->path;
}

/*!
 * Set the plugin search path to \a newPath and scan that directory for plugins.
 */
void PluginManager::setSearchPath(QDir newPath)
{
    Q_D(PluginManager);
    d->setSearchPath(newPath);
}

/*!
 * Show the Pluginmanager window, allowing the user to select the set of
 * elements they would like to load from plugins. If the window is not
 * cancelled, create a new element set and populate it with the classes that
 * were selected in the tree views.
 *
 * \see loadPluginsFromSelection()
 */
void PluginManager::selectPluginsToLoad()
{
    show();
}

/*!
 * Create a new ElementSet and populate it with the classes that are saved in
 * the settings file.
 */
void PluginManager::loadPluginsFromSettings()
{
    Q_D(PluginManager);
    auto elements = d->loadSavedElements();
    if (elements)
        emit pluginsLoaded(elements);
}

/*!
 * Called when the PluginManager window is closed with OK. Create a new
 * ElementSet and load the selected classes from plugins to populate it.
 */
void PluginManager::loadPluginsFromSelection()
{
    Q_D(PluginManager);
    auto elements = d->loadSelectedElements();
    if (elements)
        emit pluginsLoaded(elements);
}

/*!
 * \fn PluginManager::pluginsLoaded(ElementSetPtr)
 * Emitted when an ElementSet has been loaded.
 *
 * The lifetime of the created ElementSet is managed automatically by virtue of
 * using a QSharedPointer to refer to it. As soon as the last reference to the
 * ElementSet is dropped it will be deleted automatically.
 */
