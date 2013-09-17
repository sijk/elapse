#include "mainwindow.h"
#include "dataproviderplugin.h"
#include <QApplication>
#include <QDir>
#include <QPluginLoader>
#include <QJsonObject>

DataProvider *loadProvider()
{
    QDir pluginsDir(qApp->applicationDirPath());
    pluginsDir.cd("plugins");

    DataProvider *provider = 0;

    foreach (QString fileName, pluginsDir.entryList(QDir::Files)) {
        QPluginLoader loader(pluginsDir.absoluteFilePath(fileName));
        QObject *plugin = loader.instance();
        auto factory = qobject_cast<DataProviderFactoryInterface*>(plugin);
        if (factory) {
            qDebug() << factory->keys();
            QString first = factory->keys()[0];
            provider = factory->create(first);
            if (provider) {
                qDebug() << "Loaded" << loader.metaData()["className"].toString()
                         << "from" << fileName;
                break;
            } else
                qDebug() << "Error creating DataProvider from"
                         << loader.metaData()["className"].toString();
        } else {
            auto iid = loader.metaData()["IID"].toString();
            auto cls = loader.metaData()["className"].toString();
            if (iid != DataProviderFactoryInterface_iid)
                qDebug() << cls << "from" << fileName << "has incomaptible IID" << iid;
            else
                qDebug() << loader.errorString();
        }
    }

    return provider;
}


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    DataProvider *d = loadProvider();
    if (!d)
        return 1;

    QObject::connect(d, SIGNAL(dataReady(double)), &w, SLOT(onDataReady(double)));
    QObject::connect(&w, SIGNAL(start()), d, SLOT(start()));
    QObject::connect(&w, SIGNAL(stop()), d, SLOT(stop()));

    w.showPluginName(d);
    return a.exec();
}
