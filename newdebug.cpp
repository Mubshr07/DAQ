#include "newdebug.h"
#include "ui_newdebug.h"

NewDebug::NewDebug(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewDebug)
{
    ui->setupUi(this);

    localFPGAaddr = globalVars::global_FPGA_ADDR;


    timer_autoManualClick = new QTimer(this);
    connect(timer_autoManualClick, SIGNAL(timeout()), this, SLOT(on_timer_autoManualClicked()));
    timer_autoManualClick->setInterval(500);
    //timer_autoManualClick->start();


    *(localFPGAaddr + 0x06)  = 0x00;
}

NewDebug::~NewDebug()
{
    delete ui;
}

void NewDebug::on_pb_Reset_clicked()
{

}
void NewDebug::on_pb_StartConversion_clicked()
{
    *(localFPGAaddr + 0x02)  = 0x01;
    *(localFPGAaddr + 0x06)  = 0x00;
    *(localFPGAaddr + 0x03)  = 0x08;
    *(localFPGAaddr + 0x08) = 0x00;     // Pulse
    *(localFPGAaddr + 0x08) = 0x01;
    *(localFPGAaddr + 0x08) = 0x00;
    //qDebug()<<"\t\t WriteRegister Method: Addr: "<<address<<" val: "<<val<<" mosi:"<<sendValue<<"\n";
}
void NewDebug::on_pb_ReadConversion_clicked()
{

}
void NewDebug::on_pb_ADC_Number_clicked()
{
    *(localFPGAaddr + 0x01) = ui->sp_ADC->value();
}



void NewDebug::on_pb_readRegister_clicked()
{
    uint8_t val = 0x00;
    uint8_t rReg = 0x20;

    QString addrTxt = ui->txt_readRegister->toPlainText();
    bool okVar = false;
    uint8_t addrInt = addrTxt.toUInt(&okVar, 10);

    val = (rReg| (addrInt<<2));
    *(localFPGAaddr + 0x03) = val;
    *(localFPGAaddr + 0x02) = 0x02;
    *(localFPGAaddr + 0x08) = 0x00; // pulse
    *(localFPGAaddr + 0x08) = 0x01;
    *(localFPGAaddr + 0x08) = 0x00;


    //usleep(100000);
    uint16_t lsb = *(localFPGAaddr+48);
    uint16_t msb = *(localFPGAaddr+49);
    uint32_t reply = (msb<<16 & 0xffff0000) + (lsb & 0xffff);
    qDebug()<<" readRegister:: lsb:"<<lsb<<" MSB:"<<msb<<" both:"<<reply;
    ui->lbl_readRegister->setText(QString::number(reply, 16));



}

void NewDebug::on_pb_setClock_clicked()
{
    QString valTxt = ui->txt_setClock->toPlainText();
    bool okVar = false;
    uint32_t valInt = valTxt.toUInt(&okVar, 10);
    okVar = false;

    //qDebug()<<"Write:: adc: "<<adcIndx<<" addr(int):"<<addInt<<" Val:"<<valTxt.toUInt(&okVar, 10);
    //valInt *= 1000;
    valInt /= 0.02;
    *(localFPGAaddr+ 0x00) = valInt;
    //ui->lbl_SetClock->setText(QString::number(*(localFPGAaddr+00), 16));
}
void NewDebug::on_pb_samplingRate_clicked()
{
    QString valTxt = ui->txt_setSamplingRate->toPlainText();
    bool okVar = false;
    uint32_t valInt = valTxt.toUInt(&okVar, 10);
    okVar = false;

    //qDebug()<<"Write:: adc: "<<adcIndx<<" addr(int):"<<addInt<<" Val:"<<valTxt.toUInt(&okVar, 10);
    //valInt *= 1000;
    valInt /= 0.02;
    *(localFPGAaddr + 14) = valInt;
    //ui->lbl_setSamplingRate->setText(QString::number(*(localFPGAaddr+14), 16));
}
void NewDebug::on_pb_writeRegister_1_clicked()
{
    QString valTxt = ui->txt_writeRegister_1->toPlainText();
    bool okVar = false;
    uint8_t valInt = valTxt.toUInt(&okVar, 10);
    writeRegister(0x00, valInt);
    //usleep(5000000);
    //ui->lbl_writeRegister_1->setText(QString::number(readRegister(0x00), 16));

}
void NewDebug::on_pb_writeRegister_2_clicked()
{    
    QString valTxt = ui->txt_writeRegister_2->toPlainText();
    bool okVar = false;
    uint8_t valInt = valTxt.toUInt(&okVar, 10);
    writeRegister(0x01, valInt);
    //usleep(5000000);
    //ui->lbl_writeRegister_2->setText(QString::number(readRegister(0x01), 16));
}
void NewDebug::on_pb_writeRegister_3_clicked()
{
    QString valTxt = ui->txt_writeRegister_3->toPlainText();
    bool okVar = false;
    uint8_t valInt = valTxt.toUInt(&okVar, 10);
    writeRegister(0x02, valInt);
    //usleep(5000000);
    //ui->lbl_writeRegister_3->setText(QString::number(readRegister(0x02), 16));
}
void NewDebug::on_pb_writeRegister_4_clicked()
{
    QString valTxt = ui->txt_writeRegister_4->toPlainText();
    bool okVar = false;
    uint8_t valInt = valTxt.toUInt(&okVar, 10);
    writeRegister(0x03, valInt);
    //usleep(5000000);
    //ui->lbl_writeRegister_4->setText(QString::number(readRegister(0x03), 16));
}
void NewDebug::on_pb_Timer_clicked()
{
    if(timer_autoManualClick->isActive())
    {
        timer_autoManualClick->stop();
        ui->pb_Timer->setStyleSheet("background-color: red;");
    }
    else
    {
        timer_autoManualClick->start();
        ui->pb_Timer->setStyleSheet("background-color: lime;");
    }
}



int NewDebug::writeRegister(uint8_t addr, uint8_t val)
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
uint32_t NewDebug::readRegister(uint8_t addr)
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
    qDebug()<<" readRegister:: lsb:"<<lsb<<" MSB:"<<msb<<" both:"<<reply;

    return reply;
}


void NewDebug::on_timer_autoManualClicked()
{
    //on_pb_Write_New_clicked();
    //on_pb_Read_New_clicked();
    //readData();
    on_pb_writeRegister_1_clicked();
    //on_pb_readRegister_clicked();
}

void NewDebug::readData()
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
    qDebug()<<" readData() method:: value (hex):"<<QString::number(dd, 16);
}



