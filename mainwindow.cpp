#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(1024, 768);

    this->setWindowFlags(Qt::FramelessWindowHint);
    //this->setWindowState(Qt::WindowFullScreen);
    //this->setWindowFlag(Qt::WindowStaysOnTopHint);
    this->setAttribute(Qt::WA_DeleteOnClose, true); //so that it will be deleted when closed


    timer_singleShot= new QTimer(this);
    connect(timer_singleShot, SIGNAL(timeout()), SLOT(on_timer_singleShot_elapsed()));
    timer_singleShot->setSingleShot(true);
    index_SingleShotTimer = 0;
    timer_singleShot->start(50);

    loggerClass = new loggerThread();
    thrd = new QThread(loggerClass);
    loggerClass->moveToThread(thrd);
    connect(loggerClass, SIGNAL(tx_channel_Value(int, float)), this, SLOT(rx_ChannelValue(int, float)));
    connect(this, SIGNAL(tx_setChannelEnable(int, bool)), loggerClass, SLOT(rx_setChannelEnableDisable(int, bool)));
    connect(this, SIGNAL(tx_setSampleTime(int)), loggerClass, SLOT(rx_setSampleTime(int)));
    thrd->start();


    timer_enabler = new QTimer(this);
    connect(timer_enabler, SIGNAL(timeout()), SLOT(on_timer_enabler_elapsed()));
    timer_enabler->setInterval(100);
    timer_enabler->start();
    index_SingleShotTimer = 0;
    for(int i=0; i<TOTAL_CHANNEL; i++)
    {
        disableLCDNumber(i);
    }




}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pb_SetConfiguration_clicked()
{
    grphW = new graphWin();
    connect(grphW, SIGNAL(tx_GraphWindowIsOpen(bool)), loggerClass, SLOT(rx_GraphWindowIsOpen(bool)));
    connect(grphW, SIGNAL(tx_AddNewChannelToGraph(int, int)), loggerClass, SLOT(rx_AddNewChannelToGraph(int, int)));
    connect(grphW, SIGNAL(tx_RemoveChannelToGraph(int, int)), loggerClass, SLOT(rx_RemoveChannelToGraph(int, int)));
    connect(grphW, SIGNAL(tx_giveMeEnablesChannels()), loggerClass, SLOT(rx_giveMeEnablesChannels()));

    connect(loggerClass, SIGNAL(tx_EnableChannelsAre(int)), grphW, SLOT(rx_EnableChannelsAre(int)));
    connect(loggerClass, SIGNAL(tx_GraphChannelValue(int,int,float)), grphW, SLOT(rx_GraphChannelValue(int,int,float)));




    grphW->setModal(true);
    grphW->exec();

}



void MainWindow::rx_ChannelValue(int chnl, float val)
{
    //qDebug()<<" Value Received : Chnnel = "<<chnl<<" value = "<<val;
    switch (chnl) {
    case 0: {ui->lbl_lcdNumber_0->display(QString::number(val, 'f', lcdNumberPrecision)); break; }
    case 1: { ui->lbl_lcdNumber_1->display(QString::number(val, 'f', lcdNumberPrecision)); break; }
    case 2: { ui->lbl_lcdNumber_2->display(QString::number(val, 'f', lcdNumberPrecision)); break; }
    case 3: { ui->lbl_lcdNumber_3->display(QString::number(val, 'f', lcdNumberPrecision)); break; }
    case 4: { ui->lbl_lcdNumber_4->display(QString::number(val, 'f', lcdNumberPrecision)); break; }
    case 5: { ui->lbl_lcdNumber_5->display(QString::number(val, 'f', lcdNumberPrecision)); break; }
    case 6: { ui->lbl_lcdNumber_6->display(QString::number(val, 'f', lcdNumberPrecision)); break; }
    case 7: { ui->lbl_lcdNumber_7->display(QString::number(val, 'f', lcdNumberPrecision)); break; }
    case 8: { ui->lbl_lcdNumber_8->display(QString::number(val, 'f', lcdNumberPrecision)); break; }
    case 9: { ui->lbl_lcdNumber_9->display(QString::number(val, 'f', lcdNumberPrecision)); break; }
    case 10: { ui->lbl_lcdNumber_10->display(QString::number(val, 'f', lcdNumberPrecision)); break; }
    case 11: { ui->lbl_lcdNumber_11->display(QString::number(val, 'f', lcdNumberPrecision)); break; }

    case 12: { ui->lbl_lcdNumber_12->display(QString::number(val, 'f', lcdNumberPrecision)); break; }
    case 13: { ui->lbl_lcdNumber_13->display(QString::number(val, 'f', lcdNumberPrecision)); break; }
    case 14: { ui->lbl_lcdNumber_14->display(QString::number(val, 'f', lcdNumberPrecision)); break; }
    case 15: { ui->lbl_lcdNumber_15->display(QString::number(val, 'f', lcdNumberPrecision)); break; }
    case 16: { ui->lbl_lcdNumber_16->display(QString::number(val, 'f', lcdNumberPrecision)); break; }
    case 17: { ui->lbl_lcdNumber_17->display(QString::number(val, 'f', lcdNumberPrecision)); break; }
    case 18: { ui->lbl_lcdNumber_18->display(QString::number(val, 'f', lcdNumberPrecision)); break; }
    case 19: { ui->lbl_lcdNumber_19->display(QString::number(val, 'f', lcdNumberPrecision)); break; }
    case 20: { ui->lbl_lcdNumber_20->display(QString::number(val, 'f', lcdNumberPrecision)); break; }
    case 21: { ui->lbl_lcdNumber_21->display(QString::number(val, 'f', lcdNumberPrecision)); break; }

    case 22: { ui->lbl_lcdNumber_22->display(QString::number(val, 'f', lcdNumberPrecision)); break; }
    case 23: { ui->lbl_lcdNumber_23->display(QString::number(val, 'f', lcdNumberPrecision)); break; }
    case 24: { ui->lbl_lcdNumber_24->display(QString::number(val, 'f', lcdNumberPrecision)); break; }
    case 25: { ui->lbl_lcdNumber_25->display(QString::number(val, 'f', lcdNumberPrecision)); break; }
    case 26: { ui->lbl_lcdNumber_26->display(QString::number(val, 'f', lcdNumberPrecision)); break; }
    case 27: { ui->lbl_lcdNumber_27->display(QString::number(val, 'f', lcdNumberPrecision)); break; }
    case 28: { ui->lbl_lcdNumber_28->display(QString::number(val, 'f', lcdNumberPrecision)); break; }
    case 29: { ui->lbl_lcdNumber_29->display(QString::number(val, 'f', lcdNumberPrecision)); break; }
    case 30: { ui->lbl_lcdNumber_30->display(QString::number(val, 'f', lcdNumberPrecision)); break; }
    case 31: { ui->lbl_lcdNumber_31->display(QString::number(val, 'f', lcdNumberPrecision)); break; }

    case 32: { ui->lbl_lcdNumber_32->display(QString::number(val, 'f', lcdNumberPrecision)); break; }
    case 33: { ui->lbl_lcdNumber_33->display(QString::number(val, 'f', lcdNumberPrecision)); break; }
    case 34: { ui->lbl_lcdNumber_34->display(QString::number(val, 'f', lcdNumberPrecision)); break; }
    case 35: { ui->lbl_lcdNumber_35->display(QString::number(val, 'f', lcdNumberPrecision)); break; }
    case 36: { ui->lbl_lcdNumber_36->display(QString::number(val, 'f', lcdNumberPrecision)); break; }
    case 37: { ui->lbl_lcdNumber_37->display(QString::number(val, 'f', lcdNumberPrecision)); break; }
    case 38: { ui->lbl_lcdNumber_38->display(QString::number(val, 'f', lcdNumberPrecision)); break; }
    case 39: { ui->lbl_lcdNumber_39->display(QString::number(val, 'f', lcdNumberPrecision)); break; }
    case 40: { ui->lbl_lcdNumber_40->display(QString::number(val, 'f', lcdNumberPrecision)); break; }
    case 41: { ui->lbl_lcdNumber_41->display(QString::number(val, 'f', lcdNumberPrecision)); break; }

    case 42: { ui->lbl_lcdNumber_42->display(QString::number(val, 'f', lcdNumberPrecision)); break; }
    case 43: { ui->lbl_lcdNumber_43->display(QString::number(val, 'f', lcdNumberPrecision)); break; }
    case 44: { ui->lbl_lcdNumber_44->display(QString::number(val, 'f', lcdNumberPrecision)); break; }
    case 45: { ui->lbl_lcdNumber_45->display(QString::number(val, 'f', lcdNumberPrecision)); break; }
    case 46: { ui->lbl_lcdNumber_46->display(QString::number(val, 'f', lcdNumberPrecision)); break; }
    case 47: { ui->lbl_lcdNumber_47->display(QString::number(val, 'f', lcdNumberPrecision)); break; }

    } // end of Switch statement
}

void MainWindow::on_pb_Channel_Clicked()
{
    QPushButton *button = (QPushButton *)sender();
    QString accessName = button->accessibleName();


    accessibleName_int = 0;
    okVariable = false;
    accessibleName_int = accessName.toInt(&okVariable, 10);

    //qDebug()<<accessName<<" Button Clicked = "<<accessibleName_int<<" checked: "<<button->property("isEnable");

    if(okVariable)
    {
        if(button->isChecked())
        {
            emit tx_setChannelEnable(accessibleName_int, true);
            button->setStyleSheet(style_pbChnl_Enable);
        }
        else
        {
            disableLCDNumber(accessibleName_int);
            emit tx_setChannelEnable(accessibleName_int, false);
            button->setStyleSheet(style_pbChnl_Disable);
        }
    }
    else
    {
        qDebug()<<" Error in parsing accessible Name of pressed PushButton ";
    }
}


void MainWindow::on_timer_singleShot_elapsed()
{
    switch (index_SingleShotTimer) {
    case 0:{
        connectAllButtonsClickToSingleSlot();

        break;
    }
    case 1:{

        break;
    }
    case 2:{

        break;
    }
    case 3:{

        break;
    }
    }
}
void MainWindow::on_timer_enabler_elapsed()
{
    if(index_Enabler == 0 ) timer_enabler->setInterval(100);


    switch (index_Enabler) {
    case 0: {
        ui->pb_channel_0->setChecked(true); ui->pb_channel_0->clicked();
        ui->pb_channel_12->setChecked(true); ui->pb_channel_12->clicked();
        ui->pb_channel_24->setChecked(true); ui->pb_channel_24->clicked();
        ui->pb_channel_36->setChecked(true); ui->pb_channel_36->clicked();
        break; }
    case 1: {
        ui->pb_channel_1->setChecked(true); ui->pb_channel_1->clicked();
        ui->pb_channel_13->setChecked(true); ui->pb_channel_13->clicked();
        ui->pb_channel_25->setChecked(true); ui->pb_channel_25->clicked();
        ui->pb_channel_37->setChecked(true); ui->pb_channel_37->clicked();
        break; }
    case 2: {
        ui->pb_channel_2->setChecked(true); ui->pb_channel_2->clicked();
        ui->pb_channel_14->setChecked(true); ui->pb_channel_14->clicked();
        ui->pb_channel_26->setChecked(true); ui->pb_channel_26->clicked();
        ui->pb_channel_38->setChecked(true); ui->pb_channel_38->clicked();
        break; }
    case 3: {
        ui->pb_channel_3->setChecked(true); ui->pb_channel_3->clicked();
        ui->pb_channel_15->setChecked(true); ui->pb_channel_15->clicked();
        ui->pb_channel_27->setChecked(true); ui->pb_channel_27->clicked();
        ui->pb_channel_39->setChecked(true); ui->pb_channel_39->clicked();
        break; }
    case 4: {
        ui->pb_channel_4->setChecked(true); ui->pb_channel_4->clicked();
        ui->pb_channel_16->setChecked(true); ui->pb_channel_16->clicked();
        ui->pb_channel_28->setChecked(true); ui->pb_channel_28->clicked();
        ui->pb_channel_40->setChecked(true); ui->pb_channel_40->clicked();
        break; }
    case 5: {
        ui->pb_channel_5->setChecked(true); ui->pb_channel_5->clicked();
        ui->pb_channel_17->setChecked(true); ui->pb_channel_17->clicked();
        ui->pb_channel_29->setChecked(true); ui->pb_channel_29->clicked();
        ui->pb_channel_41->setChecked(true); ui->pb_channel_41->clicked();
        break; }
    case 6: {
        ui->pb_channel_6->setChecked(true); ui->pb_channel_6->clicked();
        ui->pb_channel_18->setChecked(true); ui->pb_channel_18->clicked();
        ui->pb_channel_30->setChecked(true); ui->pb_channel_30->clicked();
        ui->pb_channel_42->setChecked(true); ui->pb_channel_42->clicked();
        break; }
    case 7: {
        ui->pb_channel_7->setChecked(true); ui->pb_channel_7->clicked();
        ui->pb_channel_19->setChecked(true); ui->pb_channel_19->clicked();
        ui->pb_channel_31->setChecked(true); ui->pb_channel_31->clicked();
        ui->pb_channel_43->setChecked(true); ui->pb_channel_43->clicked();
        break; }
    case 8: {
        ui->pb_channel_8->setChecked(true); ui->pb_channel_8->clicked();
        ui->pb_channel_20->setChecked(true); ui->pb_channel_20->clicked();
        ui->pb_channel_32->setChecked(true); ui->pb_channel_32->clicked();
        ui->pb_channel_44->setChecked(true); ui->pb_channel_44->clicked();
        break; }
    case 9: {
        ui->pb_channel_9->setChecked(true); ui->pb_channel_9->clicked();
        ui->pb_channel_21->setChecked(true); ui->pb_channel_21->clicked();
        ui->pb_channel_33->setChecked(true); ui->pb_channel_33->clicked();
        ui->pb_channel_45->setChecked(true); ui->pb_channel_45->clicked();
        break; }
    case 10: {
        ui->pb_channel_10->setChecked(true); ui->pb_channel_10->clicked();
        ui->pb_channel_22->setChecked(true); ui->pb_channel_22->clicked();
        ui->pb_channel_34->setChecked(true); ui->pb_channel_34->clicked();
        ui->pb_channel_46->setChecked(true); ui->pb_channel_46->clicked();
        break; }
    case 11: {
        ui->pb_channel_11->setChecked(true); ui->pb_channel_11->clicked();
        ui->pb_channel_23->setChecked(true); ui->pb_channel_23->clicked();
        ui->pb_channel_35->setChecked(true); ui->pb_channel_35->clicked();
        ui->pb_channel_47->setChecked(true); ui->pb_channel_47->clicked();
        break; }

    } // end of Switch statement

    /*
    switch (index_Enabler) {
    case 0: { ui->pb_channel_0->setChecked(true); ui->pb_channel_0->clicked();  break; }
    case 1: { ui->pb_channel_1->setChecked(true); ui->pb_channel_1->clicked(); break; }
    case 2: { ui->pb_channel_2->setChecked(true); ui->pb_channel_2->clicked(); break; }
    case 3: { ui->pb_channel_3->setChecked(true); ui->pb_channel_3->clicked(); break; }
    case 4: { ui->pb_channel_4->setChecked(true); ui->pb_channel_4->clicked(); break; }
    case 5: { ui->pb_channel_5->setChecked(true); ui->pb_channel_5->clicked(); break; }
    case 6: { ui->pb_channel_6->setChecked(true); ui->pb_channel_6->clicked(); break; }
    case 7: { ui->pb_channel_7->setChecked(true); ui->pb_channel_7->clicked(); break; }
    case 8: { ui->pb_channel_8->setChecked(true); ui->pb_channel_8->clicked(); break; }
    case 9: { ui->pb_channel_9->setChecked(true); ui->pb_channel_9->clicked(); break; }
    case 10: { ui->pb_channel_10->setChecked(true); ui->pb_channel_10->clicked(); break; }
    case 11: { ui->pb_channel_11->setChecked(true); ui->pb_channel_11->clicked(); break; }

    case 12: { ui->pb_channel_12->setChecked(true); ui->pb_channel_12->clicked(); break; }
    case 13: { ui->pb_channel_13->setChecked(true); ui->pb_channel_13->clicked(); break; }
    case 14: { ui->pb_channel_14->setChecked(true); ui->pb_channel_14->clicked(); break; }
    case 15: { ui->pb_channel_15->setChecked(true); ui->pb_channel_15->clicked(); break; }
    case 16: { ui->pb_channel_16->setChecked(true); ui->pb_channel_16->clicked(); break; }
    case 17: { ui->pb_channel_17->setChecked(true); ui->pb_channel_17->clicked(); break; }
    case 18: { ui->pb_channel_18->setChecked(true); ui->pb_channel_18->clicked(); break; }
    case 19: { ui->pb_channel_19->setChecked(true); ui->pb_channel_19->clicked(); break; }
    case 20: { ui->pb_channel_20->setChecked(true); ui->pb_channel_20->clicked(); break; }
    case 21: { ui->pb_channel_21->setChecked(true); ui->pb_channel_21->clicked(); break; }

    case 22: { ui->pb_channel_22->setChecked(true); ui->pb_channel_22->clicked(); break; }
    case 23: { ui->pb_channel_23->setChecked(true); ui->pb_channel_23->clicked(); break; }
    case 24: { ui->pb_channel_24->setChecked(true); ui->pb_channel_24->clicked(); break; }
    case 25: { ui->pb_channel_25->setChecked(true); ui->pb_channel_25->clicked(); break; }
    case 26: { ui->pb_channel_26->setChecked(true); ui->pb_channel_26->clicked(); break; }
    case 27: { ui->pb_channel_27->setChecked(true); ui->pb_channel_27->clicked(); break; }
    case 28: { ui->pb_channel_28->setChecked(true); ui->pb_channel_28->clicked(); break; }
    case 29: { ui->pb_channel_29->setChecked(true); ui->pb_channel_29->clicked(); break; }
    case 30: { ui->pb_channel_30->setChecked(true); ui->pb_channel_30->clicked(); break; }
    case 31: { ui->pb_channel_31->setChecked(true); ui->pb_channel_31->clicked(); break; }

    case 32: { ui->pb_channel_32->setChecked(true); ui->pb_channel_32->clicked(); break; }
    case 33: { ui->pb_channel_33->setChecked(true); ui->pb_channel_33->clicked(); break; }
    case 34: { ui->pb_channel_34->setChecked(true); ui->pb_channel_34->clicked(); break; }
    case 35: { ui->pb_channel_35->setChecked(true); ui->pb_channel_35->clicked(); break; }
    case 36: { ui->pb_channel_36->setChecked(true); ui->pb_channel_36->clicked(); break; }
    case 37: { ui->pb_channel_37->setChecked(true); ui->pb_channel_37->clicked(); break; }
    case 38: { ui->pb_channel_38->setChecked(true); ui->pb_channel_38->clicked(); break; }
    case 39: { ui->pb_channel_39->setChecked(true); ui->pb_channel_39->clicked(); break; }
    case 40: { ui->pb_channel_40->setChecked(true); ui->pb_channel_40->clicked(); break; }
    case 41: { ui->pb_channel_41->setChecked(true); ui->pb_channel_41->clicked(); break; }

    case 42: { ui->pb_channel_42->setChecked(true); ui->pb_channel_42->clicked(); break; }
    case 43: { ui->pb_channel_43->setChecked(true); ui->pb_channel_43->clicked(); break; }
    case 44: { ui->pb_channel_44->setChecked(true); ui->pb_channel_44->clicked(); break; }
    case 45: { ui->pb_channel_45->setChecked(true); ui->pb_channel_45->clicked(); break; }
    case 46: { ui->pb_channel_46->setChecked(true); ui->pb_channel_46->clicked(); break; }
    case 47: { ui->pb_channel_47->setChecked(true); ui->pb_channel_47->clicked(); break; }
    } */



    // ---------------------------------------
    index_Enabler++;
    if(index_Enabler >= TOTAL_CHANNEL)
    {
        index_SingleShotTimer = 0;
        timer_enabler->stop();
    }
}

void MainWindow::connectAllButtonsClickToSingleSlot()
{
    //qDebug()<<" starting button signal slots ";
    connect(ui->pb_channel_0, SIGNAL(clicked()), SLOT(on_pb_Channel_Clicked()));
    connect(ui->pb_channel_1, SIGNAL(clicked()), SLOT(on_pb_Channel_Clicked()));
    connect(ui->pb_channel_2, SIGNAL(clicked()), SLOT(on_pb_Channel_Clicked()));
    connect(ui->pb_channel_3, SIGNAL(clicked()), SLOT(on_pb_Channel_Clicked()));
    connect(ui->pb_channel_4, SIGNAL(clicked()), SLOT(on_pb_Channel_Clicked()));
    connect(ui->pb_channel_5, SIGNAL(clicked()), SLOT(on_pb_Channel_Clicked()));
    connect(ui->pb_channel_6, SIGNAL(clicked()), SLOT(on_pb_Channel_Clicked()));
    connect(ui->pb_channel_7, SIGNAL(clicked()), SLOT(on_pb_Channel_Clicked()));
    connect(ui->pb_channel_8, SIGNAL(clicked()), SLOT(on_pb_Channel_Clicked()));
    connect(ui->pb_channel_9, SIGNAL(clicked()), SLOT(on_pb_Channel_Clicked()));

    connect(ui->pb_channel_10, SIGNAL(clicked()), SLOT(on_pb_Channel_Clicked()));
    connect(ui->pb_channel_11, SIGNAL(clicked()), SLOT(on_pb_Channel_Clicked()));
    connect(ui->pb_channel_12, SIGNAL(clicked()), SLOT(on_pb_Channel_Clicked()));
    connect(ui->pb_channel_13, SIGNAL(clicked()), SLOT(on_pb_Channel_Clicked()));
    connect(ui->pb_channel_14, SIGNAL(clicked()), SLOT(on_pb_Channel_Clicked()));
    connect(ui->pb_channel_15, SIGNAL(clicked()), SLOT(on_pb_Channel_Clicked()));
    connect(ui->pb_channel_16, SIGNAL(clicked()), SLOT(on_pb_Channel_Clicked()));
    connect(ui->pb_channel_17, SIGNAL(clicked()), SLOT(on_pb_Channel_Clicked()));
    connect(ui->pb_channel_18, SIGNAL(clicked()), SLOT(on_pb_Channel_Clicked()));
    connect(ui->pb_channel_19, SIGNAL(clicked()), SLOT(on_pb_Channel_Clicked()));

    connect(ui->pb_channel_20, SIGNAL(clicked()), SLOT(on_pb_Channel_Clicked()));
    connect(ui->pb_channel_21, SIGNAL(clicked()), SLOT(on_pb_Channel_Clicked()));
    connect(ui->pb_channel_22, SIGNAL(clicked()), SLOT(on_pb_Channel_Clicked()));
    connect(ui->pb_channel_23, SIGNAL(clicked()), SLOT(on_pb_Channel_Clicked()));
    connect(ui->pb_channel_24, SIGNAL(clicked()), SLOT(on_pb_Channel_Clicked()));
    connect(ui->pb_channel_25, SIGNAL(clicked()), SLOT(on_pb_Channel_Clicked()));
    connect(ui->pb_channel_26, SIGNAL(clicked()), SLOT(on_pb_Channel_Clicked()));
    connect(ui->pb_channel_27, SIGNAL(clicked()), SLOT(on_pb_Channel_Clicked()));
    connect(ui->pb_channel_28, SIGNAL(clicked()), SLOT(on_pb_Channel_Clicked()));
    connect(ui->pb_channel_29, SIGNAL(clicked()), SLOT(on_pb_Channel_Clicked()));

    connect(ui->pb_channel_30, SIGNAL(clicked()), SLOT(on_pb_Channel_Clicked()));
    connect(ui->pb_channel_31, SIGNAL(clicked()), SLOT(on_pb_Channel_Clicked()));
    connect(ui->pb_channel_32, SIGNAL(clicked()), SLOT(on_pb_Channel_Clicked()));
    connect(ui->pb_channel_33, SIGNAL(clicked()), SLOT(on_pb_Channel_Clicked()));
    connect(ui->pb_channel_34, SIGNAL(clicked()), SLOT(on_pb_Channel_Clicked()));
    connect(ui->pb_channel_35, SIGNAL(clicked()), SLOT(on_pb_Channel_Clicked()));
    connect(ui->pb_channel_36, SIGNAL(clicked()), SLOT(on_pb_Channel_Clicked()));
    connect(ui->pb_channel_37, SIGNAL(clicked()), SLOT(on_pb_Channel_Clicked()));
    connect(ui->pb_channel_38, SIGNAL(clicked()), SLOT(on_pb_Channel_Clicked()));
    connect(ui->pb_channel_39, SIGNAL(clicked()), SLOT(on_pb_Channel_Clicked()));

    connect(ui->pb_channel_40, SIGNAL(clicked()), SLOT(on_pb_Channel_Clicked()));
    connect(ui->pb_channel_41, SIGNAL(clicked()), SLOT(on_pb_Channel_Clicked()));
    connect(ui->pb_channel_42, SIGNAL(clicked()), SLOT(on_pb_Channel_Clicked()));
    connect(ui->pb_channel_43, SIGNAL(clicked()), SLOT(on_pb_Channel_Clicked()));
    connect(ui->pb_channel_44, SIGNAL(clicked()), SLOT(on_pb_Channel_Clicked()));
    connect(ui->pb_channel_45, SIGNAL(clicked()), SLOT(on_pb_Channel_Clicked()));
    connect(ui->pb_channel_46, SIGNAL(clicked()), SLOT(on_pb_Channel_Clicked()));
    connect(ui->pb_channel_47, SIGNAL(clicked()), SLOT(on_pb_Channel_Clicked()));
    //qDebug()<<" End button signal slots ";

    ui->lbl_lcdNumber_0->setPalette(lcdNumber_colorPallet);
    ui->lbl_lcdNumber_1->setPalette(lcdNumber_colorPallet);
    ui->lbl_lcdNumber_2->setPalette(lcdNumber_colorPallet);
    ui->lbl_lcdNumber_3->setPalette(lcdNumber_colorPallet);
    ui->lbl_lcdNumber_4->setPalette(lcdNumber_colorPallet);
    ui->lbl_lcdNumber_5->setPalette(lcdNumber_colorPallet);
    ui->lbl_lcdNumber_6->setPalette(lcdNumber_colorPallet);
    ui->lbl_lcdNumber_7->setPalette(lcdNumber_colorPallet);
    ui->lbl_lcdNumber_8->setPalette(lcdNumber_colorPallet);
    ui->lbl_lcdNumber_9->setPalette(lcdNumber_colorPallet);

    ui->lbl_lcdNumber_10->setPalette(lcdNumber_colorPallet);
    ui->lbl_lcdNumber_11->setPalette(lcdNumber_colorPallet);
    ui->lbl_lcdNumber_12->setPalette(lcdNumber_colorPallet);
    ui->lbl_lcdNumber_13->setPalette(lcdNumber_colorPallet);
    ui->lbl_lcdNumber_14->setPalette(lcdNumber_colorPallet);
    ui->lbl_lcdNumber_15->setPalette(lcdNumber_colorPallet);
    ui->lbl_lcdNumber_16->setPalette(lcdNumber_colorPallet);
    ui->lbl_lcdNumber_17->setPalette(lcdNumber_colorPallet);
    ui->lbl_lcdNumber_18->setPalette(lcdNumber_colorPallet);
    ui->lbl_lcdNumber_19->setPalette(lcdNumber_colorPallet);

    ui->lbl_lcdNumber_20->setPalette(lcdNumber_colorPallet);
    ui->lbl_lcdNumber_21->setPalette(lcdNumber_colorPallet);
    ui->lbl_lcdNumber_22->setPalette(lcdNumber_colorPallet);
    ui->lbl_lcdNumber_23->setPalette(lcdNumber_colorPallet);
    ui->lbl_lcdNumber_24->setPalette(lcdNumber_colorPallet);
    ui->lbl_lcdNumber_25->setPalette(lcdNumber_colorPallet);
    ui->lbl_lcdNumber_26->setPalette(lcdNumber_colorPallet);
    ui->lbl_lcdNumber_27->setPalette(lcdNumber_colorPallet);
    ui->lbl_lcdNumber_28->setPalette(lcdNumber_colorPallet);
    ui->lbl_lcdNumber_29->setPalette(lcdNumber_colorPallet);

    ui->lbl_lcdNumber_30->setPalette(lcdNumber_colorPallet);
    ui->lbl_lcdNumber_31->setPalette(lcdNumber_colorPallet);
    ui->lbl_lcdNumber_32->setPalette(lcdNumber_colorPallet);
    ui->lbl_lcdNumber_33->setPalette(lcdNumber_colorPallet);
    ui->lbl_lcdNumber_34->setPalette(lcdNumber_colorPallet);
    ui->lbl_lcdNumber_35->setPalette(lcdNumber_colorPallet);
    ui->lbl_lcdNumber_36->setPalette(lcdNumber_colorPallet);
    ui->lbl_lcdNumber_37->setPalette(lcdNumber_colorPallet);
    ui->lbl_lcdNumber_38->setPalette(lcdNumber_colorPallet);
    ui->lbl_lcdNumber_39->setPalette(lcdNumber_colorPallet);

    ui->lbl_lcdNumber_40->setPalette(lcdNumber_colorPallet);
    ui->lbl_lcdNumber_41->setPalette(lcdNumber_colorPallet);
    ui->lbl_lcdNumber_42->setPalette(lcdNumber_colorPallet);
    ui->lbl_lcdNumber_43->setPalette(lcdNumber_colorPallet);
    ui->lbl_lcdNumber_44->setPalette(lcdNumber_colorPallet);
    ui->lbl_lcdNumber_45->setPalette(lcdNumber_colorPallet);
    ui->lbl_lcdNumber_46->setPalette(lcdNumber_colorPallet);
    ui->lbl_lcdNumber_47->setPalette(lcdNumber_colorPallet);


}
void MainWindow::disableLCDNumber(int indx)
{
    switch (indx) {
    case 0: {ui->lbl_lcdNumber_0->display(""); break; }
    case 1: { ui->lbl_lcdNumber_1->display(""); break; }
    case 2: { ui->lbl_lcdNumber_2->display(""); break; }
    case 3: { ui->lbl_lcdNumber_3->display(""); break; }
    case 4: { ui->lbl_lcdNumber_4->display(""); break; }
    case 5: { ui->lbl_lcdNumber_5->display(""); break; }
    case 6: { ui->lbl_lcdNumber_6->display(""); break; }
    case 7: { ui->lbl_lcdNumber_7->display(""); break; }
    case 8: { ui->lbl_lcdNumber_8->display(""); break; }
    case 9: { ui->lbl_lcdNumber_9->display(""); break; }
    case 10: { ui->lbl_lcdNumber_10->display(""); break; }
    case 11: { ui->lbl_lcdNumber_11->display(""); break; }

    case 12: { ui->lbl_lcdNumber_12->display(""); break; }
    case 13: { ui->lbl_lcdNumber_13->display(""); break; }
    case 14: { ui->lbl_lcdNumber_14->display(""); break; }
    case 15: { ui->lbl_lcdNumber_15->display(""); break; }
    case 16: { ui->lbl_lcdNumber_16->display(""); break; }
    case 17: { ui->lbl_lcdNumber_17->display(""); break; }
    case 18: { ui->lbl_lcdNumber_18->display(""); break; }
    case 19: { ui->lbl_lcdNumber_19->display(""); break; }
    case 20: { ui->lbl_lcdNumber_20->display(""); break; }
    case 21: { ui->lbl_lcdNumber_21->display(""); break; }

    case 22: { ui->lbl_lcdNumber_22->display(""); break; }
    case 23: { ui->lbl_lcdNumber_23->display(""); break; }
    case 24: { ui->lbl_lcdNumber_24->display(""); break; }
    case 25: { ui->lbl_lcdNumber_25->display(""); break; }
    case 26: { ui->lbl_lcdNumber_26->display(""); break; }
    case 27: { ui->lbl_lcdNumber_27->display(""); break; }
    case 28: { ui->lbl_lcdNumber_28->display(""); break; }
    case 29: { ui->lbl_lcdNumber_29->display(""); break; }
    case 30: { ui->lbl_lcdNumber_30->display(""); break; }
    case 31: { ui->lbl_lcdNumber_31->display(""); break; }

    case 32: { ui->lbl_lcdNumber_32->display(""); break; }
    case 33: { ui->lbl_lcdNumber_33->display(""); break; }
    case 34: { ui->lbl_lcdNumber_34->display(""); break; }
    case 35: { ui->lbl_lcdNumber_35->display(""); break; }
    case 36: { ui->lbl_lcdNumber_36->display(""); break; }
    case 37: { ui->lbl_lcdNumber_37->display(""); break; }
    case 38: { ui->lbl_lcdNumber_38->display(""); break; }
    case 39: { ui->lbl_lcdNumber_39->display(""); break; }
    case 40: { ui->lbl_lcdNumber_40->display(""); break; }
    case 41: { ui->lbl_lcdNumber_41->display(""); break; }

    case 42: { ui->lbl_lcdNumber_42->display(""); break; }
    case 43: { ui->lbl_lcdNumber_43->display(""); break; }
    case 44: { ui->lbl_lcdNumber_44->display(""); break; }
    case 45: { ui->lbl_lcdNumber_45->display(""); break; }
    case 46: { ui->lbl_lcdNumber_46->display(""); break; }
    case 47: { ui->lbl_lcdNumber_47->display(""); break; }

    } // end of Switch statement
}

void MainWindow::on_pb_CloseApp_clicked()
{
    QCoreApplication::quit();
}
