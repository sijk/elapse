#include <QModelIndex>
#include "pluginmanager_p.h"
#include "pluginfilterproxymodel.h"

PluginFilterProxyModel::PluginFilterProxyModel(const QString &elementType,
                                               const QString &sampleType,
                                               QObject *parent) :
    QSortFilterProxyModel(parent),
    desiredElementType(elementType),
    desiredSampleType(sampleType)
{
}

bool PluginFilterProxyModel::filterAcceptsRow(int row,
                                              const QModelIndex &parent) const
{
    QModelIndex index = sourceModel()->index(row, 0, parent);
    bool isInterfaceItem = index.parent() == QModelIndex();
    bool isPluginItem = index.parent().parent() == QModelIndex();

    // Only accept plugins implementing the given interface
    if (isInterfaceItem)
        return index.data().toString() == desiredElementType;

    if (isPluginItem)
        return true;

    // Exclude classes that explicitly don't work with the given sampleType
    QString sampleType = index.data(SAMPLETYPE_ROLE).toString();
    if (!desiredSampleType.isEmpty() && !sampleType.isEmpty())
        return sampleType == desiredSampleType;

    return true;
}
