#include <QModelIndex>
#include "pluginmanager_p.h"
#include "pluginfilterproxymodel.h"

/*!
 * Create a new PluginFilterProxyModel as a child of the given \a parent.
 * The model will only include classes that implement the given
 * \a elementType and which are applicable to the given \a sampleType.
 * If \a sampleType is empty, all classes implementing the \a elementType
 * will be included. If a class doesn't declare which \a sampleType it is
 * applicable to, it will also be included.
 *
 * \see \ref pluginmanager-model for a detailed description of the data model.
 */
PluginFilterProxyModel::PluginFilterProxyModel(const QString &elementType,
                                               const QString &sampleType,
                                               QObject *parent) :
    QSortFilterProxyModel(parent),
    desiredElementType(elementType),
    desiredSampleType(sampleType)
{
}

/*!
 * \return whether the item at the given model index should be included in the
 * filtered model.
 */
bool PluginFilterProxyModel::filterAcceptsRow(int row,
                                              const QModelIndex &parent) const
{
    QModelIndex index = sourceModel()->index(row, 0, parent);
    bool isElementItem = index.parent() == QModelIndex();
    bool isPluginItem = index.parent().parent() == QModelIndex();

    // Only accept classes implementing the desiredElementType
    if (isElementItem)
        return index.data().toString() == desiredElementType;

    if (isPluginItem)
        return true;

    // Exclude classes that explicitly don't work with the given sampleType
    QString sampleType = index.data(SAMPLETYPE_ROLE).toString();
    if (!desiredSampleType.isEmpty() && !sampleType.isEmpty())
        return sampleType == desiredSampleType;

    return true;
}
