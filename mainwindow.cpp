#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //this->setFixedSize(1024, 768);

    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setWindowState(Qt::WindowFullScreen);
    //this->setWindowFlag(Qt::WindowStaysOnTopHint);
    this->setAttribute(Qt::WA_DeleteOnClose, true); //so that it will be deleted when closed

    //qDebug()<<" debug 1";
    timer_singleShot= new QTimer(this);
    connect(timer_singleShot, SIGNAL(timeout()), SLOT(on_timer_singleShot_elapsed()));
    timer_singleShot->setSingleShot(true);
    index_SingleShotTimer = 0;
    timer_singleShot->start(50);



    //qDebug()<<" debug 3";
    timer_enabler = new QTimer(this);
    connect(timer_enabler, SIGNAL(timeout()), SLOT(on_timer_enabler_elapsed()));
    timer_enabler->setInterval(800);
    //timer_enabler->start();
    index_SingleShotTimer = 0;


    //qDebug()<<" debug 4";
    for(int i=0; i<TOTAL_CHANNEL; i++)
    {
        disableLCDNumber(i);
    }
    //qDebug()<<" debug 5 all";
}

MainWindow::~MainWindow()
{
    delete ui;
}



// ------------------------ Thread Signals Slots ------------------
void MainWindow::rx_ChannelValue(int chnl, uint32_t raw, float fVal, float val)
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
void MainWindow::rx_ramdomOP(int idx, float val, QString str)
{
    switch (idx) {
    case 0: {
        //ui->lbl_FilePath->setText(QString("PATH: "+str));
        ui->statusbar->showMessage(QString("PATH: "+str), 5000);
        break;
    }
    case 1: {
        //qDebug()<<" Time string is:: "<<str;
        ui->lbl_Time->setText(str);
        //ui->statusbar->showMessage(QString("PATH: "+str), 5000);
        break;
    }
    }
}

// ------------------------ Timers Slots ------------------
void MainWindow::on_timer_singleShot_elapsed()
{
    switch (index_SingleShotTimer) {
    case 0:{
        connectAllButtonsClickToSingleSlot();
        emit tx_sendFactorsAndPGAs_AllChnls();
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
    if(index_Enabler == 0 ) timer_enabler->setInterval(200);


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



// ------------------------ Helping Methods ------------------
void MainWindow::rx_sendingFactorsAndPGAs(int chnl, float fac, float pgaa, bool enabled)
{
    switch (chnl) {
    case 0: { ui->lbl_factor_0->setText(QString::number(fac, 'f', factorPrecision)); break; }
    case 1: { ui->lbl_factor_1->setText(QString::number(fac, 'f', factorPrecision)); break; }
    case 2: { ui->lbl_factor_2->setText(QString::number(fac, 'f', factorPrecision)); break; }
    case 3: { ui->lbl_factor_3->setText(QString::number(fac, 'f', factorPrecision)); break; }
    case 4: { ui->lbl_factor_4->setText(QString::number(fac, 'f', factorPrecision)); break; }
    case 5: { ui->lbl_factor_5->setText(QString::number(fac, 'f', factorPrecision)); break; }
    case 6: { ui->lbl_factor_6->setText(QString::number(fac, 'f', factorPrecision)); break; }
    case 7: { ui->lbl_factor_7->setText(QString::number(fac, 'f', factorPrecision)); break; }
    case 8: { ui->lbl_factor_8->setText(QString::number(fac, 'f', factorPrecision)); break; }
    case 9: { ui->lbl_factor_9->setText(QString::number(fac, 'f', factorPrecision)); break; }
    case 10: { ui->lbl_factor_10->setText(QString::number(fac, 'f', factorPrecision)); break; }

    case 11: { ui->lbl_factor_11->setText(QString::number(fac, 'f', factorPrecision)); break; }
    case 12: { ui->lbl_factor_12->setText(QString::number(fac, 'f', factorPrecision)); break; }
    case 13: { ui->lbl_factor_13->setText(QString::number(fac, 'f', factorPrecision)); break; }
    case 14: { ui->lbl_factor_14->setText(QString::number(fac, 'f', factorPrecision)); break; }
    case 15: { ui->lbl_factor_15->setText(QString::number(fac, 'f', factorPrecision)); break; }
    case 16: { ui->lbl_factor_16->setText(QString::number(fac, 'f', factorPrecision)); break; }
    case 17: { ui->lbl_factor_17->setText(QString::number(fac, 'f', factorPrecision)); break; }
    case 18: { ui->lbl_factor_18->setText(QString::number(fac, 'f', factorPrecision)); break; }
    case 19: { ui->lbl_factor_19->setText(QString::number(fac, 'f', factorPrecision)); break; }
    case 20: { ui->lbl_factor_20->setText(QString::number(fac, 'f', factorPrecision)); break; }

    case 21: { ui->lbl_factor_21->setText(QString::number(fac, 'f', factorPrecision)); break; }
    case 22: { ui->lbl_factor_22->setText(QString::number(fac, 'f', factorPrecision)); break; }
    case 23: { ui->lbl_factor_23->setText(QString::number(fac, 'f', factorPrecision)); break; }
    case 24: { ui->lbl_factor_24->setText(QString::number(fac, 'f', factorPrecision)); break; }
    case 25: { ui->lbl_factor_25->setText(QString::number(fac, 'f', factorPrecision)); break; }
    case 26: { ui->lbl_factor_26->setText(QString::number(fac, 'f', factorPrecision)); break; }
    case 27: { ui->lbl_factor_27->setText(QString::number(fac, 'f', factorPrecision)); break; }
    case 28: { ui->lbl_factor_28->setText(QString::number(fac, 'f', factorPrecision)); break; }
    case 29: { ui->lbl_factor_29->setText(QString::number(fac, 'f', factorPrecision)); break; }
    case 30: { ui->lbl_factor_30->setText(QString::number(fac, 'f', factorPrecision)); break; }

    case 31: { ui->lbl_factor_31->setText(QString::number(fac, 'f', factorPrecision)); break; }
    case 32: { ui->lbl_factor_32->setText(QString::number(fac, 'f', factorPrecision)); break; }
    case 33: { ui->lbl_factor_33->setText(QString::number(fac, 'f', factorPrecision)); break; }
    case 34: { ui->lbl_factor_34->setText(QString::number(fac, 'f', factorPrecision)); break; }
    case 35: { ui->lbl_factor_35->setText(QString::number(fac, 'f', factorPrecision)); break; }
    case 36: { ui->lbl_factor_36->setText(QString::number(fac, 'f', factorPrecision)); break; }
    case 37: { ui->lbl_factor_37->setText(QString::number(fac, 'f', factorPrecision)); break; }
    case 38: { ui->lbl_factor_38->setText(QString::number(fac, 'f', factorPrecision)); break; }
    case 39: { ui->lbl_factor_39->setText(QString::number(fac, 'f', factorPrecision)); break; }
    case 40: { ui->lbl_factor_40->setText(QString::number(fac, 'f', factorPrecision)); break; }

    case 41: { ui->lbl_factor_41->setText(QString::number(fac, 'f', factorPrecision)); break; }
    case 42: { ui->lbl_factor_42->setText(QString::number(fac, 'f', factorPrecision)); break; }
    case 43: { ui->lbl_factor_43->setText(QString::number(fac, 'f', factorPrecision)); break; }
    case 44: { ui->lbl_factor_44->setText(QString::number(fac, 'f', factorPrecision)); break; }
    case 45: { ui->lbl_factor_45->setText(QString::number(fac, 'f', factorPrecision)); break; }
    case 46: { ui->lbl_factor_46->setText(QString::number(fac, 'f', factorPrecision)); break; }
    case 47: { ui->lbl_factor_47->setText(QString::number(fac, 'f', factorPrecision)); break; }
    }

    setChannel_toEnabledDisable(chnl, enabled);
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
    case 0: {ui->lbl_lcdNumber_0->display(""); ui->lbl_factor_0->setVisible(false); break; }
    case 1: { ui->lbl_lcdNumber_1->display(""); ui->lbl_factor_1->setVisible(false); break; }
    case 2: { ui->lbl_lcdNumber_2->display(""); ui->lbl_factor_2->setVisible(false); break; }
    case 3: { ui->lbl_lcdNumber_3->display(""); ui->lbl_factor_3->setVisible(false); break; }
    case 4: { ui->lbl_lcdNumber_4->display(""); ui->lbl_factor_4->setVisible(false); break; }
    case 5: { ui->lbl_lcdNumber_5->display(""); ui->lbl_factor_5->setVisible(false); break; }
    case 6: { ui->lbl_lcdNumber_6->display(""); ui->lbl_factor_6->setVisible(false); break; }
    case 7: { ui->lbl_lcdNumber_7->display(""); ui->lbl_factor_7->setVisible(false); break; }
    case 8: { ui->lbl_lcdNumber_8->display(""); ui->lbl_factor_8->setVisible(false); break; }
    case 9: { ui->lbl_lcdNumber_9->display(""); ui->lbl_factor_9->setVisible(false); break; }
    case 10: { ui->lbl_lcdNumber_10->display(""); ui->lbl_factor_10->setVisible(false); break; }
    case 11: { ui->lbl_lcdNumber_11->display(""); ui->lbl_factor_11->setVisible(false); break; }

    case 12: { ui->lbl_lcdNumber_12->display(""); ui->lbl_factor_12->setVisible(false); break; }
    case 13: { ui->lbl_lcdNumber_13->display(""); ui->lbl_factor_13->setVisible(false); break; }
    case 14: { ui->lbl_lcdNumber_14->display(""); ui->lbl_factor_14->setVisible(false); break; }
    case 15: { ui->lbl_lcdNumber_15->display(""); ui->lbl_factor_15->setVisible(false); break; }
    case 16: { ui->lbl_lcdNumber_16->display(""); ui->lbl_factor_16->setVisible(false); break; }
    case 17: { ui->lbl_lcdNumber_17->display(""); ui->lbl_factor_17->setVisible(false); break; }
    case 18: { ui->lbl_lcdNumber_18->display(""); ui->lbl_factor_18->setVisible(false); break; }
    case 19: { ui->lbl_lcdNumber_19->display(""); ui->lbl_factor_19->setVisible(false); break; }
    case 20: { ui->lbl_lcdNumber_20->display(""); ui->lbl_factor_20->setVisible(false); break; }
    case 21: { ui->lbl_lcdNumber_21->display(""); ui->lbl_factor_21->setVisible(false); break; }

    case 22: { ui->lbl_lcdNumber_22->display(""); ui->lbl_factor_22->setVisible(false); break; }
    case 23: { ui->lbl_lcdNumber_23->display(""); ui->lbl_factor_23->setVisible(false); break; }
    case 24: { ui->lbl_lcdNumber_24->display(""); ui->lbl_factor_24->setVisible(false); break; }
    case 25: { ui->lbl_lcdNumber_25->display(""); ui->lbl_factor_25->setVisible(false); break; }
    case 26: { ui->lbl_lcdNumber_26->display(""); ui->lbl_factor_26->setVisible(false); break; }
    case 27: { ui->lbl_lcdNumber_27->display(""); ui->lbl_factor_27->setVisible(false); break; }
    case 28: { ui->lbl_lcdNumber_28->display(""); ui->lbl_factor_28->setVisible(false); break; }
    case 29: { ui->lbl_lcdNumber_29->display(""); ui->lbl_factor_29->setVisible(false); break; }
    case 30: { ui->lbl_lcdNumber_30->display(""); ui->lbl_factor_30->setVisible(false); break; }
    case 31: { ui->lbl_lcdNumber_31->display(""); ui->lbl_factor_31->setVisible(false); break; }

    case 32: { ui->lbl_lcdNumber_32->display(""); ui->lbl_factor_32->setVisible(false); break; }
    case 33: { ui->lbl_lcdNumber_33->display(""); ui->lbl_factor_33->setVisible(false); break; }
    case 34: { ui->lbl_lcdNumber_34->display(""); ui->lbl_factor_34->setVisible(false); break; }
    case 35: { ui->lbl_lcdNumber_35->display(""); ui->lbl_factor_35->setVisible(false); break; }
    case 36: { ui->lbl_lcdNumber_36->display(""); ui->lbl_factor_36->setVisible(false); break; }
    case 37: { ui->lbl_lcdNumber_37->display(""); ui->lbl_factor_37->setVisible(false); break; }
    case 38: { ui->lbl_lcdNumber_38->display(""); ui->lbl_factor_38->setVisible(false); break; }
    case 39: { ui->lbl_lcdNumber_39->display(""); ui->lbl_factor_39->setVisible(false); break; }
    case 40: { ui->lbl_lcdNumber_40->display(""); ui->lbl_factor_40->setVisible(false); break; }
    case 41: { ui->lbl_lcdNumber_41->display(""); ui->lbl_factor_41->setVisible(false); break; }

    case 42: { ui->lbl_lcdNumber_42->display(""); ui->lbl_factor_42->setVisible(false); break; }
    case 43: { ui->lbl_lcdNumber_43->display(""); ui->lbl_factor_43->setVisible(false); break; }
    case 44: { ui->lbl_lcdNumber_44->display(""); ui->lbl_factor_44->setVisible(false); break; }
    case 45: { ui->lbl_lcdNumber_45->display(""); ui->lbl_factor_45->setVisible(false); break; }
    case 46: { ui->lbl_lcdNumber_46->display(""); ui->lbl_factor_46->setVisible(false); break; }
    case 47: { ui->lbl_lcdNumber_47->display(""); ui->lbl_factor_47->setVisible(false); break; }

    } // end of Switch statement
}
void MainWindow::showFactorLabel(int indx)
{
    switch (indx) {
    case 0: {ui->lbl_factor_0->setVisible(true); break; }
    case 1: {ui->lbl_factor_1->setVisible(true); break; }
    case 2: {ui->lbl_factor_2->setVisible(true); break; }
    case 3: {ui->lbl_factor_3->setVisible(true); break; }
    case 4: {ui->lbl_factor_4->setVisible(true); break; }
    case 5: {ui->lbl_factor_5->setVisible(true); break; }
    case 6: {ui->lbl_factor_6->setVisible(true); break; }
    case 7: {ui->lbl_factor_7->setVisible(true); break; }
    case 8: {ui->lbl_factor_8->setVisible(true); break; }
    case 9: {ui->lbl_factor_9->setVisible(true); break; }
    case 10: {ui->lbl_factor_10->setVisible(true); break; }
    case 11: {ui->lbl_factor_11->setVisible(true); break; }

    case 12: {ui->lbl_factor_12->setVisible(true); break; }
    case 13: {ui->lbl_factor_13->setVisible(true); break; }
    case 14: {ui->lbl_factor_14->setVisible(true); break; }
    case 15: {ui->lbl_factor_15->setVisible(true); break; }
    case 16: {ui->lbl_factor_16->setVisible(true); break; }
    case 17: {ui->lbl_factor_17->setVisible(true); break; }
    case 18: {ui->lbl_factor_18->setVisible(true); break; }
    case 19: {ui->lbl_factor_19->setVisible(true); break; }
    case 20: {ui->lbl_factor_20->setVisible(true); break; }
    case 21: {ui->lbl_factor_21->setVisible(true); break; }

    case 22: {ui->lbl_factor_22->setVisible(true); break; }
    case 23: {ui->lbl_factor_23->setVisible(true); break; }
    case 24: {ui->lbl_factor_24->setVisible(true); break; }
    case 25: {ui->lbl_factor_25->setVisible(true); break; }
    case 26: {ui->lbl_factor_26->setVisible(true); break; }
    case 27: {ui->lbl_factor_27->setVisible(true); break; }
    case 28: {ui->lbl_factor_28->setVisible(true); break; }
    case 29: {ui->lbl_factor_29->setVisible(true); break; }
    case 30: {ui->lbl_factor_30->setVisible(true); break; }
    case 31: {ui->lbl_factor_31->setVisible(true); break; }

    case 32: {ui->lbl_factor_32->setVisible(true); break; }
    case 33: {ui->lbl_factor_33->setVisible(true); break; }
    case 34: {ui->lbl_factor_34->setVisible(true); break; }
    case 35: {ui->lbl_factor_35->setVisible(true); break; }
    case 36: {ui->lbl_factor_36->setVisible(true); break; }
    case 37: {ui->lbl_factor_37->setVisible(true); break; }
    case 38: {ui->lbl_factor_38->setVisible(true); break; }
    case 39: {ui->lbl_factor_39->setVisible(true); break; }
    case 40: {ui->lbl_factor_40->setVisible(true); break; }
    case 41: {ui->lbl_factor_41->setVisible(true); break; }
    case 42: {ui->lbl_factor_42->setVisible(true); break; }

    case 43: {ui->lbl_factor_43->setVisible(true); break; }
    case 44: {ui->lbl_factor_44->setVisible(true); break; }
    case 45: {ui->lbl_factor_45->setVisible(true); break; }
    case 46: {ui->lbl_factor_46->setVisible(true); break; }
    case 47: {ui->lbl_factor_47->setVisible(true); break; }

    } // end of Switch statement
}
void MainWindow::setChannel_toEnabledDisable(int idx, bool enabled)
{
    switch (idx) {
    case 0: { ui->pb_channel_0->setChecked(enabled); ui->pb_channel_0->clicked();  break; }
    case 1: { ui->pb_channel_1->setChecked(enabled); ui->pb_channel_1->clicked(); break; }
    case 2: { ui->pb_channel_2->setChecked(enabled); ui->pb_channel_2->clicked(); break; }
    case 3: { ui->pb_channel_3->setChecked(enabled); ui->pb_channel_3->clicked(); break; }
    case 4: { ui->pb_channel_4->setChecked(enabled); ui->pb_channel_4->clicked(); break; }
    case 5: { ui->pb_channel_5->setChecked(enabled); ui->pb_channel_5->clicked(); break; }
    case 6: { ui->pb_channel_6->setChecked(enabled); ui->pb_channel_6->clicked(); break; }
    case 7: { ui->pb_channel_7->setChecked(enabled); ui->pb_channel_7->clicked(); break; }
    case 8: { ui->pb_channel_8->setChecked(enabled); ui->pb_channel_8->clicked(); break; }
    case 9: { ui->pb_channel_9->setChecked(enabled); ui->pb_channel_9->clicked(); break; }
    case 10: { ui->pb_channel_10->setChecked(enabled); ui->pb_channel_10->clicked(); break; }
    case 11: { ui->pb_channel_11->setChecked(enabled); ui->pb_channel_11->clicked(); break; }

    case 12: { ui->pb_channel_12->setChecked(enabled); ui->pb_channel_12->clicked(); break; }
    case 13: { ui->pb_channel_13->setChecked(enabled); ui->pb_channel_13->clicked(); break; }
    case 14: { ui->pb_channel_14->setChecked(enabled); ui->pb_channel_14->clicked(); break; }
    case 15: { ui->pb_channel_15->setChecked(enabled); ui->pb_channel_15->clicked(); break; }
    case 16: { ui->pb_channel_16->setChecked(enabled); ui->pb_channel_16->clicked(); break; }
    case 17: { ui->pb_channel_17->setChecked(enabled); ui->pb_channel_17->clicked(); break; }
    case 18: { ui->pb_channel_18->setChecked(enabled); ui->pb_channel_18->clicked(); break; }
    case 19: { ui->pb_channel_19->setChecked(enabled); ui->pb_channel_19->clicked(); break; }
    case 20: { ui->pb_channel_20->setChecked(enabled); ui->pb_channel_20->clicked(); break; }
    case 21: { ui->pb_channel_21->setChecked(enabled); ui->pb_channel_21->clicked(); break; }

    case 22: { ui->pb_channel_22->setChecked(enabled); ui->pb_channel_22->clicked(); break; }
    case 23: { ui->pb_channel_23->setChecked(enabled); ui->pb_channel_23->clicked(); break; }
    case 24: { ui->pb_channel_24->setChecked(enabled); ui->pb_channel_24->clicked(); break; }
    case 25: { ui->pb_channel_25->setChecked(enabled); ui->pb_channel_25->clicked(); break; }
    case 26: { ui->pb_channel_26->setChecked(enabled); ui->pb_channel_26->clicked(); break; }
    case 27: { ui->pb_channel_27->setChecked(enabled); ui->pb_channel_27->clicked(); break; }
    case 28: { ui->pb_channel_28->setChecked(enabled); ui->pb_channel_28->clicked(); break; }
    case 29: { ui->pb_channel_29->setChecked(enabled); ui->pb_channel_29->clicked(); break; }
    case 30: { ui->pb_channel_30->setChecked(enabled); ui->pb_channel_30->clicked(); break; }
    case 31: { ui->pb_channel_31->setChecked(enabled); ui->pb_channel_31->clicked(); break; }

    case 32: { ui->pb_channel_32->setChecked(enabled); ui->pb_channel_32->clicked(); break; }
    case 33: { ui->pb_channel_33->setChecked(enabled); ui->pb_channel_33->clicked(); break; }
    case 34: { ui->pb_channel_34->setChecked(enabled); ui->pb_channel_34->clicked(); break; }
    case 35: { ui->pb_channel_35->setChecked(enabled); ui->pb_channel_35->clicked(); break; }
    case 36: { ui->pb_channel_36->setChecked(enabled); ui->pb_channel_36->clicked(); break; }
    case 37: { ui->pb_channel_37->setChecked(enabled); ui->pb_channel_37->clicked(); break; }
    case 38: { ui->pb_channel_38->setChecked(enabled); ui->pb_channel_38->clicked(); break; }
    case 39: { ui->pb_channel_39->setChecked(enabled); ui->pb_channel_39->clicked(); break; }
    case 40: { ui->pb_channel_40->setChecked(enabled); ui->pb_channel_40->clicked(); break; }
    case 41: { ui->pb_channel_41->setChecked(enabled); ui->pb_channel_41->clicked(); break; }

    case 42: { ui->pb_channel_42->setChecked(enabled); ui->pb_channel_42->clicked(); break; }
    case 43: { ui->pb_channel_43->setChecked(enabled); ui->pb_channel_43->clicked(); break; }
    case 44: { ui->pb_channel_44->setChecked(enabled); ui->pb_channel_44->clicked(); break; }
    case 45: { ui->pb_channel_45->setChecked(enabled); ui->pb_channel_45->clicked(); break; }
    case 46: { ui->pb_channel_46->setChecked(enabled); ui->pb_channel_46->clicked(); break; }
    case 47: { ui->pb_channel_47->setChecked(enabled); ui->pb_channel_47->clicked(); break; }

    }

}


// ------------------------ GUI Buttons Slots ------------------

void MainWindow::rx_confirmationBoxClosed(bool yesBTN, int param)
{
    qDebug()<<" MessageConfirmation Slot: param:"<<param<<" Yes-Btn: "<<yesBTN;
    if(param == 2 && yesBTN)
    {
        local_loggingStarted = !local_loggingStarted;
        emit tx_loggingStartStop(local_loggingStarted, logUserFilePath);
        usleep(500000);
        emit tx_ClosingWindow_logConfig();
        QCoreApplication::quit();
    }
}
void MainWindow::on_pb_CloseApp_clicked()
{
    //emit tx_generate_ThisGUI(gui_FIRST_WIN);
    //emit tx_ClosingWindow_logConfig();
    //QCoreApplication::quit();

    if(local_loggingStarted)
    {
        msgBox = new ConfirmationBox();
        msgBox->rx_MessageBoxVariables(2, "System in Process", "Logging process is running. DO you want to stop logging and go back to settings window?");
        connect(msgBox, SIGNAL(tx_confirmationBoxClosed(bool, int)), this, SLOT(rx_confirmationBoxClosed(bool, int)));
        msgBox->setModal(true);
        msgBox->show();
    }
    else
    {
        emit tx_ClosingWindow_logConfig();
        QCoreApplication::quit();
    }
}

void MainWindow::on_slider_samplingRate_valueChanged(int value)
{
    ui->txt_SampleTime->setValue(value);
}
void MainWindow::on_txt_SampleTime_valueChanged(int arg1)
{
    ui->slider_samplingRate->setValue(arg1);
}
void MainWindow::on_pb_EnableAll_clicked()
{
    // ---- 0
    ui->pb_channel_0->setChecked(true); ui->pb_channel_0->clicked();
    ui->lbl_lcdNumber_0->display(""); ui->lbl_factor_0->setVisible(true);
    // ---- 1
    ui->pb_channel_1->setChecked(true); ui->pb_channel_1->clicked();
    ui->lbl_lcdNumber_1->display(""); ui->lbl_factor_1->setVisible(true);
    // ---- 2
    ui->pb_channel_2->setChecked(true); ui->pb_channel_2->clicked();
    ui->lbl_lcdNumber_2->display(""); ui->lbl_factor_2->setVisible(true);
    // ---- 3
    ui->pb_channel_3->setChecked(true); ui->pb_channel_3->clicked();
    ui->lbl_lcdNumber_3->display(""); ui->lbl_factor_3->setVisible(true);
    // ---- 4
    ui->pb_channel_4->setChecked(true); ui->pb_channel_4->clicked();
    ui->lbl_lcdNumber_4->display(""); ui->lbl_factor_4->setVisible(true);
    // ---- 5
    ui->pb_channel_5->setChecked(true); ui->pb_channel_5->clicked();
    ui->lbl_lcdNumber_5->display(""); ui->lbl_factor_5->setVisible(true);
    // ---- 6
    ui->pb_channel_6->setChecked(true); ui->pb_channel_6->clicked();
    ui->lbl_lcdNumber_6->display(""); ui->lbl_factor_6->setVisible(true);
    // ---- 7
    ui->pb_channel_7->setChecked(true); ui->pb_channel_7->clicked();
    ui->lbl_lcdNumber_7->display(""); ui->lbl_factor_7->setVisible(true);
    // ---- 8
    ui->pb_channel_8->setChecked(true); ui->pb_channel_8->clicked();
    ui->lbl_lcdNumber_8->display(""); ui->lbl_factor_8->setVisible(true);
    // ---- 9
    ui->pb_channel_9->setChecked(true); ui->pb_channel_9->clicked();
    ui->lbl_lcdNumber_9->display(""); ui->lbl_factor_9->setVisible(true);
    // ---- 10
    ui->pb_channel_10->setChecked(true); ui->pb_channel_10->clicked();
    ui->lbl_lcdNumber_10->display(""); ui->lbl_factor_10->setVisible(true);
    // ---- 11
    ui->pb_channel_11->setChecked(true); ui->pb_channel_11->clicked();
    ui->lbl_lcdNumber_11->display(""); ui->lbl_factor_11->setVisible(true);
    // ---- 12
    ui->pb_channel_12->setChecked(true); ui->pb_channel_12->clicked();
    ui->lbl_lcdNumber_12->display(""); ui->lbl_factor_12->setVisible(true);
    // ---- 13
    ui->pb_channel_13->setChecked(true); ui->pb_channel_13->clicked();
    ui->lbl_lcdNumber_13->display(""); ui->lbl_factor_13->setVisible(true);
    // ---- 14
    ui->pb_channel_14->setChecked(true); ui->pb_channel_14->clicked();
    ui->lbl_lcdNumber_14->display(""); ui->lbl_factor_14->setVisible(true);
    // ---- 15
    ui->pb_channel_15->setChecked(true); ui->pb_channel_15->clicked();
    ui->lbl_lcdNumber_15->display(""); ui->lbl_factor_15->setVisible(true);
    // ---- 16
    ui->pb_channel_16->setChecked(true); ui->pb_channel_16->clicked();
    ui->lbl_lcdNumber_16->display(""); ui->lbl_factor_16->setVisible(true);
    // ---- 17
    ui->pb_channel_17->setChecked(true); ui->pb_channel_17->clicked();
    ui->lbl_lcdNumber_17->display(""); ui->lbl_factor_17->setVisible(true);
    // ---- 18
    ui->pb_channel_18->setChecked(true); ui->pb_channel_18->clicked();
    ui->lbl_lcdNumber_18->display(""); ui->lbl_factor_18->setVisible(true);
    // ---- 19
    ui->pb_channel_19->setChecked(true); ui->pb_channel_19->clicked();
    ui->lbl_lcdNumber_19->display(""); ui->lbl_factor_19->setVisible(true);
    // ---- 20
    ui->pb_channel_20->setChecked(true); ui->pb_channel_20->clicked();
    ui->lbl_lcdNumber_20->display(""); ui->lbl_factor_20->setVisible(true);
    // ---- 21
    ui->pb_channel_21->setChecked(true); ui->pb_channel_21->clicked();
    ui->lbl_lcdNumber_21->display(""); ui->lbl_factor_21->setVisible(true);
    // ---- 22
    ui->pb_channel_22->setChecked(true); ui->pb_channel_22->clicked();
    ui->lbl_lcdNumber_22->display(""); ui->lbl_factor_22->setVisible(true);
    // ---- 23
    ui->pb_channel_23->setChecked(true); ui->pb_channel_23->clicked();
    ui->lbl_lcdNumber_23->display(""); ui->lbl_factor_23->setVisible(true);
    // ---- 24
    ui->pb_channel_24->setChecked(true); ui->pb_channel_24->clicked();
    ui->lbl_lcdNumber_24->display(""); ui->lbl_factor_24->setVisible(true);
    // ---- 25
    ui->pb_channel_25->setChecked(true); ui->pb_channel_25->clicked();
    ui->lbl_lcdNumber_25->display(""); ui->lbl_factor_25->setVisible(true);
    // ---- 26
    ui->pb_channel_26->setChecked(true); ui->pb_channel_26->clicked();
    ui->lbl_lcdNumber_26->display(""); ui->lbl_factor_26->setVisible(true);
    // ---- 27
    ui->pb_channel_27->setChecked(true); ui->pb_channel_27->clicked();
    ui->lbl_lcdNumber_27->display(""); ui->lbl_factor_27->setVisible(true);
    // ---- 28
    ui->pb_channel_28->setChecked(true); ui->pb_channel_28->clicked();
    ui->lbl_lcdNumber_28->display(""); ui->lbl_factor_28->setVisible(true);
    // ---- 29
    ui->pb_channel_29->setChecked(true); ui->pb_channel_29->clicked();
    ui->lbl_lcdNumber_29->display(""); ui->lbl_factor_29->setVisible(true);
    // ---- 30
    ui->pb_channel_30->setChecked(true); ui->pb_channel_30->clicked();
    ui->lbl_lcdNumber_30->display(""); ui->lbl_factor_30->setVisible(true);
    // ---- 31
    ui->pb_channel_31->setChecked(true); ui->pb_channel_31->clicked();
    ui->lbl_lcdNumber_31->display(""); ui->lbl_factor_31->setVisible(true);
    // ---- 32
    ui->pb_channel_32->setChecked(true); ui->pb_channel_32->clicked();
    ui->lbl_lcdNumber_32->display(""); ui->lbl_factor_32->setVisible(true);
    // ---- 33
    ui->pb_channel_33->setChecked(true); ui->pb_channel_33->clicked();
    ui->lbl_lcdNumber_33->display(""); ui->lbl_factor_33->setVisible(true);
    // ---- 34
    ui->pb_channel_34->setChecked(true); ui->pb_channel_34->clicked();
    ui->lbl_lcdNumber_34->display(""); ui->lbl_factor_34->setVisible(true);
    // ---- 35
    ui->pb_channel_35->setChecked(true); ui->pb_channel_35->clicked();
    ui->lbl_lcdNumber_35->display(""); ui->lbl_factor_35->setVisible(true);
    // ---- 36
    ui->pb_channel_36->setChecked(true); ui->pb_channel_36->clicked();
    ui->lbl_lcdNumber_36->display(""); ui->lbl_factor_36->setVisible(true);
    // ---- 37
    ui->pb_channel_37->setChecked(true); ui->pb_channel_37->clicked();
    ui->lbl_lcdNumber_37->display(""); ui->lbl_factor_37->setVisible(true);
    // ---- 38
    ui->pb_channel_38->setChecked(true); ui->pb_channel_38->clicked();
    ui->lbl_lcdNumber_38->display(""); ui->lbl_factor_38->setVisible(true);
    // ---- 39
    ui->pb_channel_39->setChecked(true); ui->pb_channel_39->clicked();
    ui->lbl_lcdNumber_39->display(""); ui->lbl_factor_39->setVisible(true);
    // ---- 40
    ui->pb_channel_40->setChecked(true); ui->pb_channel_40->clicked();
    ui->lbl_lcdNumber_40->display(""); ui->lbl_factor_40->setVisible(true);
    // ---- 41
    ui->pb_channel_41->setChecked(true); ui->pb_channel_41->clicked();
    ui->lbl_lcdNumber_41->display(""); ui->lbl_factor_41->setVisible(true);
    // ---- 42
    ui->pb_channel_42->setChecked(true); ui->pb_channel_42->clicked();
    ui->lbl_lcdNumber_42->display(""); ui->lbl_factor_42->setVisible(true);
    // ---- 43
    ui->pb_channel_43->setChecked(true); ui->pb_channel_43->clicked();
    ui->lbl_lcdNumber_43->display(""); ui->lbl_factor_43->setVisible(true);
    // ---- 44
    ui->pb_channel_44->setChecked(true); ui->pb_channel_44->clicked();
    ui->lbl_lcdNumber_44->display(""); ui->lbl_factor_44->setVisible(true);
    // ---- 45
    ui->pb_channel_45->setChecked(true); ui->pb_channel_45->clicked();
    ui->lbl_lcdNumber_45->display(""); ui->lbl_factor_45->setVisible(true);
    // ---- 46
    ui->pb_channel_46->setChecked(true); ui->pb_channel_46->clicked();
    ui->lbl_lcdNumber_46->display(""); ui->lbl_factor_46->setVisible(true);
    // ---- 47
    ui->pb_channel_47->setChecked(true); ui->pb_channel_47->clicked();
    ui->lbl_lcdNumber_47->display(""); ui->lbl_factor_47->setVisible(true);

}
void MainWindow::on_pb_DisableAll_clicked()
{
    // ---- 0
    ui->pb_channel_0->setChecked(false); ui->pb_channel_0->clicked();
    ui->lbl_lcdNumber_0->display(""); ui->lbl_factor_0->setVisible(false);
    // ---- 1
    ui->pb_channel_1->setChecked(false); ui->pb_channel_1->clicked();
    ui->lbl_lcdNumber_1->display(""); ui->lbl_factor_1->setVisible(false);
    // ---- 2
    ui->pb_channel_2->setChecked(false); ui->pb_channel_2->clicked();
    ui->lbl_lcdNumber_2->display(""); ui->lbl_factor_2->setVisible(false);
    // ---- 3
    ui->pb_channel_3->setChecked(false); ui->pb_channel_3->clicked();
    ui->lbl_lcdNumber_3->display(""); ui->lbl_factor_3->setVisible(false);
    // ---- 4
    ui->pb_channel_4->setChecked(false); ui->pb_channel_4->clicked();
    ui->lbl_lcdNumber_4->display(""); ui->lbl_factor_4->setVisible(false);
    // ---- 5
    ui->pb_channel_5->setChecked(false); ui->pb_channel_5->clicked();
    ui->lbl_lcdNumber_5->display(""); ui->lbl_factor_5->setVisible(false);
    // ---- 6
    ui->pb_channel_6->setChecked(false); ui->pb_channel_6->clicked();
    ui->lbl_lcdNumber_6->display(""); ui->lbl_factor_6->setVisible(false);
    // ---- 7
    ui->pb_channel_7->setChecked(false); ui->pb_channel_7->clicked();
    ui->lbl_lcdNumber_7->display(""); ui->lbl_factor_7->setVisible(false);
    // ---- 8
    ui->pb_channel_8->setChecked(false); ui->pb_channel_8->clicked();
    ui->lbl_lcdNumber_8->display(""); ui->lbl_factor_8->setVisible(false);
    // ---- 9
    ui->pb_channel_9->setChecked(false); ui->pb_channel_9->clicked();
    ui->lbl_lcdNumber_9->display(""); ui->lbl_factor_9->setVisible(false);
    // ---- 10
    ui->pb_channel_10->setChecked(false); ui->pb_channel_10->clicked();
    ui->lbl_lcdNumber_10->display(""); ui->lbl_factor_10->setVisible(false);
    // ---- 11
    ui->pb_channel_11->setChecked(false); ui->pb_channel_11->clicked();
    ui->lbl_lcdNumber_11->display(""); ui->lbl_factor_11->setVisible(false);
    // ---- 12
    ui->pb_channel_12->setChecked(false); ui->pb_channel_12->clicked();
    ui->lbl_lcdNumber_12->display(""); ui->lbl_factor_12->setVisible(false);
    // ---- 13
    ui->pb_channel_13->setChecked(false); ui->pb_channel_13->clicked();
    ui->lbl_lcdNumber_13->display(""); ui->lbl_factor_13->setVisible(false);
    // ---- 14
    ui->pb_channel_14->setChecked(false); ui->pb_channel_14->clicked();
    ui->lbl_lcdNumber_14->display(""); ui->lbl_factor_14->setVisible(false);
    // ---- 15
    ui->pb_channel_15->setChecked(false); ui->pb_channel_15->clicked();
    ui->lbl_lcdNumber_15->display(""); ui->lbl_factor_15->setVisible(false);
    // ---- 16
    ui->pb_channel_16->setChecked(false); ui->pb_channel_16->clicked();
    ui->lbl_lcdNumber_16->display(""); ui->lbl_factor_16->setVisible(false);
    // ---- 17
    ui->pb_channel_17->setChecked(false); ui->pb_channel_17->clicked();
    ui->lbl_lcdNumber_17->display(""); ui->lbl_factor_17->setVisible(false);
    // ---- 18
    ui->pb_channel_18->setChecked(false); ui->pb_channel_18->clicked();
    ui->lbl_lcdNumber_18->display(""); ui->lbl_factor_18->setVisible(false);
    // ---- 19
    ui->pb_channel_19->setChecked(false); ui->pb_channel_19->clicked();
    ui->lbl_lcdNumber_19->display(""); ui->lbl_factor_19->setVisible(false);
    // ---- 20
    ui->pb_channel_20->setChecked(false); ui->pb_channel_20->clicked();
    ui->lbl_lcdNumber_20->display(""); ui->lbl_factor_20->setVisible(false);
    // ---- 21
    ui->pb_channel_21->setChecked(false); ui->pb_channel_21->clicked();
    ui->lbl_lcdNumber_21->display(""); ui->lbl_factor_21->setVisible(false);
    // ---- 22
    ui->pb_channel_22->setChecked(false); ui->pb_channel_22->clicked();
    ui->lbl_lcdNumber_22->display(""); ui->lbl_factor_22->setVisible(false);
    // ---- 23
    ui->pb_channel_23->setChecked(false); ui->pb_channel_23->clicked();
    ui->lbl_lcdNumber_23->display(""); ui->lbl_factor_23->setVisible(false);
    // ---- 24
    ui->pb_channel_24->setChecked(false); ui->pb_channel_24->clicked();
    ui->lbl_lcdNumber_24->display(""); ui->lbl_factor_24->setVisible(false);
    // ---- 25
    ui->pb_channel_25->setChecked(false); ui->pb_channel_25->clicked();
    ui->lbl_lcdNumber_25->display(""); ui->lbl_factor_25->setVisible(false);
    // ---- 26
    ui->pb_channel_26->setChecked(false); ui->pb_channel_26->clicked();
    ui->lbl_lcdNumber_26->display(""); ui->lbl_factor_26->setVisible(false);
    // ---- 27
    ui->pb_channel_27->setChecked(false); ui->pb_channel_27->clicked();
    ui->lbl_lcdNumber_27->display(""); ui->lbl_factor_27->setVisible(false);
    // ---- 28
    ui->pb_channel_28->setChecked(false); ui->pb_channel_28->clicked();
    ui->lbl_lcdNumber_28->display(""); ui->lbl_factor_28->setVisible(false);
    // ---- 29
    ui->pb_channel_29->setChecked(false); ui->pb_channel_29->clicked();
    ui->lbl_lcdNumber_29->display(""); ui->lbl_factor_29->setVisible(false);
    // ---- 30
    ui->pb_channel_30->setChecked(false); ui->pb_channel_30->clicked();
    ui->lbl_lcdNumber_30->display(""); ui->lbl_factor_30->setVisible(false);
    // ---- 31
    ui->pb_channel_31->setChecked(false); ui->pb_channel_31->clicked();
    ui->lbl_lcdNumber_31->display(""); ui->lbl_factor_31->setVisible(false);
    // ---- 32
    ui->pb_channel_32->setChecked(false); ui->pb_channel_32->clicked();
    ui->lbl_lcdNumber_32->display(""); ui->lbl_factor_32->setVisible(false);
    // ---- 33
    ui->pb_channel_33->setChecked(false); ui->pb_channel_33->clicked();
    ui->lbl_lcdNumber_33->display(""); ui->lbl_factor_33->setVisible(false);
    // ---- 34
    ui->pb_channel_34->setChecked(false); ui->pb_channel_34->clicked();
    ui->lbl_lcdNumber_34->display(""); ui->lbl_factor_34->setVisible(false);
    // ---- 35
    ui->pb_channel_35->setChecked(false); ui->pb_channel_35->clicked();
    ui->lbl_lcdNumber_35->display(""); ui->lbl_factor_35->setVisible(false);
    // ---- 36
    ui->pb_channel_36->setChecked(false); ui->pb_channel_36->clicked();
    ui->lbl_lcdNumber_36->display(""); ui->lbl_factor_36->setVisible(false);
    // ---- 37
    ui->pb_channel_37->setChecked(false); ui->pb_channel_37->clicked();
    ui->lbl_lcdNumber_37->display(""); ui->lbl_factor_37->setVisible(false);
    // ---- 38
    ui->pb_channel_38->setChecked(false); ui->pb_channel_38->clicked();
    ui->lbl_lcdNumber_38->display(""); ui->lbl_factor_38->setVisible(false);
    // ---- 39
    ui->pb_channel_39->setChecked(false); ui->pb_channel_39->clicked();
    ui->lbl_lcdNumber_39->display(""); ui->lbl_factor_39->setVisible(false);
    // ---- 40
    ui->pb_channel_40->setChecked(false); ui->pb_channel_40->clicked();
    ui->lbl_lcdNumber_40->display(""); ui->lbl_factor_40->setVisible(false);
    // ---- 41
    ui->pb_channel_41->setChecked(false); ui->pb_channel_41->clicked();
    ui->lbl_lcdNumber_41->display(""); ui->lbl_factor_41->setVisible(false);
    // ---- 42
    ui->pb_channel_42->setChecked(false); ui->pb_channel_42->clicked();
    ui->lbl_lcdNumber_42->display(""); ui->lbl_factor_42->setVisible(false);
    // ---- 43
    ui->pb_channel_43->setChecked(false); ui->pb_channel_43->clicked();
    ui->lbl_lcdNumber_43->display(""); ui->lbl_factor_43->setVisible(false);
    // ---- 44
    ui->pb_channel_44->setChecked(false); ui->pb_channel_44->clicked();
    ui->lbl_lcdNumber_44->display(""); ui->lbl_factor_44->setVisible(false);
    // ---- 45
    ui->pb_channel_45->setChecked(false); ui->pb_channel_45->clicked();
    ui->lbl_lcdNumber_45->display(""); ui->lbl_factor_45->setVisible(false);
    // ---- 46
    ui->pb_channel_46->setChecked(false); ui->pb_channel_46->clicked();
    ui->lbl_lcdNumber_46->display(""); ui->lbl_factor_46->setVisible(false);
    // ---- 47
    ui->pb_channel_47->setChecked(false); ui->pb_channel_47->clicked();
    ui->lbl_lcdNumber_47->display(""); ui->lbl_factor_47->setVisible(false);

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
            showFactorLabel(accessibleName_int);
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

void MainWindow::on_pb_StartLog_clicked()
{
    emit tx_setSampleTime((int)(ui->txt_SampleTime->value() * 1000.0));

    if(!local_loggingStarted) {
        logUserFilePath = QFileDialog::getSaveFileName(this, tr("Save Log File"), QString(QDir::homePath()+"/DAQ_Logs/untitled.csv"), tr("DAC Logs (*.csv)"));
        qDebug()<<" User setted File name is : "<<logUserFilePath;
        //ui->lbl_FilePath->setText(QString("Path: "+logUserFilePath));
        ui->statusbar->showMessage(QString("Path: "+logUserFilePath), 10000);
    }
    local_loggingStarted = !local_loggingStarted;
    emit tx_loggingStartStop(local_loggingStarted, logUserFilePath);

    ui->pb_StartLog->setText(QString(local_loggingStarted? "Started":"Stoped"));
    ui->pb_StartLog->setStyleSheet(QString(local_loggingStarted? styleLogStart : styleLogStop));
}

void MainWindow::on_pb_ConfigChannelSettings_clicked()
{
    tx_generate_ThisGUI(gui_CONFIG_CH_WIN);
}
void MainWindow::on_pb_ShowGraphWin_clicked()
{
    tx_generate_ThisGUI(gui_GRAPH_WIN);
}
