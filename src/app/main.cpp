#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setOrganizationName("NeuroTech");
    a.setApplicationName("Elapse client");

    MainWindow window;
    window.show();

    return a.exec();
}
