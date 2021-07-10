#include "mainwindow.h"
#include "mainhandler.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //MainWindow w;
    //w.show();

    qRegisterMetaType<GUI_WIN>();
    qRegisterMetaType<CHANNEL_TYPE>();
    qRegisterMetaType<CHANNEL_REFERENCE>();

    MainHandler handl;
    handl.initial_Start();



    return a.exec();
}
