#ifndef MAINHANDLER_H
#define MAINHANDLER_H

#include <QObject>
#include <QCoreApplication>

#include "classes/chnlclass_simple.h"
#include "classes/loggerthread.h"
#include "classes/globalvars.h"
#include "firstwindow.h"
#include "mainwindow.h"
#include "graphwin.h"
#include "configchwin.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainHandler : public QObject
{
    Q_OBJECT
public:
    explicit MainHandler(QObject *parent = nullptr);

signals:
    void tx_saalsdfj();

public slots:
    void initial_Start();
    void rx_generate_ThisGUI(GUI_WIN guiEnum);




    void generate_firstWindow();
    void generate_logConfig();
    void generate_graphWin();
    void generate_ConfigCHWin();

    void rx_ClosingWindow_FirstWin(bool shutDown);
    void rx_ClosingWindow_logConfig();
    void rx_ClosingWindow_graphWin();
    void rx_ClosingWindow_ConfigCHWin();

private slots:
    void on_timer_generateGUI_Elapsed();
    void on_timer_SingleShot_elapsed();

private:
    FirstWindow *firstWin;
    MainWindow *logConfig;
    graphWin *GraphW;
    ConfigChWin *configCH;

    QTimer *timer_generateGUI;
    QTimer *timer_SingleShots;
    int index_singleShot = 0;

    void GUIobjectInitializer();

    loggerThread *loggerClass;
    QThread *thrd;
    graphWin *grphW;

    GUI_WIN local_generateGUI = gui_FIRST_WIN;
};

#endif // MAINHANDLER_H
