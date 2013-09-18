#include "mainwindow.h"
#include "pluginloader.h"
#include "dataprovider.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    PluginLoader loader;
    QString providerKey = "SineProvider";

    if (!loader.keysForInterface(DataProviderInterface_iid).contains(providerKey)) {
        qDebug() << providerKey << "not found";
        return 1;
    }

    QObject *provider = loader.create(providerKey);
    if (!provider) {
        qDebug() << "Loading failed";
        return 1;
    }

    QObject::connect(provider, SIGNAL(dataReady(double)), &w, SLOT(onDataReady(double)));
    QObject::connect(&w, SIGNAL(start()), provider, SLOT(start()));
    QObject::connect(&w, SIGNAL(stop()), provider, SLOT(stop()));

    w.showProviderName(provider);
    w.show();
    return a.exec();
}
