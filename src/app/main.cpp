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

    window.show();
    return a.exec();
}
