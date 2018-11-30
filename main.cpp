#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QCoreApplication::setOrganizationName("romanmatv developer");
    QCoreApplication::setOrganizationDomain("romanmatv.ru");
    QCoreApplication::setApplicationName("RM Key Gen");
    QCoreApplication::setApplicationVersion("0.0.1");

    QApplication::setOrganizationName("romanmatv developer");
    QApplication::setOrganizationDomain("romanmatv.ru");
    QApplication::setApplicationName("RM Key Gen");
    QApplication::setApplicationVersion("0.0.1");

    MainWindow w;
    w.show();

    return a.exec();
}
