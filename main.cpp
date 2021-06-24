#include "mainwindow.h"
#include "mainhandler.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //MainWindow w;
    //w.show();
    MainHandler handl;
    handl.initial_Start();



    return a.exec();
}
