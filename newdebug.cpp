#include "newdebug.h"
#include "ui_newdebug.h"

NewDebug::NewDebug(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewDebug)
{
    ui->setupUi(this);
//    this->setFixedSize(1024, 768);

    this->setWindowFlags(Qt::FramelessWindowHint);
    //this->setWindowState(Qt::WindowFullScreen);
    //this->setWindowFlag(Qt::WindowStaysOnTopHint);
    this->setAttribute(Qt::WA_DeleteOnClose, true); //so that it will be deleted when closed


    localFPGAaddr = globalVars::global_FPGA_ADDR;


    timer_autoManualClick = new QTimer(this);
    connect(timer_autoManualClick, SIGNAL(timeout()), this, SLOT(on_timer_autoManualClicked()));
    timer_autoManualClick->setInterval(100);
    //timer_autoManualClick->start();


    timer_configRegister = new QTimer(this);
    connect(timer_configRegister, SIGNAL(timeout()), this, SLOT(on_timer_configRegister_Elapsed()));
    timer_configRegister->setInterval(100);

    *(localFPGAaddr + 0x06)  = 0x00;
}

void NewDebug::on_pb_Close_clicked()
{
    emit tx_generate_ThisGUI(gui_FIRST_WIN);
    emit tx_ClosingWindow_DebugWin();
}

NewDebug::~NewDebug()
{
    delete ui;
}

int adcNumber = 0;
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
uint32_t NewDebug::on_pb_ReadConversion_clicked()
{
    int finalIndx = ui->sp_ADC->value() + adcNumber;

    int PulseIndx = finalIndx/ 8;

    /*
    uint16_t lsb = *(localFPGAaddr+((PulseIndx*5)+48));
    uint16_t msb = *(localFPGAaddr+((PulseIndx*5)+49));

    uint8_t first = 0x00;
    uint8_t middle = 0x00;
    uint8_t last = 0x00;
    first = (msb & 0xFF);
    middle = (lsb & 0xFF00) >> 8;
    last = (lsb & 0xFF);
    */
    uint32_t endResult = 0x00000000;
//    endResult = (first<<16);
//    endResult = endResult |(middle<<8);
//    endResult = endResult |(last);



    uint8_t lsb = 0x00;
    uint8_t msb =  0x00;

    endResult = *(localFPGAaddr+(PulseIndx+48));

    lsb = (endResult & 0xFF0000)>>16;
    msb = endResult & 0xFF;

    endResult = endResult & 0xFF00;
    endResult = endResult | (lsb & 0xFF);
    endResult = endResult | (msb<<16);


    //qDebug()<<" FullPCB:: current ADC:"<<finalIndx<<" read-Addr:"<<PulseIndx+48<<" endResult (hex):"<<QString::number(endResult, 16);

    *(localFPGAaddr + 0x02)  = 0x03;
    *(localFPGAaddr + 0x06)  = 0x00;
    *(localFPGAaddr + 0x03)  = 0xFF;


    *(localFPGAaddr + (PulseIndx+8)) = 0x00;     // Pulse    //qDebug()<<"\t\t WriteRegister Method: Addr: "<<address<<" val: "<<val<<" mosi:"<<sendValue<<"\n";
    *(localFPGAaddr + (PulseIndx+8)) = 0x01;
    *(localFPGAaddr + (PulseIndx+8)) = 0x00;


    return endResult;


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

    int indxx = ui->sp_ADC->value();
    int actualIDX = indxx / 8;

    *(localFPGAaddr + actualIDX+8) = 0x00; // pulse
    *(localFPGAaddr + actualIDX+8) = 0x01;
    *(localFPGAaddr + actualIDX+8) = 0x00;


    //usleep(100000);
    //uint16_t lsb = *(localFPGAaddr+((actualIDX*5)+48));
    //uint16_t msb = *(localFPGAaddr+((actualIDX*5)+49));
    uint32_t reply = *(localFPGAaddr+(actualIDX+48));; //(msb<<16 & 0xffff0000) + (lsb & 0xffff);
    //qDebug()<<" readRegister:: lsb:"<<lsb<<" MSB:"<<msb<<" both:"<<reply<<" Pulse:"<<actualIDX+8;
    qDebug()<<" readRegister::"<<reply<<" Pulse:"<<actualIDX+8<<" read-Addr:"<<indxx+48;
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


void NewDebug::on_timer_autoManualClicked()
{
    if(autoMode_isEnable)
    { // automatic
        showValueofPCB_Channels(0, getCalculatedFromRawValue(*(localFPGAaddr+0x00)));
        showValueofPCB_Channels(1, getCalculatedFromRawValue(*(localFPGAaddr+0x01)));
        showValueofPCB_Channels(2, getCalculatedFromRawValue(*(localFPGAaddr+0x02)));
        showValueofPCB_Channels(3, getCalculatedFromRawValue(*(localFPGAaddr+0x03)));
        showValueofPCB_Channels(4, getCalculatedFromRawValue(*(localFPGAaddr+0x04)));
        showValueofPCB_Channels(5, getCalculatedFromRawValue(*(localFPGAaddr+0x05)));
        showValueofPCB_Channels(6, getCalculatedFromRawValue(*(localFPGAaddr+0x06)));
        showValueofPCB_Channels(7, getCalculatedFromRawValue(*(localFPGAaddr+0x07)));
    }
    else
    {
        if(adcNumber == 8) adcNumber = 0;
        else  adcNumber++;

        //adcNumber = ui->sp_ADC->value();adcNumber

        *(localFPGAaddr + 0x01) = (ui->sp_ADC->value() + adcNumber);
        uint32_t rawValue = on_pb_ReadConversion_clicked();
        usleep(10000);
        rawValue = on_pb_ReadConversion_clicked();


        float internalRef = 2.048;
        double coeficient = pow(2, 24);
        float calculatedValue = (rawValue/coeficient) * internalRef;


        showValueofPCB_Channels(adcNumber, calculatedValue);
    }


    //on_pb_Write_New_clicked();
    //on_pb_Read_New_clicked();
    //readData();
    //on_pb_writeRegister_1_clicked();
    //on_pb_ReadConversion_clicked();
    //on_pb_readRegister_clicked();


}

float NewDebug::getCalculatedFromRawValue(uint32_t raw)
{
    //int32_t simpleInt = (raw & 0x7FFFFF);
    //simpleInt = simpleInt + ((raw & 0x800000)<<8); // >> 23;

    float internalRef = 2.048;
    float coeficient = pow(2, 24);
    float calculatedValue = (raw/coeficient) * internalRef;
    return calculatedValue;
}


void NewDebug::on_timer_configRegister_Elapsed()
{

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

    int indxx = ui->sp_ADC->value();

    int actualIDX = indxx / 8;
    actualIDX += 8;

    *(localFPGAaddr + actualIDX) = 0x00;     // Pulse
    *(localFPGAaddr + actualIDX) = 0x01;
    *(localFPGAaddr + actualIDX) = 0x00;
    qDebug()<<"\t\t WriteRegister Method: Addr: "<<address<<" val: "<<val<<" mosi:"<<sendValue<<" Pulse Indx:"<<actualIDX<<"\n";
    return  1;
}
uint32_t NewDebug::readRegister(uint8_t addr)
{
    uint8_t val = 0x00;
    uint8_t rReg = 0x20;
    val = (rReg| (addr<<2));
    *(localFPGAaddr + 0x03) = val;
    *(localFPGAaddr + 0x02) = 0x02;

    int indxx = ui->sp_ADC->value();
    int actualIDX = indxx / 8;

    *(localFPGAaddr + actualIDX+8) = 0x00; // pulse
    *(localFPGAaddr + actualIDX+8) = 0x01;
    *(localFPGAaddr + actualIDX+8) = 0x00;


    //usleep(100000);
    //uint16_t lsb = *(localFPGAaddr+((actualIDX*5)+48));
    //uint16_t msb = *(localFPGAaddr+((actualIDX*5)+49));
    uint32_t reply = *(localFPGAaddr+(actualIDX+48)); //(msb<<16 & 0xffff0000) + (lsb & 0xffff);
    //qDebug()<<" readRegister:: lsb:"<<lsb<<" MSB:"<<msb<<" both:"<<reply<<" Pulse:"<<actualIDX+8;
    qDebug()<<" readRegister:: "<<reply<<" Pulse:"<<actualIDX+8;

    return reply;
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




void NewDebug::on_pb_readRegister_2_clicked()
{
    uint16_t lsb = *(localFPGAaddr+48);
    uint16_t msb = *(localFPGAaddr+49);
    msb = (msb & 0xFF);
    uint32_t reply = (msb<<16 & 0xffff0000) + (lsb & 0xffff);
    qDebug()<<" readRegister 2:: lsb:"<<lsb<<" MSB:"<<msb<<" both:"<<reply;
    ui->lbl_readRegister->setText(QString::number(reply, 16));


}
void NewDebug::on_pb_read_ALLChannels_clicked()
{
    if(timer_autoManualClick->isActive())
    {
        timer_autoManualClick->stop();
        ui->pb_read_ALLChannels->setStyleSheet("background-color:red;");
    }
    else
    {
        timer_autoManualClick->start(50);
        ui->pb_read_ALLChannels->setStyleSheet("background-color:lime;");
    }

}

void NewDebug::showValueofPCB_Channels(int idx, float val)
{
    switch (idx) {
    case 0: {
        ui->lbl_Channel_1->setText(QString::number(val, 'f', 2));
        break;
    }
    case 1: {
        ui->lbl_Channel_2->setText(QString::number(val, 'f', 2));
        break;
    }
    case 2: {
        ui->lbl_Channel_3->setText(QString::number(val, 'f', 2));
        break;
    }
    case 3: {
        ui->lbl_Channel_4->setText(QString::number(val, 'f', 2));
        break;
    }
    case 4: {
        ui->lbl_Channel_5->setText(QString::number(val, 'f', 2));
        break;
    }
    case 5: {
        ui->lbl_Channel_6->setText(QString::number(val, 'f', 2));
        break;
    }
    case 6: {
        ui->lbl_Channel_7->setText(QString::number(val, 'f', 2));
        break;
    }
    case 7: {
        ui->lbl_Channel_8->setText(QString::number(val, 'f', 2));
        break;
    }
    }
}

void NewDebug::on_pb_ConfigAll_clicked()
{
    int delay = 10000;
    for(int i=0; i<8; i++)
    {
        *(localFPGAaddr+0x01) = (ui->sp_ADC->value())+ i;
        usleep(delay);
        on_pb_writeRegister_1_clicked();
        usleep(delay);
        on_pb_writeRegister_2_clicked();
        usleep(delay);
        on_pb_writeRegister_3_clicked();
        usleep(delay);
        on_pb_writeRegister_4_clicked();
        usleep(delay);
        on_pb_StartConversion_clicked();
        usleep(delay);

        qDebug()<<"\t" <<i <<" Channel Configured ";
    }
    qDebug()<<" all Channels Configured ";
}
void NewDebug::on_pb_read_Automatic_clicked()
{

    //if(timer_autoManualClick->isActive()) {
    if(autoMode_isEnable) {

        //timer_autoManualClick->stop();
        ui->pb_read_Automatic->setStyleSheet("background-color:red;");


        *(localFPGAaddr+0x06) = 0x00;
        *(localFPGAaddr+0x07) = 0x00;
        autoMode_isEnable = false;
    }
    else {

        *(localFPGAaddr+0x06) = 0x01;

        *(localFPGAaddr+0x07) = 0x00;
        *(localFPGAaddr+0x07) = 0x01;
        *(localFPGAaddr+0x07) = 0x00;
        autoMode_isEnable = true;
        //timer_autoManualClick->start();
        ui->pb_read_Automatic->setStyleSheet("background-color:lime;");
    }
}
