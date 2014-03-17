#ifndef PLUGINFILTERPROXYMODEL_H
#define PLUGINFILTERPROXYMODEL_H

#include <QSortFilterProxyModel>
#include "elapse/sampletypes.h"


/*!
 * \brief The PluginFilterProxyModel class provides a filtered view of part of
 * the PluginManager's internal data model.
 *
 * It is used to map part of the model to each QTreeView in the PluginManager
 * window.
 *
 * \ingroup plugins-int
 */

class PluginFilterProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    PluginFilterProxyModel(const QString &elementType,
                           elapse::Signal::Type signalType,
                           QObject *parent = nullptr);
protected:
    bool filterAcceptsRow(int row, const QModelIndex &parent) const;

private:
    QString desiredElementType;
    elapse::Signal::Type desiredSignalType;
};

#endif // PLUGINFILTERPROXYMODEL_H
