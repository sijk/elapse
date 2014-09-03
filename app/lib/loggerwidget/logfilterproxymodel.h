#ifndef LOGFILTERPROXYMODEL_H
#define LOGFILTERPROXYMODEL_H

#include <QSortFilterProxyModel>
#include <QxtLogger>

namespace elapse { namespace log {

/*!
 * \brief The LogFilterProxyModel class filters the LogModel by log level.
 *
 * All messages in the source model with level less than minimumLogLevel()
 * will be hidden. The default minimum log level is \c InfoLevel. Changes to
 * the minimum log level are persistent between application restarts.
 *
 * \ingroup logging
 */

class LogFilterProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    explicit LogFilterProxyModel(QObject *parent = 0);

    QxtLogger::LogLevel minimumLogLevel() const;
    void setMinimumLogLevel(QxtLogger::LogLevel level);

protected:
    bool filterAcceptsRow(int srcRow, const QModelIndex &srcParent) const;

private:
    QxtLogger::LogLevel minLevel;
};

}} // namespace elapse::log

#endif // LOGFILTERPROXYMODEL_H
