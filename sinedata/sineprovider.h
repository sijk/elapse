#ifndef SINEPROVIDER_H
#define SINEPROVIDER_H

#include <QTimer>
#include "dataproviderinterface.h"

class SineProvider : public DataProvider
{
    Q_OBJECT
public:
    explicit SineProvider(QObject *parent = 0);

public slots:
    void start();
    void stop();

private slots:
    void onTimer();

private:
    QTimer t;
};

DEFAULT_DATA_PROVIDER_FACTORY(SineProvider)

#endif // SINEPROVIDER_H
