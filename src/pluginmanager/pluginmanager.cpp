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


class GenericPlugin : public QObject, public FactoryInterface<QObject>
{
    Q_OBJECT
};


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
        auto factory = static_cast<GenericPlugin*>(plugin);

        if (factory) {
            QJsonObject metadata = loader.metaData();
            QString iid = metadata["IID"].toString();
            QString name = metadata["className"].toString();

            auto ifaceItem = createInterfaceItem(iid);
            rootItem->appendRow(ifaceItem);

            auto pluginItem = createPluginItem(name, file);
            ifaceItem->appendRow(pluginItem);

            foreach (const QMetaObject &obj, factory->classes()) {
                auto implItem = createImplementationItem(obj);
                pluginItem->appendRow(implItem);
            }
        }

        loader.unload();
    }

    attachViews();
}

QStandardItemModel *PluginManager::model() const
{
    return _model;
}

QStandardItem *PluginManager::createInterfaceItem(const QString &iid)
{
    auto iface = _model->findItems(iid);
    if (!iface.isEmpty())
        return iface.at(0);

    auto item = new QStandardItem(iid);

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

QStandardItem *PluginManager::createImplementationItem(const QMetaObject &obj)
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

void PluginManager::attachViews()
{
    auto setupTreeView = [this](QTreeView *tree, const QString &iid,
                                const QString &sampleType = QString()) {
        auto filteredModel = new PluginFilterProxyModel(iid, sampleType);
        filteredModel->setSourceModel(_model);

        tree->setModel(filteredModel);
        // TODO: do this root item selection inside the proxy model
        tree->setRootIndex(tree->model()->index(0,0));
        tree->expandAll();

        // Select the first implementation by default
        tree->selectionModel()->select(tree->rootIndex().child(0,0).child(0,0),
                                       QItemSelectionModel::SelectCurrent);

        // Ensure that something is always selected from then on
        connect(tree->selectionModel(), &QItemSelectionModel::selectionChanged,
            [=](const QItemSelection &current, const QItemSelection &prev){
                if (current.indexes().isEmpty() && !prev.indexes().isEmpty())
                    tree->selectionModel()->select(prev, QItemSelectionModel::SelectCurrent);
            });
    };

    setupTreeView(ui->treeSource,       DataSourceInterface_iid);
    setupTreeView(ui->treeDecoderEeg,   SampleDecoderInterface_iid,    "EEG");
    setupTreeView(ui->treeDecoderVideo, SampleDecoderInterface_iid,    "VIDEO");
    setupTreeView(ui->treeDecoderImu,   SampleDecoderInterface_iid,    "IMU");
    setupTreeView(ui->treeFeatEeg,      FeatureExtractorInterface_iid, "EEG");
    setupTreeView(ui->treeFeatVideo,    FeatureExtractorInterface_iid, "VIDEO");
    setupTreeView(ui->treeFeatImu,      FeatureExtractorInterface_iid, "IMU");
    setupTreeView(ui->treeClassifier,   ClassifierInterface_iid);
}
