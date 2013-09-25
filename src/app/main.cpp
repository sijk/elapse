#include <QApplication>
#include "pluginloader.h"
#include "threadedtcpclienteegdatasource.h"
#include "eegdecoder.h"
#include "mainwindow.h"

#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    ThreadedTcpClientEegDataSource source;
    EegDecoder eegdec;

    source.setProperty("host", "overo.local");

    eegdec.setProperty("gain", 1);
    eegdec.setProperty("vref", 4.5e6);

    QObject::connect(&source, SIGNAL(eegReady(QByteArray)),
                     &eegdec, SLOT(onData(QByteArray)));
    QObject::connect(&eegdec, SIGNAL(newSample(EegSample)),
                     &w, SLOT(onDataReady(EegSample)));
    QObject::connect(&w, SIGNAL(start()), &source, SLOT(start()));
    QObject::connect(&w, SIGNAL(stop()), &source, SLOT(stop()));
    QObject::connect(&source, SIGNAL(error(QString)),
                     &w, SLOT(onSourceError(QString)));

    w.show();
    return a.exec();
}
