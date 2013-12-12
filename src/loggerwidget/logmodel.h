#ifndef LOGMODEL_H
#define LOGMODEL_H

#include <QAbstractTableModel>
#include <QTime>
#include <QxtLogger>


struct LogItem {
    QTime time;
    QxtLogger::LogLevel level;
    QString message;
};


class LogModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit LogModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const;

    void appendItem(const LogItem &item);

private:
    QList<LogItem> _items;
};

#endif // LOGMODEL_H
