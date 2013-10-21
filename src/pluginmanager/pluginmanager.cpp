#include <QJsonObject>
#include <QPluginLoader>
#include "plugin_base.h"
#include "pluginmanager.h"

#include <QDebug>


class GenericPlugin : public QObject, public BasePlugin<QObject>
{
    Q_OBJECT
};


/* ========================================================================== */


class ImplementationItem : public QStandardItem
{
public:
    ImplementationItem(const QString &key);
    void setData(const QVariant &value, int role);
};

ImplementationItem::ImplementationItem(const QString &key) :
    QStandardItem(key)
{
    setCheckable(true);
}

void ImplementationItem::setData(const QVariant &value, int role)
{
    if (role != Qt::CheckStateRole)
        return QStandardItem::setData(value, role);

    if (!parent())
        return QStandardItem::setData(value, role);

    // Disallow un-checking items
    if (value.toInt() != Qt::Checked)
        return;

    // Uncheck anything implementing the same interface as this
    auto iface = parent()->parent();
    for (int i = 0; i < iface->rowCount(); i++) {
        auto plugin = iface->child(i);
        for (int j = 0; j < plugin->rowCount(); j++) {
            auto impl = plugin->child(j);
            if (impl->checkState())
                impl->QStandardItem::setData(Qt::Unchecked, Qt::CheckStateRole);
        }
    }

    QStandardItem::setData(value, role);
}


/* ========================================================================== */


PluginManager::PluginManager(QDir searchPath, QObject *parent) :
    QObject(parent),
    _model(new QStandardItemModel(this))
{
    setSearchPath(searchPath);
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

            foreach (const QString &key, factory->keys()) {
                auto implItem = new ImplementationItem(key);
                pluginItem->appendRow(implItem);
            }

            // Select the first implementation of each interface by default
            if (ifaceItem->rowCount() == 1)
                pluginItem->child(0)->setCheckState(Qt::Checked);
        }

        loader.unload();
    }
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

    return item;
}

QStandardItem *PluginManager::createPluginItem(const QString &name,
                                               const QFileInfo &file)
{
    auto item = new QStandardItem(name);

    item->setData(file.absoluteFilePath());

    QFont font;
    font.setItalic(true);
    item->setFont(font);

    return item;
}
