#include <QApplication>
#include "pipeline.h"
#include "mainwindow.h"

#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Pipeline pipeline;
    MainWindow window(pipeline.pluginLoader());

    pipeline.setElementProperty("DataSource", "host", "overo.local");

    QObject::connect(&window,   SIGNAL(start()),
                     &pipeline, SLOT(start()));
    QObject::connect(&window,   SIGNAL(stop()),
                     &pipeline, SLOT(stop()));

    QObject::connect(&pipeline, SIGNAL(started()),
                     &window,   SLOT(onSourceStarted()));
    QObject::connect(&pipeline, SIGNAL(error(QString)),
                     &window,   SLOT(onSourceError(QString)));

#if 0
    source->setProperty("host", "overo.local");
    eegdec.setProperty("gain", 1);
    eegdec.setProperty("vref", 4.5e6);

    // Connect EEG signal chain
    QObject::connect(source, SIGNAL(eegReady(QByteArray)),
                     &eegdec, SLOT(onData(QByteArray)));
    QObject::connect(&eegdec, SIGNAL(newSample(EegSample)),
                     &w, SLOT(onDataReady(EegSample)));

    // Connect EEG file sink
    QObject::connect(&w, SIGNAL(start()), &eegsink, SLOT(startRecording()));
    QObject::connect(source, SIGNAL(eegReady(QByteArray)),
                     &eegsink, SLOT(onData(QByteArray)));
    QObject::connect(&w, SIGNAL(stop()), &eegsink, SLOT(stopRecording()));

    // Connect controls to source
    QObject::connect(&w, SIGNAL(start()), source, SLOT(start()));
    QObject::connect(&w, SIGNAL(stop()), source, SLOT(stop()));

    // Connect source signals to GUI
    QObject::connect(source, SIGNAL(error(QString)),
                     &w, SLOT(onSourceError(QString)));
    QObject::connect(source, SIGNAL(started()),
                     &w, SLOT(onSourceStarted()));
#endif

    window.show();
    return a.exec();
}
