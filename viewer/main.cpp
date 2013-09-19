#include <QApplication>
#include "pluginloader.h"
#include "dataprovider.h"
#include "mainwindow.h"

#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PluginLoader loader;
    MainWindow w(loader);

    QString providerIID = DataProviderInterface_iid;
    QString providerKey = "SineProvider";

    if (!loader.keysForInterface(providerIID).contains(providerKey)) {
        qDebug() << providerKey << "not found";
        return 1;
    }

    QObject *provider = loader.create(providerKey);
    if (!provider) {
        qDebug() << "Loading failed";
        return 1;
    }

    QObject::connect(provider, SIGNAL(dataReady(double)),
                     &w, SLOT(onDataReady(double)));
    QObject::connect(&w, SIGNAL(start()), provider, SLOT(start()));
    QObject::connect(&w, SIGNAL(stop()), provider, SLOT(stop()));

    w.show();
    return a.exec();
}
