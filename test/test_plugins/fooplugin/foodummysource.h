#ifndef FOODUMMYSOURCE_H
#define FOODUMMYSOURCE_H

#include <QTimer>
#include "elements/datasource.h"


class FooDummySource : public DataSource
{
    Q_OBJECT

public:
    Q_INVOKABLE explicit FooDummySource(QObject *parent = nullptr);

public slots:
    void start();
    void stop();

private slots:
    void emitDummyData();

private:
    QTimer timer;
};

#endif // FOODUMMYSOURCE_H
