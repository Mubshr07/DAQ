#ifndef DEBUGWIN_H
#define DEBUGWIN_H

#include <QDialog>
#include "classes/globalvars.h"

namespace Ui {
class DebugWin;
}

class DebugWin : public QDialog
{
    Q_OBJECT

public:
    explicit DebugWin(QWidget *parent = nullptr);
    ~DebugWin();

signals:
    //void tx_read_ADC(int adcID, )




private slots:
    void on_pb_Close_clicked();
    void on_pb_Write_clicked();
    void on_pb_Read_clicked();
    void on_pb_Write_Auto_clicked();
    void on_pb_Write_Clock_clicked();
    void on_pb_Write_SampleRate_clicked();
    void on_pb_Write_New_clicked();
    void on_pb_Read_New_clicked();
    void on_timer_autoManualClicked();
    void on_pb_Write_Timer_clicked();

    void on_pb_ConfigADC_clicked();

private:
    Ui::DebugWin *ui;
    uint32_t *localFPGAaddr;

    int writeRegister(uint8_t addr, uint8_t val);
    uint32_t readRegister(uint8_t addr);
    void selectedADC(int id);
    void ConfigADC();
    void startConversion();
    void readData();


    QTimer *timer_autoManualClick;
};

#endif // DEBUGWIN_H
