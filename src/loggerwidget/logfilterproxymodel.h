#ifndef LOGFILTERPROXYMODEL_H
#define LOGFILTERPROXYMODEL_H

#include <QSortFilterProxyModel>
#include <QxtLogger>


/*!
 * \brief The LogFilterProxyModel class filters the LogModel by log level.
 *
 * All messages in the source model with level less than minimumLogLevel()
 * will be hidden. The default minimum log level is \c InfoLevel.
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

#endif // LOGFILTERPROXYMODEL_H
