#include <QCoreApplication>
#include <QMetaClassInfo>
#include <QJsonObject>
#include <QPluginLoader>
#include <QFileDialog>
#include <QxtLogger>
#include "elapse/plugin.h"
#include "pluginfilterproxymodel.h"
#include "elementsetfactory.h"
#include "pluginmanager.h"
#include "pluginmanager_p.h"
#include "pluginmanager_def.h"


/*!
 * \page pluginmanager-model PluginManager Data Model
 *
 * This page describes the structure of the PluginManager's internal data model.
 *
 * Suppose that we have two plugins, \c FooPlugin and \c BarPlugin. They each
 * provide several classes implementing elapse::DataSource and
 * elapse::SampleDecoder element types. This hypothetical situation is
 * illustrated below.
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
 * \c elementType = "SampleDecoder" and \c signalType = Signal::EEG, then the
 * filtered model would have the following structure:
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


/*!
 * Create the private data for the given PluginManager. Set the search path to
 * the default and populate the plugin model from that path.
 */
PluginManagerPrivate::PluginManagerPrivate(PluginManager *q) :
    q_ptr(q),
    corePluginDir(QDir(qApp->applicationDirPath()).absoluteFilePath("plugins"))
{
    ui.setupUi(q);

    QObject::connect(ui.pathButton, &QPushButton::clicked, [=]{
        QString dir = QFileDialog::getExistingDirectory(q, "Plugin path");
        if (!dir.isEmpty())
            setSearchPath(dir);
    });

    QString defaultUserPluginDir = QSettings().value("plugins-path").toString();
    setSearchPath(defaultUserPluginDir);
}

/*!
 * Enable testing code to access the d_ptr of the public class.
 */
PluginManagerPrivate *PluginManagerPrivate::expose(PluginManager *manager)
{
    return manager->d_func();
}

/*!
 * \see PluginManager::setSearchPath()
 */
void PluginManagerPrivate::setSearchPath(QDir newPath)
{
    if (newPath == userPluginDir && model.rowCount() > 0) {
        qxtLog->debug("PluginManager search path was set to the current value. "
                      "Not doing anything...");
        return;
    }

    userPluginDir = newPath;

    model.clear();
    searchForPluginsIn(corePluginDir);
    if (userPluginDir.exists()) {
        searchForPluginsIn(userPluginDir);
        QSettings().setValue("plugins-path", userPluginDir.absolutePath());
    }

    attachViews();
}

void PluginManagerPrivate::searchForPluginsIn(QDir dir)
{
    qxtLog->info("Searching for plugins in", dir.absolutePath());

    auto rootItem = model.invisibleRootItem();

    foreach (QFileInfo file, dir.entryInfoList(QDir::Files)) {
        QPluginLoader loader(file.absoluteFilePath());
        QObject *plugin = loader.instance();
        auto factory = qobject_cast<elapse::PluginInterface*>(plugin);

        if (factory) {
            QString pluginName = loader.metaData()["className"].toString();

            foreach (const QMetaObject &obj, factory->classes()) {
                QString elementName = baseClass(&obj)->className();
                // Remove namespace qualifiers
                elementName = elementName.remove(0, elementName.lastIndexOf(':') + 1);

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
            qxtLog->debug(loader.errorString());
        }

        loader.unload();
    }

    model.sort(0);
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
        auto filteredModel = new PluginFilterProxyModel(elementType, signalType, tree);
        filteredModel->setSourceModel(&model);

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

    setupTreeView(ui.dataSource,            "DataSource");
    setupTreeView(ui.sampleDecoderEeg,      "SampleDecoder",    Signal::EEG);
    setupTreeView(ui.sampleDecoderVideo,    "SampleDecoder",    Signal::VIDEO);
    setupTreeView(ui.sampleDecoderImu,      "SampleDecoder",    Signal::IMU);
    setupTreeView(ui.featureExtractorEeg,   "FeatureExtractor", Signal::EEG);
    setupTreeView(ui.featureExtractorVideo, "FeatureExtractor", Signal::VIDEO);
    setupTreeView(ui.featureExtractorImu,   "FeatureExtractor", Signal::IMU);
    setupTreeView(ui.classifier,            "Classifier");
    setupTreeView(ui.dataSink,              "DataSinkDelegate");
}

/*!
 * \return the details of the class that is selected in the given \a tree view.
 */
ClassInfo PluginManagerPrivate::getSelectedElement(const QTreeView *tree)
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
 * Inspect the tree views and save the details of the selected elements to
 * the settings file.
 */
void PluginManagerPrivate::saveSelectedElements()
{
    Q_Q(PluginManager);
    QSettings settings;
    auto trees = q->findChildren<QTreeView*>();

    foreach (const QTreeView *tree, trees) {
        ClassInfo info = getSelectedElement(tree);
        QString name = tree->objectName();

        settings.setValue(pathSetting.arg(name), info.pluginPath);
        settings.setValue(classSetting.arg(name), info.className);
    }

    qxtLog->info("Saved current element selection");
}

/*!
 * Set the selections in the tree views to match the elements that are saved
 * in the settings file.
 */
void PluginManagerPrivate::selectSavedElements()
{
    Q_Q(PluginManager);
    QSettings settings;
    auto trees = q->findChildren<QTreeView*>();

    foreach (const QTreeView *tree, trees) {
        QAbstractItemModel *model = tree->model();
        QString name = tree->objectName();
        QItemSelectionModel *selection = tree->selectionModel();
        ClassInfo info;

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
    }
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
    return d->userPluginDir;
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

    qxtLog->info("Loading the saved set of elements");
    SelectElementsFromSettings selectFromSettings;
    auto elements = ElementSetFactory::loadUsingStrategy(&selectFromSettings);

    if (elements) {
        d->selectSavedElements();
        emit pluginsLoaded(elements);
    }
}

/*!
 * Called when the PluginManager window is closed with OK. Create a new
 * ElementSet and load the selected classes from plugins to populate it.
 */
void PluginManager::loadPluginsFromSelection()
{
    Q_D(PluginManager);

    qxtLog->info("Loading the selected set of elements");
    SelectElementsFromGui selectFromGui(this);
    auto elements = ElementSetFactory::loadUsingStrategy(&selectFromGui);

    if (elements) {
        d->saveSelectedElements();
        emit pluginsLoaded(elements);
    }
}

/*!
 * \fn PluginManager::pluginsLoaded(ElementSetPtr)
 * Emitted when an ElementSet has been loaded.
 *
 * The lifetime of the created ElementSet is managed automatically by virtue of
 * using a QSharedPointer to refer to it. As soon as the last reference to the
 * ElementSet is dropped it will be deleted automatically.
 */

