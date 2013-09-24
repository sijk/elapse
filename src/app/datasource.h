#ifndef DATASOURCE_H
#define DATASOURCE_H

#include <QObject>
class QByteArray;

class DataSource : public QObject
{
    Q_OBJECT
public:
    explicit DataSource(QObject *parent = 0) : QObject(parent) {}
    virtual ~DataSource() {}

signals:
    void videoReady(const QByteArray &data);
    void eegReady(const QByteArray &data);
    void imuReady(const QByteArray &data);

public slots:
    virtual void start() = 0;
    virtual void stop() = 0;
};

#endif // DATASOURCE_H
