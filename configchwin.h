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
    void tx_setChannelNewSettings(int chnl, float fac, float pgaa, CHANNEL_TYPE typ, CHANNEL_REFERENCE ref);
    void tx_ClosingWindow_ConfigCHWin();
    void tx_generate_ThisGUI(GUI_WIN guiEnum);
    void tx_giveMechannelSettings(int chnl);

    void tx_ChannelSettingsWindowIsOpen(bool windOpen);

public slots:
    void on_pb_Channel_Clicked();
    void connectAllButtonsClickToSingleSlot();

    void rx_ChannelOLDSettings(int chnl, float fac, float pgaa, CHANNEL_TYPE typ, CHANNEL_REFERENCE ref);
    void rx_ramdomOP(int idx, float val, QString str);
    void rx_ChannelValue(int chnl, float rawVal, float val);


    void on_timer_singleShot_elapsed();




private slots:
    void on_sp_Channel_PGA_valueChanged(double arg1);
    void on_sp_Channel_Factor_valueChanged(double arg1);
    void on_pb_ChannelReferenceToggle_clicked();
    void on_pb_SaveNewSettings_clicked();
    void on_pb_WindowClose_clicked();

    void on_pb_PGA_Minus_clicked();

    void on_pb_PGA_Plus_clicked();

private:
    Ui::ConfigChWin *ui;
    QTimer *timer_singleShot;
    int index_SingleShotTimer = 0;
    int accessibleName_int = 0;
    bool okVariable = false;
    QVariant localEnable = false;

    QString style_pbChnl_Enable = "font: 600 16pt 'Times New Roman'; padding: 4px; background-color:lime; border: 2px solid white; border-radius: 5px";
    QString style_pbChnl_Disable = "font: 600 16pt 'Times New Roman'; padding: 5px; background-color:rgb(170, 255, 255); border: 1px solid red; border-radius:5px; ";

    int local_currentCH_ID = 0;
    float local_currentCH_Factor = 1.0;
    float local_currentCH_PGA = 1.0;
    CHANNEL_TYPE local_currentCH_type = BRIDGE;
    CHANNEL_REFERENCE local_currentCH_Ref = INTERNAL;


    int localFactrs_precision = 4;

    void normal_Button_Color(int idx);




};

#endif // CONFIGCHWIN_H
