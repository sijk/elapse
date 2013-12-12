#ifndef MODELLOGGERENGINE_H
#define MODELLOGGERENGINE_H

#include <QxtLoggerEngine>

class LogModel;
class QAbstractItemModel;


class ModelLoggerEngine : public QxtLoggerEngine
{
public:
    ModelLoggerEngine();
    ~ModelLoggerEngine();

    void initLoggerEngine();
    void killLoggerEngine();
    bool isInitialized() const;
    void writeFormatted(QxtLogger::LogLevel level,
                        const QList<QVariant> &messages);

    QAbstractItemModel *model();

private:
    LogModel *_model;
};

#endif // MODELLOGGERENGINE_H
