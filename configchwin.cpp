#include "configchwin.h"
#include "ui_configchwin.h"

ConfigChWin::ConfigChWin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConfigChWin)
{
    ui->setupUi(this);

    this->setFixedSize(1024, 768);

    this->setWindowFlags(Qt::FramelessWindowHint);
    //this->setWindowState(Qt::WindowFullScreen);
    //this->setWindowFlag(Qt::WindowStaysOnTopHint);
    this->setAttribute(Qt::WA_DeleteOnClose, true); //so that it will be deleted when closed

    //qDebug()<<" debug 1";
    timer_singleShot= new QTimer(this);
    connect(timer_singleShot, SIGNAL(timeout()), SLOT(on_timer_singleShot_elapsed()));
    timer_singleShot->setSingleShot(true);
    index_SingleShotTimer = 0;
    timer_singleShot->start(50);




}

ConfigChWin::~ConfigChWin()
{
    delete ui;
}



void ConfigChWin::on_pb_Channel_Clicked()
{
    QPushButton *button = (QPushButton *)sender();
    QString accessName = button->accessibleName();

    accessibleName_int = 0;
    okVariable = false;
    accessibleName_int = accessName.toInt(&okVariable, 10);
    //qDebug()<<accessName<<" Button Clicked = "<<accessibleName_int<<" checked: "<<button->property("isEnable");

    if(okVariable)
    {
        normal_Button_Color(local_currentCH_ID);
        emit tx_giveMechannelSettings(accessibleName_int);
        button->setStyleSheet(style_pbChnl_Enable);
        local_currentCH_ID = accessibleName_int;
    }
    else
    {
        qDebug()<<" Error in parsing accessible Name of pressed PushButton ";
        ui->lbl_Status->setText(" Error in parsing accessible Name of pressed PushButton ");
    }
}


void ConfigChWin::normal_Button_Color(int idx)
{
    switch (idx) {
    case 0:{ ui->pb_channel_0->setStyleSheet(style_pbChnl_Disable); break; }
    case 1:{ ui->pb_channel_1->setStyleSheet(style_pbChnl_Disable); break; }
    case 2:{ ui->pb_channel_2->setStyleSheet(style_pbChnl_Disable); break; }
    case 3:{ ui->pb_channel_3->setStyleSheet(style_pbChnl_Disable); break; }
    case 4:{ ui->pb_channel_4->setStyleSheet(style_pbChnl_Disable); break; }
    case 5:{ ui->pb_channel_5->setStyleSheet(style_pbChnl_Disable); break; }
    case 6:{ ui->pb_channel_6->setStyleSheet(style_pbChnl_Disable); break; }
    case 7:{ ui->pb_channel_7->setStyleSheet(style_pbChnl_Disable); break; }
    case 8:{ ui->pb_channel_8->setStyleSheet(style_pbChnl_Disable); break; }
    case 9:{ ui->pb_channel_9->setStyleSheet(style_pbChnl_Disable); break; }
    case 10:{ ui->pb_channel_10->setStyleSheet(style_pbChnl_Disable); break; }

    case 11:{ ui->pb_channel_11->setStyleSheet(style_pbChnl_Disable); break; }
    case 12:{ ui->pb_channel_12->setStyleSheet(style_pbChnl_Disable); break; }
    case 13:{ ui->pb_channel_13->setStyleSheet(style_pbChnl_Disable); break; }
    case 14:{ ui->pb_channel_14->setStyleSheet(style_pbChnl_Disable); break; }
    case 15:{ ui->pb_channel_15->setStyleSheet(style_pbChnl_Disable); break; }
    case 16:{ ui->pb_channel_16->setStyleSheet(style_pbChnl_Disable); break; }
    case 17:{ ui->pb_channel_17->setStyleSheet(style_pbChnl_Disable); break; }
    case 18:{ ui->pb_channel_18->setStyleSheet(style_pbChnl_Disable); break; }
    case 19:{ ui->pb_channel_19->setStyleSheet(style_pbChnl_Disable); break; }
    case 20:{ ui->pb_channel_20->setStyleSheet(style_pbChnl_Disable); break; }

    case 21:{ ui->pb_channel_21->setStyleSheet(style_pbChnl_Disable); break; }
    case 22:{ ui->pb_channel_22->setStyleSheet(style_pbChnl_Disable); break; }
    case 23:{ ui->pb_channel_23->setStyleSheet(style_pbChnl_Disable); break; }
    case 24:{ ui->pb_channel_24->setStyleSheet(style_pbChnl_Disable); break; }
    case 25:{ ui->pb_channel_25->setStyleSheet(style_pbChnl_Disable); break; }
    case 26:{ ui->pb_channel_26->setStyleSheet(style_pbChnl_Disable); break; }
    case 27:{ ui->pb_channel_27->setStyleSheet(style_pbChnl_Disable); break; }
    case 28:{ ui->pb_channel_28->setStyleSheet(style_pbChnl_Disable); break; }
    case 29:{ ui->pb_channel_29->setStyleSheet(style_pbChnl_Disable); break; }
    case 30:{ ui->pb_channel_30->setStyleSheet(style_pbChnl_Disable); break; }

    case 31:{ ui->pb_channel_31->setStyleSheet(style_pbChnl_Disable); break; }
    case 32:{ ui->pb_channel_32->setStyleSheet(style_pbChnl_Disable); break; }
    case 33:{ ui->pb_channel_33->setStyleSheet(style_pbChnl_Disable); break; }
    case 34:{ ui->pb_channel_34->setStyleSheet(style_pbChnl_Disable); break; }
    case 35:{ ui->pb_channel_35->setStyleSheet(style_pbChnl_Disable); break; }
    case 36:{ ui->pb_channel_36->setStyleSheet(style_pbChnl_Disable); break; }
    case 37:{ ui->pb_channel_37->setStyleSheet(style_pbChnl_Disable); break; }
    case 38:{ ui->pb_channel_38->setStyleSheet(style_pbChnl_Disable); break; }
    case 39:{ ui->pb_channel_39->setStyleSheet(style_pbChnl_Disable); break; }
    case 40:{ ui->pb_channel_40->setStyleSheet(style_pbChnl_Disable); break; }

    case 41:{ ui->pb_channel_41->setStyleSheet(style_pbChnl_Disable); break; }
    case 42:{ ui->pb_channel_42->setStyleSheet(style_pbChnl_Disable); break; }
    case 43:{ ui->pb_channel_43->setStyleSheet(style_pbChnl_Disable); break; }
    case 44:{ ui->pb_channel_44->setStyleSheet(style_pbChnl_Disable); break; }
    case 45:{ ui->pb_channel_45->setStyleSheet(style_pbChnl_Disable); break; }
    case 46:{ ui->pb_channel_46->setStyleSheet(style_pbChnl_Disable); break; }
    case 47:{ ui->pb_channel_47->setStyleSheet(style_pbChnl_Disable); break; }


    }
}

void ConfigChWin::on_timer_singleShot_elapsed()
{
    switch (index_SingleShotTimer) {
    case 0:{
        connectAllButtonsClickToSingleSlot();
        ui->pb_channel_0->clicked();
        emit tx_ChannelSettingsWindowIsOpen(true);
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

void ConfigChWin::connectAllButtonsClickToSingleSlot()
{
    qDebug()<<" ConfigChWin starting button signal slots ";
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
    qDebug()<<" ConfigChWin End button signal slots ";


}


void ConfigChWin::rx_ramdomOP(int idx, float val, QString str)
{
    switch (idx) {
    case 15179: {
        ui->lbl_Status->setText(str);
        break;
    }
    case 1: {
        qDebug()<<" ConfigChWin::rx_ramdomOP string is:: "<<str;
        break;
    }
    }
}


void ConfigChWin::rx_ChannelOLDSettings(int chnl, float fac, float pgaa, CHANNEL_TYPE typ, CHANNEL_REFERENCE ref)
{
    local_currentCH_ID = chnl;
    local_currentCH_Factor = fac;
    local_currentCH_PGA = pgaa;
    local_currentCH_type = typ;
    local_currentCH_Ref = ref;

    ui->lbl_Channel_ID->setText(QString::number(local_currentCH_ID+1));
    ui->sp_Channel_Factor->setValue(local_currentCH_Factor);
    ui->sp_Channel_PGA->setValue(local_currentCH_PGA);

    ui->lbl_Channel_Type->setText(QString(local_currentCH_type? "SINGLE ENDED":"BRIDGE"));

    ui->pb_ChannelReferenceToggle->setText(QString(local_currentCH_Ref? "External":"Internal"));
    ui->lbl_Status->setText("New Settings loaded of channel ID: "+QString::number(local_currentCH_ID+1));
}

void ConfigChWin::rx_ChannelValue(int chnl, float rawVal, float val)
{
    //qDebug()<<" Value Received : Chnnel = "<<chnl<<" value = "<<val;

    float newCalcu = rawVal * local_currentCH_Factor;
    ui->lcd_Ch_Value_New->display(QString::number(newCalcu, 'f', 2));
    ui->lcd_Ch_Value_OLD->display(QString::number(val, 'f', 2));
}

// ----------------- GUI Buttons ----------------------------
void ConfigChWin::on_pb_WindowClose_clicked()
{
    emit tx_ChannelSettingsWindowIsOpen(false);
    emit tx_generate_ThisGUI(gui_FIRST_WIN);
    emit tx_ClosingWindow_ConfigCHWin();
}
void ConfigChWin::on_sp_Channel_PGA_valueChanged(double arg1)
{
    local_currentCH_PGA = arg1;
}
void ConfigChWin::on_sp_Channel_Factor_valueChanged(double arg1)
{
    local_currentCH_Factor = arg1;
}
void ConfigChWin::on_pb_ChannelReferenceToggle_clicked()
{
    if(local_currentCH_Ref == INTERNAL) local_currentCH_Ref = EXTERNAL;
    else local_currentCH_Ref = INTERNAL;

    ui->pb_ChannelReferenceToggle->setText(QString(local_currentCH_Ref? "External":"Internal"));
}
void ConfigChWin::on_pb_SaveNewSettings_clicked()
{
    emit tx_setChannelNewSettings(local_currentCH_ID, local_currentCH_Factor, local_currentCH_PGA, local_currentCH_type, local_currentCH_Ref);

}






