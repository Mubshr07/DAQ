#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "classes/globalvars.h"
#include "classes/chnlclass_simple.h"
#include "classes/loggerthread.h"
#include "graphwin.h"

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
    void tx_setSampleTime(int sec);




public slots:
    void on_pb_Channel_Clicked();
    void connectAllButtonsClickToSingleSlot();
    void disableLCDNumber(int indx);

    void rx_ChannelValue(int chnl, float val);


    void on_timer_singleShot_elapsed();
    void on_timer_enabler_elapsed();



private slots:
    void on_pb_SetConfiguration_clicked();
    void on_pb_CloseApp_clicked();

private:
    Ui::MainWindow *ui;
    QTimer *timer_singleShot;
    QTimer *timer_enabler;

    loggerThread *loggerClass;
    QThread *thrd;
    graphWin *grphW;

    int index_SingleShotTimer = 0;
    int index_Enabler = 0;

    Qt::GlobalColor lcdNumber_colorPallet = Qt::red;

    int accessibleName_int = 0;
    bool okVariable = false;
    QVariant localEnable = false;

    QString style_pbChnl_Enable = "font: 600 20pt 'Times New Roman'; padding: 4px; background-color:lime; border: 2px solid white; border-radius: 5px";
    QString style_pbChnl_Disable = "font: 600 20pt 'Times New Roman'; padding: 5px; background-color: rgb(255, 255, 255); border: 1px solid red; border-radius:5px; ";
    int lcdNumberPrecision = 2;


};
#endif // MAINWINDOW_H
