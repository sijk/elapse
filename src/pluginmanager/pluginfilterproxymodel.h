#ifndef PLUGINFILTERPROXYMODEL_H
#define PLUGINFILTERPROXYMODEL_H

#include <QSortFilterProxyModel>

/*!
 * \brief The PluginFilterProxyModel class provides a filtered view of part of
 * the PluginManager's internal data model.
 *
 * It is used to map part of the model to each QTreeView in the PluginManager
 * window.
 */

class PluginFilterProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    PluginFilterProxyModel(const QString &elementType,
                           const QString &sampleType,
                           QObject *parent = nullptr);
protected:
    bool filterAcceptsRow(int row, const QModelIndex &parent) const;

private:
    QString desiredElementType;
    QString desiredSampleType;
};

#endif // PLUGINFILTERPROXYMODEL_H
