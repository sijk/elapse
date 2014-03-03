#include <QSettings>
#include "logmodel.h"
#include "logfilterproxymodel.h"

/*!
 * Construct a new LogFilterProxyModel as a child of the given parent.
 */
LogFilterProxyModel::LogFilterProxyModel(QObject *parent) :
    QSortFilterProxyModel(parent)
{
    QVariant savedLevel(QSettings().value("logview/level", QxtLogger::InfoLevel));
    minLevel = QxtLogger::LogLevel(savedLevel.toInt());

    setFilterKeyColumn(2);
    setFilterCaseSensitivity(Qt::CaseInsensitive);
}

/*!
 * Set the minimum log level to \a level. All messages below this level wil be
 * hidden.
 */
void LogFilterProxyModel::setMinimumLogLevel(QxtLogger::LogLevel level)
{
    minLevel = level;
    invalidateFilter();
    QSettings().setValue("logview/level", int(level));
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

    if (level >= minLevel)
        return QSortFilterProxyModel::filterAcceptsRow(srcRow, srcParent);

    return false;
}