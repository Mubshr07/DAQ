#include "debugwin.h"
#include "ui_debugwin.h"

DebugWin::DebugWin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DebugWin)
{
    ui->setupUi(this);

    localFPGAaddr = globalVars::global_FPGA_ADDR;


    timer_autoManualClick = new QTimer(this);
    connect(timer_autoManualClick, SIGNAL(timeout()), this, SLOT(on_timer_autoManualClicked()));
    timer_autoManualClick->setInterval(1000);
    //timer_autoManualClick->start();
}

DebugWin::~DebugWin()
{
    delete ui;
}

void DebugWin::on_pb_Close_clicked()
{
    this->close();
}
void DebugWin::on_pb_Write_clicked()
{
    int adcIndx = ui->sp_write_ADC_Index->value()-1;
    QString addrTxt = ui->txt_Write_Register->toPlainText();
    QString valTxt = ui->txt_Write_Value->toPlainText();
    bool okVar = false;
    uint addInt = addrTxt.toInt(&okVar, 10);
    uint valInt = valTxt.toInt(&okVar, 10);
    okVar = false;

    qDebug()<<"Write:: adc: "<<adcIndx<<" addr(int):"<<addInt<<" Val:"<<valTxt.toUInt(&okVar, 10);

    *(localFPGAaddr+ addInt) = valInt;
    //    *(localFPGAaddr+ 0x01) = adcIndx;
    //    *(localFPGAaddr+ 0x02) = 0x02;
    //    *(localFPGAaddr+ 0x03) = 0xAABBCCDD; //valTxt.toUInt(&okVar, 16);
    //    *(localFPGAaddr+ 0x04) = 0xAABBCCDD; //valTxt.toUInt(&okVar, 16);
    //    *(localFPGAaddr+ 0x05) = 0xAABBCCDD; //valTxt.toUInt(&okVar, 16);
    *(localFPGAaddr+ 0x06) = 0x00;
    usleep(1000);
    *(localFPGAaddr+ 0x08) = 0x00;
    *(localFPGAaddr+ 0x08) = 0x01; // PULSE
    *(localFPGAaddr+ 0x08) = 0x00;

    //*(localFPGAaddr+ addInt) = valTxt.toUInt(&okVar, 16);

}
void DebugWin::on_pb_Read_clicked()
{
    int adcIndx = ui->sp_read_ADC_Index->value()-1;
    QString addrTxt = ui->txt_Read_Register->toPlainText();
    bool okVar = false;
    int8_t addInt = addrTxt.toInt(&okVar);

    okVar = false;


    selectedADC(adcIndx);
    ui->lbl_read_result->setText(QString::number(readRegister(addInt), 16));
    qDebug()<<"Read:: adc: "<<adcIndx<<" addr(int8_t):"<<addInt<<" Val(Hex)::"<<QString::number(readRegister(addInt), 16)<<" Val(deci)::"<<readRegister(addInt) ;
}
void DebugWin::on_pb_Write_Auto_clicked()
{
    *(localFPGAaddr+ 0x06) = 0x01;
    *(localFPGAaddr+ 0x07) = 0x00;
    *(localFPGAaddr+ 0x07) = 0x01; // PULSE
    *(localFPGAaddr+ 0x07) = 0x00;
}
void DebugWin::on_pb_Write_Clock_clicked()
{
    //int adcIndx = ui->sp_write_ADC_Index->value()-1;
    //QString addrTxt = ui->txt_Write_Register->toPlainText();
    QString valTxt = ui->txt_Write_Value->toPlainText();
    bool okVar = false;
    //uint addInt = addrTxt.toInt(&okVar, 10);
    uint32_t valInt = valTxt.toUInt(&okVar, 10);
    okVar = false;

    //qDebug()<<"Write:: adc: "<<adcIndx<<" addr(int):"<<addInt<<" Val:"<<valTxt.toUInt(&okVar, 10);
    //valInt *= 1000;
    valInt /= 0.02;
    *(localFPGAaddr+ 0x00) = valInt;
}
void DebugWin::on_pb_Write_SampleRate_clicked()
{
    //int adcIndx = ui->sp_write_ADC_Index->value()-1;
    //QString addrTxt = ui->txt_Write_Register->toPlainText();
    QString valTxt = ui->txt_Write_Value->toPlainText();
    bool okVar = false;
    //uint addInt = addrTxt.toInt(&okVar, 10);
    uint32_t valInt = valTxt.toUInt(&okVar, 10);
    okVar = false;

    //qDebug()<<"Write:: adc: "<<adcIndx<<" addr(int):"<<addInt<<" Val:"<<valTxt.toUInt(&okVar, 10);
    //valInt *= 1000;
    valInt /= 0.02;
    *(localFPGAaddr + 14) = valInt;
}

int DebugWin::writeRegister(uint8_t addr, uint8_t val)
{
    uint8_t wReg = 0x40;
    uint8_t address = 0x00;
    address = (wReg|(addr<<2));
    uint32_t sendValue = 0x00;


    sendValue = ((val<<8) & 0xff00) + (address & 0xff);
    *(localFPGAaddr + 0x02)  = 0x02;
    *(localFPGAaddr + 0x06)  = 0x00;
    *(localFPGAaddr + 0x03)  = sendValue;
    *(localFPGAaddr + 0x08) = 0x00;     // Pulse
    *(localFPGAaddr + 0x08) = 0x01;
    *(localFPGAaddr + 0x08) = 0x00;
    qDebug()<<"\t\t WriteRegister Method: Addr: "<<address<<" val: "<<val<<" mosi:"<<sendValue<<"\n";
    return  1;
}
uint32_t DebugWin::readRegister(uint8_t addr)
{
    uint8_t val = 0x00;
    uint8_t rReg = 0x20;
    val = (rReg| (addr<<2));
    *(localFPGAaddr + 0x03) = val;
    *(localFPGAaddr + 0x02) = 0x02;
    *(localFPGAaddr + 0x08) = 0x00; // pulse
    *(localFPGAaddr + 0x08) = 0x01;
    *(localFPGAaddr + 0x08) = 0x00;


    //usleep(100000);
    uint16_t lsb = *(localFPGAaddr+48);
    uint16_t msb = *(localFPGAaddr+49);
    uint32_t reply = (msb<<16 & 0xffff0000) + (lsb & 0xffff);
    return reply;
}

void DebugWin::selectedADC(int id)
{
    *(localFPGAaddr + 0x01) = id;
}
void DebugWin::on_pb_Write_New_clicked()
{
    int adcIndx = ui->sp_write_ADC_Index->value()-1;
    QString addrTxt = ui->txt_Write_Register->toPlainText();
    QString valTxt = ui->txt_Write_Value->toPlainText();
    bool okVar = false;
    uint8_t addInt = addrTxt.toInt(&okVar, 10);
    okVar = false;
    uint8_t valInt = valTxt.toInt(&okVar, 10);
    okVar = false;

    qDebug()<<"Write:: adc: "<<adcIndx<<" addr(int):"<<addInt<<" Val:"<<valTxt.toUInt(&okVar, 10);

    selectedADC(adcIndx);
    writeRegister(addInt, valInt);
}
void DebugWin::on_pb_Read_New_clicked()
{
    QString addrTxt = ui->txt_Write_Register->toPlainText();

    bool okVar = false;
    uint8_t addInt = addrTxt.toInt(&okVar, 10);
    okVar = false;
    uint32_t readThis = readRegister(addInt);

    qDebug()<<" Reading ADC Register:"<<addInt<<" value: "<<QString::number(readThis, 16)<<"";
}
void DebugWin::on_timer_autoManualClicked()
{
    //on_pb_Write_New_clicked();
    //on_pb_Read_New_clicked();
    readData();
}

void DebugWin::on_pb_Write_Timer_clicked()
{
    if(timer_autoManualClick->isActive())
    {
        timer_autoManualClick->stop();
        ui->pb_Write_Timer->setStyleSheet("background-color: red;");
    }
    else
    {
        timer_autoManualClick->start();
        ui->pb_Write_Timer->setStyleSheet("background-color: lime;");
    }
}
void DebugWin::ConfigADC()
{
    *(localFPGAaddr+0x01) = 0x00;
    *(localFPGAaddr+0x06) = 0x00;
    usleep(1000);
    writeRegister(0x00, 0x00);
    usleep(1000);
    writeRegister(0x01, 0xC4);
    usleep(1000);
    writeRegister(0x02, 0x10);
    usleep(1000);
    writeRegister(0x03, 0x00);
    usleep(1000);

    writeRegister(0x04, 0x00);
    usleep(10000);
    startConversion();

    usleep(10000);
    qDebug()<<" ADC Configured ";


}

void DebugWin::startConversion()
{

    *(localFPGAaddr + 0x02)  = 0x01;
    *(localFPGAaddr + 0x06)  = 0x00;
    *(localFPGAaddr + 0x03)  = 0x08;
    *(localFPGAaddr + 0x08) = 0x00;     // Pulse
    *(localFPGAaddr + 0x08) = 0x01;
    *(localFPGAaddr + 0x08) = 0x00;
    //qDebug()<<"\t\t WriteRegister Method: Addr: "<<address<<" val: "<<val<<" mosi:"<<sendValue<<"\n";
}
void DebugWin::readData()
{
    *(localFPGAaddr + 0x02)  = 0x03;
    *(localFPGAaddr + 0x06)  = 0x00;
    *(localFPGAaddr + 0x03)  = 0xFF;
    *(localFPGAaddr + 0x08) = 0x00;     // Pulse
    *(localFPGAaddr + 0x08) = 0x01;
    *(localFPGAaddr + 0x08) = 0x00;
    //qDebug()<<"\t\t WriteRegister Method: Addr: "<<address<<" val: "<<val<<" mosi:"<<sendValue<<"\n";

    uint16_t lsb  = *(localFPGAaddr + 48);
    uint16_t msb  = *(localFPGAaddr + 49);

    uint32_t dd = (((msb&0xFF)<<16)&0xFFFF0000)+ (lsb&0xFF);
    ui->lbl_read_result->setText(QString::number(dd, 16));

    qDebug()<<" readData() method:: value (hex):"<<QString::number(dd, 16);
}

void DebugWin::on_pb_ConfigADC_clicked()
{
    ConfigADC();
}



