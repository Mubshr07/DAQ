#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "classes/globalvars.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void tx_setChannelEnable(int chnl, bool enable);
    void tx_setSampleTime(int mSec);
    void tx_ClosingWindow_logConfig();
    void tx_generate_ThisGUI(GUI_WIN guiEnum);
    void tx_sendFactorsAndPGAs_AllChnls();
    void tx_loggingStartStop(bool started, QString filePath);

public slots:
    void on_pb_Channel_Clicked();
    void connectAllButtonsClickToSingleSlot();
    void disableLCDNumber(int indx);
    void showFactorLabel(int indx);

    void rx_ChannelValue(int chnl, uint32_t raw, float fVal, float val);
    void rx_sendingFactorsAndPGAs(int chnl, float fac, float pgaa, bool enabled);

    void rx_ramdomOP(int idx, float val, QString str);

    void rx_confirmationBoxClosed(bool yesBTN, int param);




    void on_timer_singleShot_elapsed();
    void on_timer_enabler_elapsed();



private slots:
    void on_pb_CloseApp_clicked();

    void on_slider_samplingRate_valueChanged(int value);
    void on_txt_SampleTime_valueChanged(int arg1);
    void on_pb_EnableAll_clicked();
    void on_pb_DisableAll_clicked();
    void on_pb_StartLog_clicked();

    void on_pb_ConfigChannelSettings_clicked();

    void on_pb_ShowGraphWin_clicked();

private:
    Ui::MainWindow *ui;
    QTimer *timer_singleShot;
    QTimer *timer_enabler;

    ConfirmationBox *msgBox;


    bool local_loggingStarted = false;
    QString logUserFilePath = "";

    int index_SingleShotTimer = 0;
    int index_Enabler = 0;

    Qt::GlobalColor lcdNumber_colorPallet = Qt::white;

    int accessibleName_int = 0;
    bool okVariable = false;
    QVariant localEnable = false;

    QString style_pbChnl_Enable = "font: 600 16pt 'Times New Roman'; padding: 4px; background-color:lime; border: 2px solid white; border-radius: 5px";
    QString style_pbChnl_Disable = "font: 600 16pt 'Times New Roman'; padding: 5px; background-color: rgb(255, 255, 255); border: 1px solid red; border-radius:5px; ";
    int lcdNumberPrecision = 1;
    int factorPrecision = 3;

    QString styleLogStop = "font: 600 20pt 'Times New Roman'; padding: 5px; background-color: rgb(255, 255, 255); border: 1px solid black; border-radius:5px; color:red;";
    QString styleLogStart = "font: 600 20pt 'Times New Roman'; padding: 5px; background-color: lime; border: 1px solid black; border-radius:5px; color:white;";

    QString lblStyle_normal = "color:white;";
    QString lblStyle_transparent = "color:transparent;";


    void setChannel_toEnabledDisable(int idx, bool enabled);


};
#endif // MAINWINDOW_H
