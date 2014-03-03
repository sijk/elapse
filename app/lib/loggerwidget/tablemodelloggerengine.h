#ifndef TABLEMODELLOGGERENGINE_H
#define TABLEMODELLOGGERENGINE_H

#include <QxtLoggerEngine>

class LogModel;
class QAbstractItemModel;


/*!
 * \brief The TableModelLoggerEngine class is a QxtLoggerEngine that stores
 * messages in a table model.
 * \ingroup logging
 */

class TableModelLoggerEngine : public QxtLoggerEngine
{
public:
    TableModelLoggerEngine();
    ~TableModelLoggerEngine();

    void initLoggerEngine();
    void killLoggerEngine();
    bool isInitialized() const;
    void writeFormatted(QxtLogger::LogLevel level,
                        const QList<QVariant> &messages);

    QAbstractItemModel *model();

private:
    LogModel *_model;
};

#endif // TABLEMODELLOGGERENGINE_H