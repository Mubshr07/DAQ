#include "mainhandler.h"

MainHandler::MainHandler(QObject *parent) : QObject(parent)
{

    //qDebug()<<" debug 2";
    loggerClass = new loggerThread();
    thrd = new QThread(loggerClass);
    loggerClass->moveToThread(thrd);
    thrd->start();

    //qDebug()<<" debug 3";

    timer_SingleShots = new QTimer();
    index_singleShot = 0;
    connect(timer_SingleShots, SIGNAL(timeout()), SLOT(on_timer_SingleShot_elapsed()));
    timer_SingleShots->setSingleShot(true);

    //qDebug()<<" debug 4";

    timer_generateGUI = new QTimer();
    connect(timer_generateGUI, SIGNAL(timeout()), SLOT(on_timer_generateGUI_Elapsed()));
    timer_generateGUI->setSingleShot(true);;
    //qDebug()<<" debug 5";

}
void MainHandler::initial_Start()
{
    timer_SingleShots->start(300);
}

void MainHandler::on_timer_SingleShot_elapsed()
{
    qDebug()<<" Single Shot elapsed ";
    switch (index_singleShot) {
    case 0: {
        GUIobjectInitializer();
        //generate_firstWindow();
        //generate_ConfigCHWin();
        generate_logConfig();
        break;
    }
    }

}
void MainHandler::on_timer_generateGUI_Elapsed()
{
    qDebug()<<" \t\t Timer generateGUI elapsed :: " <<local_generateGUI;
    switch (local_generateGUI) {
    case gui_CONFIG_CH_WIN: {
        generate_ConfigCHWin();
        break;
    }
    case gui_CONFIRMATION_WIN: {

        break;
    }
    case gui_FIRST_WIN: {
        //qDebug()<<" First Window Switch Statement"<<firstWin->isWidgetType();
        //firstWin->show();
        if(firstWin == nullptr ) generate_firstWindow();
        else firstWin->show();
        break;
    }
    case gui_GRAPH_WIN: {
        generate_graphWin();
        break;
    }
    case gui_LOG_CONFIG_WIN: {
        generate_logConfig();
        break;
    }
    case gui_DEBUG_WIN: {
        generate_DebugWin();
        break;
    }
    } // end of Switch statement
}
void MainHandler::rx_generate_ThisGUI(GUI_WIN guiEnum)
{
    qDebug()<<" Singal Received genrate_ThisGUI:: "<<guiEnum;
    local_generateGUI = guiEnum;
    timer_generateGUI->start(100);
}





void MainHandler::generate_firstWindow()
{
    firstWin = new FirstWindow();
    connect(firstWin, SIGNAL(tx_generate_ThisGUI(GUI_WIN)), this, SLOT(rx_generate_ThisGUI(GUI_WIN)));
    connect(firstWin, SIGNAL(tx_ClosingWindow_FirstWin(bool)), this, SLOT(rx_ClosingWindow_FirstWin(bool)));
    firstWin->setModal(true);
    firstWin->show();
}
void MainHandler::generate_logConfig()
{
    logConfig = new MainWindow();
    connect(loggerClass, SIGNAL(tx_channel_Value(int,uint32_t,float,float)), logConfig, SLOT(rx_ChannelValue(int,uint32_t,float,float)));
    connect(logConfig, SIGNAL(tx_setChannelEnable(int, bool)), loggerClass, SLOT(rx_setChannelEnableDisable(int, bool)));
    connect(logConfig, SIGNAL(tx_setSampleTime(int)), loggerClass, SLOT(rx_setSampleTime(int)));

    connect(logConfig, SIGNAL(tx_sendFactorsAndPGAs_AllChnls()), loggerClass, SLOT(rx_sendFactorsAndPGAs_AllChnls()));
    connect(loggerClass, SIGNAL(tx_sendingFactorsAndPGAs(int, float, float, bool)), logConfig, SLOT(rx_sendingFactorsAndPGAs(int, float, float, bool)));

    connect(logConfig, SIGNAL(tx_loggingStartStop(bool, QString)), loggerClass, SLOT(rx_loggingStartStop(bool, QString)));
    connect(loggerClass, SIGNAL(tx_ramdomOP(int,float, QString)), logConfig, SLOT(rx_ramdomOP(int,float, QString)));

    connect(logConfig, SIGNAL(tx_ClosingWindow_logConfig()), this, SLOT(rx_ClosingWindow_logConfig()));
    connect(logConfig, SIGNAL(tx_generate_ThisGUI(GUI_WIN)), this, SLOT(rx_generate_ThisGUI(GUI_WIN)));
    logConfig->show();
}
void MainHandler::generate_graphWin()
{
    grphW = new graphWin();
    connect(grphW, SIGNAL(tx_GraphWindowIsOpen(bool)), loggerClass, SLOT(rx_GraphWindowIsOpen(bool)));
    connect(grphW, SIGNAL(tx_AddNewChannelToGraph(int, int)), loggerClass, SLOT(rx_AddNewChannelToGraph(int, int)));
    connect(grphW, SIGNAL(tx_RemoveChannelToGraph(int, int)), loggerClass, SLOT(rx_RemoveChannelToGraph(int, int)));
    connect(grphW, SIGNAL(tx_giveMeEnablesChannels()), loggerClass, SLOT(rx_giveMeEnablesChannels()));
    //connect(grphW, SIGNAL(tx_loggingStartStop(bool, QString)), loggerClass, SLOT(rx_loggingStartStop(bool, QString)));
    //connect(grphW, SIGNAL(tx_generate_ThisGUI(GUI_WIN)), this, SLOT(rx_generate_ThisGUI(GUI_WIN)));
    connect(grphW, SIGNAL(tx_ClosingWindow_graphWin()), this, SLOT(rx_ClosingWindow_graphWin()));

    connect(loggerClass, SIGNAL(tx_EnableChannelsAre(int)), grphW, SLOT(rx_EnableChannelsAre(int)));
    connect(loggerClass, SIGNAL(tx_GraphChannelValue(int,int,float)), grphW, SLOT(rx_GraphChannelValue(int,int,float)));
    connect(loggerClass, SIGNAL(tx_ramdomOP(int,float, QString)), grphW, SLOT(rx_ramdomOP(int,float, QString)));


    grphW->setModal(true);
    grphW->show();
}
void MainHandler::generate_ConfigCHWin()
{

    configCH = new ConfigChWin();

    connect(configCH, SIGNAL(tx_setChannelNewSettings(int,float,CHANNEL_PGA,CHANNEL_TYPE,CHANNEL_REFERENCE, bool)), loggerClass, SLOT(rx_setChannelNewSettings(int,float,CHANNEL_PGA,CHANNEL_TYPE,CHANNEL_REFERENCE, bool)));
    connect(configCH, SIGNAL(tx_ClosingWindow_ConfigCHWin()), this, SLOT(rx_ClosingWindow_ConfigCHWin()));
    connect(configCH, SIGNAL(tx_generate_ThisGUI(GUI_WIN)), this, SLOT(rx_generate_ThisGUI(GUI_WIN)));
    connect(configCH, SIGNAL(tx_giveMechannelSettings(int)), loggerClass, SLOT(rx_giveMechannelSettings(int)));
    connect(configCH, SIGNAL(tx_ChannelSettingsWindowIsOpen(bool)), loggerClass, SLOT(rx_ChannelSettingsWindowIsOpen(bool)));
    connect(configCH, SIGNAL(tx_startReadingTimer(bool)), loggerClass, SLOT(rx_startReadingTimer(bool)));

    connect(configCH, SIGNAL(tx_setSampleTime(int)), loggerClass, SLOT(rx_setSampleTime(int)));

    connect(loggerClass, SIGNAL(tx_EnableChannelsAre(int)), configCH, SLOT(rx_EnableChannelsAre(int)));
    connect(loggerClass, SIGNAL(tx_ramdomOP(int,float, QString)), configCH, SLOT(rx_ramdomOP(int,float, QString)));
    connect(loggerClass, SIGNAL(tx_ChannelOLDSettings(int,float,CHANNEL_PGA,CHANNEL_TYPE,CHANNEL_REFERENCE, bool)), configCH, SLOT(rx_ChannelOLDSettings(int,float,CHANNEL_PGA,CHANNEL_TYPE,CHANNEL_REFERENCE, bool)));
    connect(loggerClass, SIGNAL(tx_channel_Value(int, uint32_t, float,float)), configCH, SLOT(rx_ChannelValue(int, uint32_t, float,float)));

    configCH->setModal(true);
    configCH->show();
}
void MainHandler::generate_DebugWin()
{
    debgWn = new NewDebug();

//    connect(configCH, SIGNAL(tx_setChannelNewSettings(int,float,float,CHANNEL_TYPE,CHANNEL_REFERENCE)), loggerClass, SLOT(rx_setChannelNewSettings(int,float,float,CHANNEL_TYPE,CHANNEL_REFERENCE)));
        connect(debgWn, SIGNAL(tx_ClosingWindow_DebugWin()), this, SLOT(rx_ClosingWindow_DebugWin()));
        connect(debgWn, SIGNAL(tx_generate_ThisGUI(GUI_WIN)), this, SLOT(rx_generate_ThisGUI(GUI_WIN)));


    debgWn->setModal(true);
    debgWn->show();
}

// ----------------- Closing Windows --------------------
void MainHandler::rx_ClosingWindow_FirstWin(bool shutDown)
{
    qDebug()<<" First Window is CLosed ::"<<shutDown;
    firstWin->hide();

    if(shutDown) {
        QCoreApplication::quit();
    }
}
void MainHandler::rx_ClosingWindow_logConfig()
{
    qDebug()<<" LogConfig Window is CLosed ";
    logConfig->hide();
}
void MainHandler::rx_ClosingWindow_graphWin()
{
    qDebug()<<" GraphWindow Window is CLosed ";
    //grphW->hide();
    grphW->~graphWin();
    grphW = nullptr;
}
void MainHandler::rx_ClosingWindow_ConfigCHWin()
{
    qDebug()<<" Conifg Channel Window is CLosed ";
    //configCH->hide();
    configCH->~ConfigChWin();
    configCH = nullptr;
}
void MainHandler::rx_ClosingWindow_DebugWin()
{
    qDebug()<<" Debug Window is CLosed ";
    debgWn->hide();
}

void MainHandler::GUIobjectInitializer()
{


}

