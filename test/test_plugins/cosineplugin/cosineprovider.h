#ifndef COSINEPROVIDER_H
#define COSINEPROVIDER_H

#include <QTimer>
#include "dataprovider.h"

class CosineProvider : public DataProvider
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit CosineProvider(QObject *parent = 0);

public slots:
    void start();
    void stop();

private slots:
    void onTimer();

private:
    QTimer t;
};

#endif // COSINEPROVIDER_H
