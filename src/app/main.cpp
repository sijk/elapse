#include <QApplication>
#include "pluginloader.h"
#include "tcpclienteegdatasource.h"
#include "eegdecoder.h"
#include "mainwindow.h"

#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    TcpClientEegDataSource source;
    EegDecoder eegdec;

    eegdec.setGains({1,1,1,1,1,1,1,1});
    eegdec.setVref(4.5e6);

    QObject::connect(&source, SIGNAL(eegReady(QByteArray)),
                     &eegdec, SLOT(onData(QByteArray)));
    QObject::connect(&eegdec, SIGNAL(newSample(EegSample)),
                     &w, SLOT(onDataReady(EegSample)));
    QObject::connect(&w, SIGNAL(start()), &source, SLOT(start()));
    QObject::connect(&w, SIGNAL(stop()), &source, SLOT(stop()));

    w.show();
    return a.exec();
}
