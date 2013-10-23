#include <QCoreApplication>
#include <QMetaClassInfo>
#include <QJsonObject>
#include <QPluginLoader>
#include <QStandardItemModel>
#include <QSortFilterProxyModel>
#include "plugin.h"
#include "sampletypes.h"
#include "pluginmanager.h"
#include "ui_pluginmanager.h"

#include <QDebug>


/* ========================================================================== */


template<class T>
struct ElementContainer
{
    T dataSource;
    T sampleDecoders[N_SAMPLE_TYPES];
    T featureExtractors[N_SAMPLE_TYPES];
    T classifier;
};


enum PluginItemDataRole
{
    SAMPLETYPE_ROLE = Qt::UserRole,
    FILEPATH_ROLE
};


/* ========================================================================== */


class PluginFilterProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    PluginFilterProxyModel(const QString &acceptableInterface,
                           const QString &acceptableSampleType,
                           QObject *parent = nullptr);
protected:
    bool filterAcceptsRow(int srcRow, const QModelIndex &srcParent) const;

private:
    QString acceptableInterface;
    QString acceptableSampleType;
};

PluginFilterProxyModel::PluginFilterProxyModel(const QString &iid,
                                               const QString &sampleType,
                                               QObject *parent) :
    QSortFilterProxyModel(parent),
    acceptableInterface(iid),
    acceptableSampleType(sampleType)
{
}

bool PluginFilterProxyModel::filterAcceptsRow(int srcRow,
                                              const QModelIndex &srcParent) const
{
    QModelIndex index = sourceModel()->index(srcRow, 0, srcParent);
    bool isInterfaceItem = index.parent() == QModelIndex();
    bool isPluginItem = index.parent().parent() == QModelIndex();

    // Only accept plugins implementing the given interface
    if (isInterfaceItem)
        return index.data().toString() == acceptableInterface;

    if (isPluginItem)
        return true;

    // Exclude classes that explicitly don't work with the given sampleType
    QString sampleType = index.data(SAMPLETYPE_ROLE).toString();
    if (!acceptableSampleType.isEmpty() && !sampleType.isEmpty())
        return sampleType == acceptableSampleType;

    return true;
}

#include "pluginmanager.moc"


/* ========================================================================== */


PluginManager::PluginManager(QDir searchPath, QWidget *parent) :
    QDialog(parent),
    _model(new QStandardItemModel(this)),
    ui(new Ui::PluginManager)
{
    ui->setupUi(this);

    if (searchPath == QDir())
        searchPath = QDir(qApp->applicationDirPath()).absoluteFilePath("plugins");

    setSearchPath(searchPath);
}

PluginManager::~PluginManager()
{
    delete ui;
}

void PluginManager::setSearchPath(QDir path)
{
    if (path == _path)
        return;

    _path = path;
    _model->clear();
    auto rootItem = _model->invisibleRootItem();

    foreach (QFileInfo file, path.entryInfoList(QDir::Files)) {
        QPluginLoader loader(file.absoluteFilePath());
        QObject *plugin = loader.instance();
        if (!plugin) qDebug() << "loader instance is null";
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
            qDebug() << "factory cast to plugin failed";
            qDebug() << loader.errorString();
        }

        loader.unload();
    }

    attachViews();
}

QStandardItemModel *PluginManager::model() const
{
    return _model;
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
        filteredModel->setSourceModel(_model);

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
