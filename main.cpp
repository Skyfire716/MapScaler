#include "mainwindow.h"

#include <QApplication>
#include <qtwebengineglobal.h>

int main(int argc, char *argv[])
{
    QtWebEngine::initialize();
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
