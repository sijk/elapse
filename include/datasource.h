#ifndef DATASOURCE_H
#define DATASOURCE_H

#include <QObject>
class QByteArray;

class DataSource : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString host MEMBER _host)

public:
    explicit DataSource(QObject *parent = 0) : QObject(parent) {}
    virtual ~DataSource() {}

signals:
    void videoReady(const QByteArray &data);
    void eegReady(const QByteArray &data);
    void imuReady(const QByteArray &data);

    void started();
    void error(const QString &message);

public slots:
    virtual void start() = 0;
    virtual void stop() = 0;

protected:
    QString _host;
};

#endif // DATASOURCE_H
