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
    timer_singleShot->start(250);

    pgaMAP.clear();
    pgaMAP.insert(CH_PGA_1, 1);
    pgaMAP.insert(CH_PGA_2, 2);
    pgaMAP.insert(CH_PGA_4, 4);
    pgaMAP.insert(CH_PGA_8, 8);
    pgaMAP.insert(CH_PGA_16, 16);
    pgaMAP.insert(CH_PGA_32, 32);
    pgaMAP.insert(CH_PGA_64, 64);
    pgaMAP.insert(CH_PGA_128, 128);


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


void ConfigChWin::rx_EnableChannelsAre(int chnlID)
{
    if(chnlID < TOTAL_CHANNEL)  enabledChannels_Booleans[chnlID] = true;
    else if(chnlID == 15179) {
        for(int i=0; i<TOTAL_CHANNEL; i++)
        {
            normal_Button_Color(i);
        }
    }
}

void ConfigChWin::normal_Button_Color(int idx)
{
    switch (idx) {
    case 0:{ ui->pb_channel_0->setStyleSheet(QString(enabledChannels_Booleans[idx]? style_pbChnl_Enable_EnabledTrue : style_pbChnl_Disable)); break; }
    case 1:{ ui->pb_channel_1->setStyleSheet(QString(enabledChannels_Booleans[idx]? style_pbChnl_Enable_EnabledTrue : style_pbChnl_Disable)); break; }
    case 2:{ ui->pb_channel_2->setStyleSheet(QString(enabledChannels_Booleans[idx]? style_pbChnl_Enable_EnabledTrue:style_pbChnl_Disable)); break; }
    case 3:{ ui->pb_channel_3->setStyleSheet(QString(enabledChannels_Booleans[idx]? style_pbChnl_Enable_EnabledTrue:style_pbChnl_Disable)); break; }
    case 4:{ ui->pb_channel_4->setStyleSheet(QString(enabledChannels_Booleans[idx]? style_pbChnl_Enable_EnabledTrue:style_pbChnl_Disable)); break; }
    case 5:{ ui->pb_channel_5->setStyleSheet(QString(enabledChannels_Booleans[idx]? style_pbChnl_Enable_EnabledTrue:style_pbChnl_Disable)); break; }
    case 6:{ ui->pb_channel_6->setStyleSheet(QString(enabledChannels_Booleans[idx]? style_pbChnl_Enable_EnabledTrue:style_pbChnl_Disable)); break; }
    case 7:{ ui->pb_channel_7->setStyleSheet(QString(enabledChannels_Booleans[idx]? style_pbChnl_Enable_EnabledTrue:style_pbChnl_Disable)); break; }
    case 8:{ ui->pb_channel_8->setStyleSheet(QString(enabledChannels_Booleans[idx]? style_pbChnl_Enable_EnabledTrue:style_pbChnl_Disable)); break; }
    case 9:{ ui->pb_channel_9->setStyleSheet(QString(enabledChannels_Booleans[idx]? style_pbChnl_Enable_EnabledTrue:style_pbChnl_Disable)); break; }
    case 10:{ ui->pb_channel_10->setStyleSheet(QString(enabledChannels_Booleans[idx]? style_pbChnl_Enable_EnabledTrue:style_pbChnl_Disable)); break; }

    case 11:{ ui->pb_channel_11->setStyleSheet(QString(enabledChannels_Booleans[idx]? style_pbChnl_Enable_EnabledTrue:style_pbChnl_Disable)); break; }
    case 12:{ ui->pb_channel_12->setStyleSheet(QString(enabledChannels_Booleans[idx]? style_pbChnl_Enable_EnabledTrue:style_pbChnl_Disable)); break; }
    case 13:{ ui->pb_channel_13->setStyleSheet(QString(enabledChannels_Booleans[idx]? style_pbChnl_Enable_EnabledTrue:style_pbChnl_Disable)); break; }
    case 14:{ ui->pb_channel_14->setStyleSheet(QString(enabledChannels_Booleans[idx]? style_pbChnl_Enable_EnabledTrue:style_pbChnl_Disable)); break; }
    case 15:{ ui->pb_channel_15->setStyleSheet(QString(enabledChannels_Booleans[idx]? style_pbChnl_Enable_EnabledTrue:style_pbChnl_Disable)); break; }
    case 16:{ ui->pb_channel_16->setStyleSheet(QString(enabledChannels_Booleans[idx]? style_pbChnl_Enable_EnabledTrue:style_pbChnl_Disable)); break; }
    case 17:{ ui->pb_channel_17->setStyleSheet(QString(enabledChannels_Booleans[idx]? style_pbChnl_Enable_EnabledTrue:style_pbChnl_Disable)); break; }
    case 18:{ ui->pb_channel_18->setStyleSheet(QString(enabledChannels_Booleans[idx]? style_pbChnl_Enable_EnabledTrue:style_pbChnl_Disable)); break; }
    case 19:{ ui->pb_channel_19->setStyleSheet(QString(enabledChannels_Booleans[idx]? style_pbChnl_Enable_EnabledTrue:style_pbChnl_Disable)); break; }
    case 20:{ ui->pb_channel_20->setStyleSheet(QString(enabledChannels_Booleans[idx]? style_pbChnl_Enable_EnabledTrue:style_pbChnl_Disable)); break; }

    case 21:{ ui->pb_channel_21->setStyleSheet(QString(enabledChannels_Booleans[idx]? style_pbChnl_Enable_EnabledTrue:style_pbChnl_Disable)); break; }
    case 22:{ ui->pb_channel_22->setStyleSheet(QString(enabledChannels_Booleans[idx]? style_pbChnl_Enable_EnabledTrue:style_pbChnl_Disable)); break; }
    case 23:{ ui->pb_channel_23->setStyleSheet(QString(enabledChannels_Booleans[idx]? style_pbChnl_Enable_EnabledTrue:style_pbChnl_Disable)); break; }
    case 24:{ ui->pb_channel_24->setStyleSheet(QString(enabledChannels_Booleans[idx]? style_pbChnl_Enable_EnabledTrue:style_pbChnl_Disable)); break; }
    case 25:{ ui->pb_channel_25->setStyleSheet(QString(enabledChannels_Booleans[idx]? style_pbChnl_Enable_EnabledTrue:style_pbChnl_Disable)); break; }
    case 26:{ ui->pb_channel_26->setStyleSheet(QString(enabledChannels_Booleans[idx]? style_pbChnl_Enable_EnabledTrue:style_pbChnl_Disable)); break; }
    case 27:{ ui->pb_channel_27->setStyleSheet(QString(enabledChannels_Booleans[idx]? style_pbChnl_Enable_EnabledTrue:style_pbChnl_Disable)); break; }
    case 28:{ ui->pb_channel_28->setStyleSheet(QString(enabledChannels_Booleans[idx]? style_pbChnl_Enable_EnabledTrue:style_pbChnl_Disable)); break; }
    case 29:{ ui->pb_channel_29->setStyleSheet(QString(enabledChannels_Booleans[idx]? style_pbChnl_Enable_EnabledTrue:style_pbChnl_Disable)); break; }
    case 30:{ ui->pb_channel_30->setStyleSheet(QString(enabledChannels_Booleans[idx]? style_pbChnl_Enable_EnabledTrue:style_pbChnl_Disable)); break; }

    case 31:{ ui->pb_channel_31->setStyleSheet(QString(enabledChannels_Booleans[idx]? style_pbChnl_Enable_EnabledTrue:style_pbChnl_Disable)); break; }
    case 32:{ ui->pb_channel_32->setStyleSheet(QString(enabledChannels_Booleans[idx]? style_pbChnl_Enable_EnabledTrue:style_pbChnl_Disable)); break; }
    case 33:{ ui->pb_channel_33->setStyleSheet(QString(enabledChannels_Booleans[idx]? style_pbChnl_Enable_EnabledTrue:style_pbChnl_Disable)); break; }
    case 34:{ ui->pb_channel_34->setStyleSheet(QString(enabledChannels_Booleans[idx]? style_pbChnl_Enable_EnabledTrue:style_pbChnl_Disable)); break; }
    case 35:{ ui->pb_channel_35->setStyleSheet(QString(enabledChannels_Booleans[idx]? style_pbChnl_Enable_EnabledTrue:style_pbChnl_Disable)); break; }
    case 36:{ ui->pb_channel_36->setStyleSheet(QString(enabledChannels_Booleans[idx]? style_pbChnl_Enable_EnabledTrue:style_pbChnl_Disable)); break; }
    case 37:{ ui->pb_channel_37->setStyleSheet(QString(enabledChannels_Booleans[idx]? style_pbChnl_Enable_EnabledTrue:style_pbChnl_Disable)); break; }
    case 38:{ ui->pb_channel_38->setStyleSheet(QString(enabledChannels_Booleans[idx]? style_pbChnl_Enable_EnabledTrue:style_pbChnl_Disable)); break; }
    case 39:{ ui->pb_channel_39->setStyleSheet(QString(enabledChannels_Booleans[idx]? style_pbChnl_Enable_EnabledTrue:style_pbChnl_Disable)); break; }
    case 40:{ ui->pb_channel_40->setStyleSheet(QString(enabledChannels_Booleans[idx]? style_pbChnl_Enable_EnabledTrue:style_pbChnl_Disable)); break; }

    case 41:{ ui->pb_channel_41->setStyleSheet(QString(enabledChannels_Booleans[idx]? style_pbChnl_Enable_EnabledTrue:style_pbChnl_Disable)); break; }
    case 42:{ ui->pb_channel_42->setStyleSheet(QString(enabledChannels_Booleans[idx]? style_pbChnl_Enable_EnabledTrue:style_pbChnl_Disable)); break; }
    case 43:{ ui->pb_channel_43->setStyleSheet(QString(enabledChannels_Booleans[idx]? style_pbChnl_Enable_EnabledTrue:style_pbChnl_Disable)); break; }
    case 44:{ ui->pb_channel_44->setStyleSheet(QString(enabledChannels_Booleans[idx]? style_pbChnl_Enable_EnabledTrue:style_pbChnl_Disable)); break; }
    case 45:{ ui->pb_channel_45->setStyleSheet(QString(enabledChannels_Booleans[idx]? style_pbChnl_Enable_EnabledTrue:style_pbChnl_Disable)); break; }
    case 46:{ ui->pb_channel_46->setStyleSheet(QString(enabledChannels_Booleans[idx]? style_pbChnl_Enable_EnabledTrue:style_pbChnl_Disable)); break; }
    case 47:{ ui->pb_channel_47->setStyleSheet(QString(enabledChannels_Booleans[idx]? style_pbChnl_Enable_EnabledTrue:style_pbChnl_Disable)); break; }


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
        uploadAllChannelConfigs();
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
    //qDebug()<<" ConfigChWin starting button signal slots ";
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
    //qDebug()<<" ConfigChWin End button signal slots ";


}


void ConfigChWin::rx_ramdomOP(int idx, float val, QString str)
{
    switch (idx) {
    case 15179: {
        if(!uploadingAll) ui->lbl_Status->setText(str);
        break;
    }
    case 1: {
        //qDebug()<<" ConfigChWin::rx_ramdomOP string is:: "<<str;
        break;
    }
    }
}


void ConfigChWin::rx_ChannelOLDSettings(int chnl, float fac, CHANNEL_PGA pgaa, CHANNEL_TYPE typ, CHANNEL_REFERENCE ref, bool enb)
{
    //qDebug()<<"rx_ChannelOLDSettings:: chnl:"<<chnl<<" fact:"<<fac<<" pga:"<<pgaa<<" type:"<<typ<<" ref:"<<ref<<" enable:"<<enb;
    local_currentCH_ID = chnl;
    local_currentCH_Factor = fac;
    local_currentCH_PGA = pgaa;
    local_currentCH_type = typ;
    local_currentCH_Ref = ref;
    local_currentCH_Enable = enb;


    ui->lbl_Channel_ID->setText(QString::number(local_currentCH_ID+1));
    ui->sp_Channel_Factor->setValue(local_currentCH_Factor);
    //ui->sp_Channel_PGA->setValue(local_currentCH_PGA);
    ui->lbl_PGA_Channel->setText(QString::number(pgaMAP.value(local_currentCH_PGA)));

    int typeIndex = local_currentCH_type;
    ui->cmb_ChannelType->setCurrentIndex(typeIndex);


    ui->pb_Channel_Enable->setStyleSheet(QString(local_currentCH_Enable? styleEnable : styleDisable));
    ui->pb_Channel_Enable->setText(QString(local_currentCH_Enable? "Enabled": "Disabled"));

    ui->pb_ChannelReferenceToggle->setText(QString(local_currentCH_Ref? "External":"Internal"));
    ui->lbl_Status->setText("New Settings loaded of channel ID: "+QString::number(local_currentCH_ID+1));
}

void ConfigChWin::rx_ChannelValue(int chnl, uint32_t raw, float fVal, float FacVal)
{
    //qDebug()<<" Value Received : Chnnel = "<<chnl<<" value = "<<val;

    float newCalcu = fVal * local_currentCH_Factor;
    ui->lcd_Ch_Value_Raw->display(QString::number(raw, 16));
    ui->lcd_Ch_Value_floating->display(QString::number(fVal, 'f', 2));
    ui->lcd_Ch_Value_floatingFactor->display(QString::number(newCalcu, 'f', 2));
}

// ----------------- GUI Buttons ----------------------------
void ConfigChWin::on_pb_WindowClose_clicked()
{
    emit tx_ChannelSettingsWindowIsOpen(false);
    //emit tx_generate_ThisGUI(gui_FIRST_WIN);
    emit tx_ClosingWindow_ConfigCHWin();
}

void ConfigChWin::on_sp_Channel_Factor_valueChanged(double arg1)
{
    local_currentCH_Factor = arg1;
}
void ConfigChWin::on_pb_ChannelReferenceToggle_clicked()
{
    if(local_currentCH_Ref == INTERNAL_REF) local_currentCH_Ref = EXTERNAL_REF;
    else local_currentCH_Ref = INTERNAL_REF;

    ui->pb_ChannelReferenceToggle->setText(QString(local_currentCH_Ref? "External":"Internal"));
}
void ConfigChWin::on_pb_SaveNewSettings_clicked()
{
    emit tx_setChannelNewSettings(local_currentCH_ID, local_currentCH_Factor, local_currentCH_PGA, local_currentCH_type, local_currentCH_Ref,local_currentCH_Enable);
    QString str = QString::number(local_currentCH_ID);
        str += " channel settings are Uploaded.";
    ui->lbl_Status->setText(str);
}

void ConfigChWin::on_pb_PGA_Minus_clicked()
{
    int locaa = local_currentCH_PGA;
    //qDebug()<<" Locaa:: "<<locaa;
    if(locaa < 1 ) return;  // {locaa = 0; return; }

    locaa--;
    local_currentCH_PGA = (CHANNEL_PGA) locaa;
    ui->lbl_PGA_Channel->setText(QString::number(pgaMAP.value(local_currentCH_PGA)));
}
void ConfigChWin::on_pb_PGA_Plus_clicked()
{
    int locaa = local_currentCH_PGA;
    //qDebug()<<" Locaa:: "<<locaa;
    if(locaa > 6 ) return;
    locaa++;
    local_currentCH_PGA = (CHANNEL_PGA) locaa;
    ui->lbl_PGA_Channel->setText(QString::number(pgaMAP.value(local_currentCH_PGA)));
}
void ConfigChWin::on_pb_Channel_Enable_clicked()
{
    local_currentCH_Enable =  !local_currentCH_Enable;
    ui->pb_Channel_Enable->setStyleSheet(QString(local_currentCH_Enable? styleEnable : styleDisable));
    ui->pb_Channel_Enable->setText(QString(local_currentCH_Enable? "Enabled": "Disabled"));

    enabledChannels_Booleans[local_currentCH_ID] = local_currentCH_Enable;

}

void ConfigChWin::on_cmb_ChannelType_currentIndexChanged(int index)
{
    local_currentCH_type = (CHANNEL_TYPE) index;
}
void ConfigChWin::on_pb_StartConversion_clicked()
{
    startReading_Bool = !startReading_Bool;
    emit tx_startReadingTimer(startReading_Bool);
    ui->pb_StartConversion->setStyleSheet(QString(startReading_Bool? styleEnable : styleDisable));
    ui->pb_StartConversion->setText(QString(startReading_Bool? "Started Read":"Stopped Read"));
    ui->lbl_Status->setText("Listening Current Channel Readings.");
}
void ConfigChWin::on_pb_GotoLogWindow_clicked()
{
//    emit tx_ChannelSettingsWindowIsOpen(false);
//    emit tx_setSampleTime((int)(ui->txt_SampleTime->value() * 1000.0));
//    emit tx_generate_ThisGUI(gui_GRAPH_WIN);
//    emit tx_ClosingWindow_ConfigCHWin();
}
void ConfigChWin::on_pb_UploadAll_clicked()
{
    uploadingAll = true;
    index_SingleShotTimer = 1;
    uploadingAllIndex = 0;
    uploadAllChannelConfigs();
    timer_singleShot->start(800);
//    for(int i=0; i<TOTAL_CHANNEL; i++)
//    {
//        emit tx_setChannelNewSettings(i, local_currentCH_Factor, local_currentCH_PGA, local_currentCH_type, local_currentCH_Ref, local_currentCH_Enable);
//        ui->lbl_Status->setText(QString(QString::number(i)+ " channel settings are Uploaded."));
//        usleep(500000);
//    }
//    ui->lbl_Status->setText(" All Channels Configured");
}
void ConfigChWin::uploadAllChannelConfigs()
{
    emit tx_setChannelNewSettings(uploadingAllIndex, local_currentCH_Factor, local_currentCH_PGA, local_currentCH_type, local_currentCH_Ref, local_currentCH_Enable);
    ui->lbl_Status->setText(QString(QString::number(uploadingAllIndex)+ " channel settings are Uploaded."));
    if(uploadingAllIndex<47) timer_singleShot->start(800);
    if(uploadingAllIndex >= 47) {
        ui->lbl_Status->setText(QString("All channels settings are Uploaded."));
        uploadingAll = false;
    }
    uploadingAllIndex++;
}



