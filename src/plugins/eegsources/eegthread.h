#ifndef EEGTHREAD_H
#define EEGTHREAD_H

#include <QThread>
#include <QMutex>

class EegThread : public QThread
{
    Q_OBJECT
public:
    explicit EegThread(QObject *parent = 0);
    ~EegThread();

    void run();

    void setHost(const QString &hostName, quint16 port);

signals:
    void newData(const QByteArray &data);
    void connected();
    void error(int socketError, const QString &message);

public slots:
    void connect();
    void disconnect();

private:
    QString hostName;
    quint16 port;
    QMutex mutex;
    bool quit;
};

#endif // EEGTHREAD_H
