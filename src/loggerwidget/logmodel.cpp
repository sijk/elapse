#include <QMap>
#include <QBrush>
#include "logmodel.h"

static const QMap<QxtLogger::LogLevel, QBrush> levelColours = {
    { QxtLogger::TraceLevel,    Qt::gray        },
    { QxtLogger::DebugLevel,    Qt::lightGray   },
    { QxtLogger::InfoLevel,     Qt::white       },
    { QxtLogger::WarningLevel,  Qt::yellow      },
    { QxtLogger::ErrorLevel,    Qt::red         },
    { QxtLogger::CriticalLevel, Qt::magenta     },
    { QxtLogger::FatalLevel,    Qt::darkMagenta },
    { QxtLogger::WriteLevel,    Qt::white       },
};

/*!
 * Construct a new LogModel as a child of the given \a parent.
 */
LogModel::LogModel(QObject *parent) :
    QAbstractTableModel(parent)
{
}

int LogModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return _items.size();
}

int LogModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 3;
}

QVariant LogModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() > _items.size())
        return QVariant();

    const LogItem &item = _items.at(index.row());

    switch (role) {
    case Qt::DisplayRole:
        switch (index.column()) {
        case 0:
            return item.time.toString("hh:mm:ss.zzz");
        case 1:
            return QxtLogger::logLevelToString(item.level).remove("Level");
        case 2:
            return item.message;
        }

    case LOG_LEVEL_ROLE:
        return item.level;

    case Qt::BackgroundRole:
        switch (index.column()) {
        case 1:
            return levelColours[item.level];
        }

    case Qt::TextAlignmentRole:
        switch (index.column()) {
        case 1:
            return Qt::AlignCenter;
        }
    }

    return QVariant();
}

QVariant LogModel::headerData(int section, Qt::Orientation orientation,
                              int role) const
{
    if (orientation == Qt::Vertical)
        return QVariant();

    if (role != Qt::DisplayRole)
        return QVariant();

    switch (section) {
    case 0:
        return "Time";
    case 1:
        return "Level";
    case 2:
        return "Message";
    }

    return QVariant();
}

/*!
 * Append the given \a item to the table model.
 */
void LogModel::appendItem(const LogItem &item)
{
    int row = _items.size();
    beginInsertRows(QModelIndex(), row, row);
    _items.append(item);
    endInsertRows();
}
