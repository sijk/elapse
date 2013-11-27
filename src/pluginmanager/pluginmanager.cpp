#include <QCoreApplication>
#include <QMetaClassInfo>
#include <QJsonObject>
#include <QPluginLoader>
#include <QStandardItemModel>
#include "plugin.h"
#include "elements.h"
#include "pluginfilterproxymodel.h"
#include "pluginmanager_p.h"
#include "pluginmanager.h"
#include "ui_pluginmanager.h"

#include <QDebug>


PluginManager::PluginManager(QWidget *parent) :
    QDialog(parent),
    model(new QStandardItemModel(this)),
    ui(new Ui::PluginManager)
{
    ui->setupUi(this);
    setSearchPath(QDir(qApp->applicationDirPath()).absoluteFilePath("plugins"));
    connect(this, SIGNAL(accepted()), SLOT(loadSelectedElementsFromPlugins()));
}

PluginManager::~PluginManager()
{
    delete ui;
}

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
            qDebug() << loader.errorString();
        }

        loader.unload();
    }

    attachViews();
}

void PluginManager::loadPlugins()
{
    show();
}

void PluginManager::loadSelectedElementsFromPlugins()
{
    ElementSet *elements = new ElementSet;

    // Load plugin and instantiate selected class for each element

    emit pluginsLoaded(elements);
}

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

const QMetaObject *PluginManager::baseClass(const QMetaObject *obj)
{
    const QMetaObject *super = obj->superClass();
    if (super && super != &QObject::staticMetaObject)
        return baseClass(super);
    return obj;
}

void PluginManager::attachViews()
{
    auto setupTreeView = [this](QTreeView *tree, const QString &iid,
                                const QString &sampleType = QString()) {
        // Filter model by element type and sample type
        auto filteredModel = new PluginFilterProxyModel(iid, sampleType);
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
