#ifndef DUMMYEEGSOURCE_H
#define DUMMYEEGSOURCE_H

#include <QTimer>
#include "datasource.h"

class DummyEegSource : public DataSource
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit DummyEegSource(QObject *parent = 0);

public slots:
    void start();
    void stop();

private slots:
    void onTimer();

private:
    void appendSampleToChunk();
    QTimer timer;
    quint32 seqnum;
    QByteArray chunk;
};

#endif // DUMMYEEGSOURCE_H