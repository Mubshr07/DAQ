#include "mainwindow.h"
#include "mainhandler.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //MainWindow w;
    //w.show();

    qRegisterMetaType<uint32_t>("uint32_t");
    qRegisterMetaType<int32_t>("int32_t");

    qRegisterMetaType<GUI_WIN>();
    qRegisterMetaType<CHANNEL_TYPE>();
    qRegisterMetaType<CHANNEL_REFERENCE>();
    qRegisterMetaType<CHANNEL_PGA>();

    MainHandler handl;
    handl.initial_Start();



    return a.exec();
}
