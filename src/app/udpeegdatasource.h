#ifndef UDPEEGDATASOURCE_H
#define UDPEEGDATASOURCE_H

#include <QUdpSocket>
#include "datasource.h"

class UdpEegDataSource : public DataSource
{
    Q_OBJECT
public:
    explicit UdpEegDataSource(QObject *parent = 0);

public slots:
    void start();
    void stop();

private slots:
    void onDataReady();

private:
    QUdpSocket sock;
    bool do_emit;
};

#endif // UDPEEGDATASOURCE_H
