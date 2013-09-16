#include "mainwindow.h"
#include "dataproviderinterface.h"
#include <QApplication>
#include <QDir>
#include <QPluginLoader>
#include <QJsonObject>

DataProviderPtr loadProvider()
{
    QDir pluginsDir(qApp->applicationDirPath());
    pluginsDir.cd("plugins");

    DataProviderPtr provider;

    foreach (QString fileName, pluginsDir.entryList(QDir::Files)) {
        QPluginLoader loader(pluginsDir.absoluteFilePath(fileName));
        QObject *plugin = loader.instance();
        auto factory = qobject_cast<DataProviderFactory*>(plugin);
        if (factory) {
            provider = factory->createProvider();
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
            if (iid != DataProviderFactory_iid)
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

    DataProviderPtr d = loadProvider();
    if (!d)
        return 1;

    QObject::connect(d.data(), SIGNAL(dataReady(double)), &w, SLOT(onDataReady(double)));
    QObject::connect(&w, SIGNAL(start()), d.data(), SLOT(start()));
    QObject::connect(&w, SIGNAL(stop()), d.data(), SLOT(stop()));

    w.showPluginName(d.data());
    return a.exec();
}
