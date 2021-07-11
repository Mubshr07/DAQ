#ifndef NEWDEBUG_H
#define NEWDEBUG_H

#include <QDialog>
#include "classes/globalvars.h"

namespace Ui {
class NewDebug;
}

class NewDebug : public QDialog
{
    Q_OBJECT

public:
    explicit NewDebug(QWidget *parent = nullptr);
    ~NewDebug();

private slots:
    void on_pb_Reset_clicked();
    void on_pb_StartConversion_clicked();
    uint32_t on_pb_ReadConversion_clicked();
    void on_pb_ADC_Number_clicked();
    void on_pb_setClock_clicked();
    void on_pb_samplingRate_clicked();
    void on_pb_writeRegister_1_clicked();
    void on_pb_writeRegister_2_clicked();
    void on_pb_writeRegister_3_clicked();
    void on_pb_writeRegister_4_clicked();

    void on_pb_Timer_clicked();



    void on_timer_autoManualClicked();
    void on_timer_configRegister_Elapsed();


    void on_pb_readRegister_clicked();

    void on_pb_readRegister_2_clicked();

    void on_pb_read_ALLChannels_clicked();

    void on_pb_ConfigAll_clicked();

    void on_pb_read_Automatic_clicked();

private:
    Ui::NewDebug *ui;

    uint32_t *localFPGAaddr;

    int writeRegister(uint8_t addr, uint8_t val);
    uint32_t readRegister(uint8_t addr);

    float getCalculatedFromRawValue(uint32_t raw);
    bool autoMode_isEnable = false;

    void readData();

    void showValueofPCB_Channels(int idx, float val);

    QTimer *timer_autoManualClick;
    QTimer *timer_configRegister;


};

#endif // NEWDEBUG_H
