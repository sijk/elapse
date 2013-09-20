#ifndef SINEPROVIDER_H
#define SINEPROVIDER_H

#include <QTimer>
#include "dataprovider.h"

class SineProvider : public DataProvider
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit SineProvider(QObject *parent = 0);

public slots:
    void start();
    void stop();

private slots:
    void onTimer();

private:
    QTimer t;
};

#endif // SINEPROVIDER_H
