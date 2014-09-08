#include <QApplication>
#include "elapseclient.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setOrganizationName("NeuroTech");
    a.setApplicationName("Elapse client");

    elapse::client::ElapseClient elapseClient;
    elapseClient.show();

    return a.exec();
}
