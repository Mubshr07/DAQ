#ifndef CONFIGCHWIN_H
#define CONFIGCHWIN_H

#include <QDialog>

#include "classes/globalvars.h"


namespace Ui {
class ConfigChWin;
}

class ConfigChWin : public QDialog
{
    Q_OBJECT

public:
    explicit ConfigChWin(QWidget *parent = nullptr);
    ~ConfigChWin();

signals:
    void tx_setChannelNewSettings(int chnl, float fac, CHANNEL_PGA pgaa, CHANNEL_TYPE typ, CHANNEL_REFERENCE ref, bool enabled);
    void tx_ClosingWindow_ConfigCHWin();
    void tx_setSampleTime(int mSec);
    void tx_generate_ThisGUI(GUI_WIN guiEnum);
    void tx_giveMechannelSettings(int chnl);
    void tx_startReadingTimer(bool startReading);
    void tx_ChannelSettingsWindowIsOpen(bool windOpen);

public slots:
    void on_pb_Channel_Clicked();
    void connectAllButtonsClickToSingleSlot();

    void rx_ChannelOLDSettings(int chnl, float fac, CHANNEL_PGA pgaa, CHANNEL_TYPE typ, CHANNEL_REFERENCE ref, bool enb);
    void rx_ramdomOP(int idx, float val, QString str);
    void rx_ChannelValue_Config(int chnl, uint32_t raw, float fVal, float FacVal);

    void rx_EnableChannelsAre(int chnlID);

    void on_timer_singleShot_elapsed();




private slots:
    void on_sp_Channel_Factor_valueChanged(double arg1);
    void on_pb_ChannelReferenceToggle_clicked();
    void on_pb_SaveNewSettings_clicked();
    void on_pb_WindowClose_clicked();
    void on_pb_PGA_Minus_clicked();
    void on_pb_PGA_Plus_clicked();
    void on_pb_Channel_Enable_clicked();

    void on_cmb_ChannelType_currentIndexChanged(int index);
    void on_pb_StartConversion_clicked();
    void on_pb_GotoLogWindow_clicked();

    void on_pb_UploadAll_clicked();

private:
    Ui::ConfigChWin *ui;
    QTimer *timer_singleShot;
    int index_SingleShotTimer = 0;
    int uploadingAllIndex = 0;
    int accessibleName_int = 0;
    bool okVariable = false;
    QVariant localEnable = false;

    bool enabledChannels_Booleans[48] = {false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false};

    QString style_pbChnl_Enable = "font: 600 16pt 'Times New Roman'; padding: 4px; background-color:yellow; border: 2px solid white; border-radius: 5px; color:black;";
    QString style_pbChnl_Enable_EnabledTrue = "font: 600 16pt 'Times New Roman'; padding: 4px;background-color:rgb(170, 255, 255); border: 2px solid lime; border-radius: 5px; color:black;";
    QString style_pbChnl_Disable = "font: 600 16pt 'Times New Roman'; padding: 5px; background-color:rgb(170, 255, 255); border: 1px solid red; border-radius:5px; color:red; ";
    QString styleEnable = "font: 750 24pt 'MS Shell Dlg 2'; background-color: rgb(170, 255, 127); border:2px solid rgb(85, 170, 0); border-radius:10px;";
    QString styleDisable = "font: 750 24pt 'MS Shell Dlg 2'; background-color: red; border:2px solid rgb(85, 170, 0); border-radius:10px;";


    int local_currentCH_ID = 0;
    float local_currentCH_Factor = 1.0;
    //float local_currentCH_PGA = 1.0;
    CHANNEL_TYPE local_currentCH_type = BridgeCH;
    CHANNEL_PGA local_currentCH_PGA = CH_PGA_1;
    CHANNEL_REFERENCE local_currentCH_Ref = INTERNAL_REF;
    bool local_currentCH_Enable = false;

    QMap<CHANNEL_PGA, int> pgaMAP;

    int localFactrs_precision = 4;

    void normal_Button_Color(int idx);
    void uploadAllChannelConfigs();

    bool startReading_Bool = false;
    bool uploadingAll = false;

};

#endif // CONFIGCHWIN_H
