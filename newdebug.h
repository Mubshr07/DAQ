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
    void on_pb_ReadConversion_clicked();
    void on_pb_ADC_Number_clicked();
    void on_pb_setClock_clicked();
    void on_pb_samplingRate_clicked();
    void on_pb_writeRegister_1_clicked();
    void on_pb_writeRegister_2_clicked();
    void on_pb_writeRegister_3_clicked();
    void on_pb_writeRegister_4_clicked();

    void on_pb_Timer_clicked();



    void on_timer_autoManualClicked();
    void on_pb_readRegister_clicked();

private:
    Ui::NewDebug *ui;

    uint32_t *localFPGAaddr;

    int writeRegister(uint8_t addr, uint8_t val);
    uint32_t readRegister(uint8_t addr);



    void readData();


    QTimer *timer_autoManualClick;


};

#endif // NEWDEBUG_H
