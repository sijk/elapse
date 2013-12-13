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
    setSearchPath(QDir(qApp->applicationDirPath()).absoluteFilePath("plugins"));
    connect(this, SIGNAL(accepted()), SLOT(loadSelectedElementsFromPlugins()));
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
    if (newPath == path)
        return;

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
 * Helper function for loadSelectedElementsFromPlugins(). Load the plugin
 * containing the class that is selected in the given \a tree view and
 * return an instance of that class.
 *
 * If the plugin cannot be loaded, the class cannot be instantiated, or casting
 * the instance to the requested ElementType fails, a null pointer is returned.
 */
template<class ElementType>
ElementType loadSelected(QTreeView *tree)
{
    QModelIndexList idxs = tree->selectionModel()->selection().indexes();
    Q_ASSERT(idxs.size() == 1);
    QModelIndex index = idxs.at(0);

    QString className(index.data().toString());
    QString pluginPath(index.parent().data(FILEPATH_ROLE).toString());

    QPluginLoader loader(pluginPath);
    Plugin *plugin = static_cast<Plugin*>(loader.instance());

    if (!plugin)
        return nullptr;

    foreach (const QMetaObject &obj, plugin->classes()) {
        if (obj.className() == className) {
            QObject *instance = obj.newInstance();
            ElementType element = qobject_cast<ElementType>(instance);
            if (instance && !element)
                delete instance;
            return element;
        }
    }

    return nullptr;
}

/*!
 * Called when the PluginManager window is closed with OK. Create a new
 * ElementSet and load the selected classes from plugins to populate it.
 *
 * The lifetime of the created ElementSet is managed automatically by virtue of
 * using a QSharedPointer to refer to it. As soon as the last reference to the
 * ElementSet is dropped it will be deleted automatically.
 */
void PluginManager::loadSelectedElementsFromPlugins()
{
    auto elements = ElementSetPtr::create();

    elements->dataSource               = loadSelected<DataSource*>(ui->treeSource);
    elements->sampleDecoders[EEG]      = loadSelected<SampleDecoder*>(ui->treeDecoderEeg);
    elements->sampleDecoders[VIDEO]    = loadSelected<SampleDecoder*>(ui->treeDecoderVideo);
    elements->sampleDecoders[IMU]      = loadSelected<SampleDecoder*>(ui->treeDecoderImu);
    elements->featureExtractors[EEG]   = loadSelected<FeatureExtractor*>(ui->treeFeatEeg);
    elements->featureExtractors[VIDEO] = loadSelected<FeatureExtractor*>(ui->treeFeatVideo);
    elements->featureExtractors[IMU]   = loadSelected<FeatureExtractor*>(ui->treeFeatImu);
    elements->classifier               = loadSelected<Classifier*>(ui->treeClassifier);

    if (!elements->dataSource ||
        !elements->sampleDecoders[EEG] ||
        !elements->sampleDecoders[VIDEO] ||
        !elements->sampleDecoders[IMU] ||
        !elements->featureExtractors[EEG] ||
        !elements->featureExtractors[VIDEO] ||
        !elements->featureExtractors[IMU] ||
        !elements->classifier)
        return;

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
