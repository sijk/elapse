#ifndef LOGMODEL_H
#define LOGMODEL_H

#include <QAbstractTableModel>
#include <QxtLogger>

namespace elapse { namespace log {

/*!
 * \brief The LogItem struct represents a logged message.
 * \ingroup logging
 */

struct LogItem {
    QString time;
    QxtLogger::LogLevel level;
    QString message;
};


#define LOG_LEVEL_ROLE  Qt::UserRole


/*!
 * \brief The LogModel class stores LogItem%s in a table model.
 * \ingroup logging
 */

class LogModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit LogModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;

    void appendItem(const LogItem &item);

private:
    QList<LogItem> _items;
};

}} // namespace elapse::log

#endif // LOGMODEL_H
