#include "logmodel.h"
#include "logfilterproxymodel.h"

/*!
 * Construct a new LogFilterProxyModel as a child of the givena parent.
 */
LogFilterProxyModel::LogFilterProxyModel(QObject *parent) :
    QSortFilterProxyModel(parent),
    minLevel(QxtLogger::InfoLevel)
{
}

/*!
 * Set the minimum log level to \a level. All messages below this level wil be
 * hidden.
 */
void LogFilterProxyModel::setMinimumLogLevel(QxtLogger::LogLevel level)
{
    minLevel = level;
    invalidateFilter();
}

/*!
 * \return the current minimum log level.
 */
QxtLogger::LogLevel LogFilterProxyModel::minimumLogLevel() const
{
    return minLevel;
}

/*!
 * \return whether the given log item should be passed through the filter
 * or not.
 */
bool LogFilterProxyModel::filterAcceptsRow(int srcRow,
                                           const QModelIndex &srcParent) const
{
    QModelIndex idx = sourceModel()->index(srcRow, 1, srcParent);
    int level = sourceModel()->data(idx, LOG_LEVEL_ROLE).toInt();
    return level >= minLevel;
}
