#include "chnlclass_simple.h"

chnlClass_Simple::chnlClass_Simple()
{
    local_ADCaddress = 0;
    local_Enable = false;
}


//------------------------ MAIN VAlUE Calculation -----------------------


//------------------------ MAIN ADDRESS RAW VAlue SAMPLING -----------------------
void chnlClass_Simple::Get_RawValue_fromADDRESS()
{
    /*
    float a = local_ADCaddress-2, b = local_ADCaddress+2;
    float random = ((float) rand()) / (float) RAND_MAX;
    float diff = b - a;
    float r = random * diff;
    return a+r;
    */


    *(localFPGAaddr+0x01) = local_ADCaddress;

    *(localFPGAaddr + 0x02) = 0x03;
    *(localFPGAaddr + 0x03) = 0xFFFFFF;

    int indxx = (local_ADCaddress / 8);

    *(localFPGAaddr + indxx+8) = 0x00; // pulse
    *(localFPGAaddr + indxx+8) = 0x01;
    *(localFPGAaddr + indxx+8) = 0x00;

    /*
    //usleep(100000);
    uint16_t lsb = *(localFPGAaddr+((indxx*5)+48));
    uint16_t msb = *(localFPGAaddr+((indxx*5)+49));
    uint8_t first = 0x00;
    uint8_t middle = 0x00;
    uint8_t last = 0x00;
    first = (msb & 0xFF);
    middle = (lsb & 0xFF00) >> 8;
    last = (lsb & 0xFF);
    endResult = (first<<16);
    endResult = endResult |(middle<<8);
    endResult = endResult |(last);
    */


    uint8_t lsb = 0x00;
    uint8_t msb =  0x00;

    endResult = *(localFPGAaddr+(indxx+48));

    lsb = (endResult & 0xFF0000)>>16;
    msb = endResult & 0xFF;

    endResult = endResult & 0xFF00;
    endResult = endResult | (lsb & 0xFF);
    endResult = endResult | (msb<<16);

    float internalRef = 2.048;
    float coeficient = pow(2, 24);
    float calculatedValue = (endResult/coeficient) * internalRef;
    endResult_Float = calculatedValue;


    endResult_Float_Factor = endResult_Float * local_CH_factor;

    //qDebug()<<"ADC:"<<local_ADCaddress<<"\t readRegister:: lsb:"<<lsb<<" MSB:"<<msb<<" both:"<<endResult<<" calc:"<<calculatedValue;
    //return calculatedValue;

}
void chnlClass_Simple::Get_RawValue_fromADDRESSAuto()
{
    autoScheme_endResult = *(localFPGAaddr + local_ADCaddress);
    float internalRef = 2.048;
    float coeficient = pow(2, 24);
    float calculatedValue = (autoScheme_endResult/coeficient) * internalRef;
    autoScheme_endResult_Float = calculatedValue;
    autoScheme_endResult_Float_Factor = autoScheme_endResult_Float * local_CH_factor;
}


int chnlClass_Simple::reConfigFPGA_forThisChannel()
{
    *(localFPGAaddr + 0x01) = local_ADCaddress;
    uint8_t reg0 = 0x00;
    switch (local_CH_PGA) {
    case CH_PGA_1: { fpga_PGA = 0; break; }
    case CH_PGA_2: { fpga_PGA = 1; break; }
    case CH_PGA_4: { fpga_PGA = 2; break; }
    case CH_PGA_8: { fpga_PGA = 3; break; }
    case CH_PGA_16: { fpga_PGA = 4; break; }
    case CH_PGA_32: { fpga_PGA = 5; break; }
    case CH_PGA_64: { fpga_PGA = 6; break; }
    case CH_PGA_128: { fpga_PGA = 7; break; }
    }
    reg0 = ((fpga_PGA<<1) & 0x0E) | reg0;
    //qDebug()<<" 1: "<<QString::number(reg0, 16);
    switch (local_CH_Type) {
    case UniPolar: { reg0 = reg0 | 0b10110000; break; }
    case BiPolar: { reg0 = reg0 | 0b10000000; break; }
    case BRIDGE: { reg0 = reg0 | 0b00110000; break; }
    }

    //qDebug()<<" 2: "<<QString::number(reg0, 16);
    usleep(10000);
    writeRegister(0x00, reg0);
    usleep(10000);
    writeRegister(0x01, 0xC4);
    usleep(10000);

    switch (local_CH_Reference) {
    INTERNAL: { writeRegister(0x02, 0x00); break; }
    EXTERNAL: { writeRegister(0x02, 0xC0); break; }
    }
    usleep(10000);
    writeRegister(0x03, 0x00);
    usleep(10000);

    // Start Conversion
    *(localFPGAaddr + 0x02)  = 0x01;
    *(localFPGAaddr + 0x06)  = 0x00;
    *(localFPGAaddr + 0x03)  = 0x08;

    int pulseRegister = local_ADCaddress/8;
        pulseRegister += 8;

    *(localFPGAaddr + pulseRegister) = 0x00;     // Pulse
    *(localFPGAaddr + pulseRegister) = 0x01;
    *(localFPGAaddr + pulseRegister) = 0x00;

    usleep(10000);

    return 1;
}


int chnlClass_Simple::writeRegister(uint8_t addr, uint8_t val)
{
    uint8_t wReg = 0x40;
    uint8_t address = 0x00;
    address = (wReg|(addr<<2));
    uint32_t sendValue = 0x00;

    sendValue = ((val<<8) & 0xff00) + (address & 0xff);
    *(localFPGAaddr + 0x02)  = 0x02;
    *(localFPGAaddr + 0x06)  = 0x00;
    *(localFPGAaddr + 0x03)  = sendValue;

    int actualIDX = local_ADCaddress / 8;
        actualIDX += 8;

    *(localFPGAaddr + actualIDX) = 0x00;     // Pulse
    *(localFPGAaddr + actualIDX) = 0x01;
    *(localFPGAaddr + actualIDX) = 0x00;


    qDebug()<<"ADC:"<<local_ADCaddress<<"\t\t WriteRegister Method: Addr: "<<address<<" val: "<<val<<" mosi:"<<sendValue; //<<"\n";
    return  1;
}
uint32_t chnlClass_Simple::readRegister(uint8_t addr)
{
    uint8_t address = 0x00;
    uint8_t rReg = 0x20;
    address = (rReg| (addr<<2));
    *(localFPGAaddr + 0x03) = address;
    *(localFPGAaddr + 0x02) = 0x02;

    int actualIDX = local_ADCaddress / 8;

    *(localFPGAaddr + actualIDX+8) = 0x00; // pulse
    *(localFPGAaddr + actualIDX+8) = 0x01;
    *(localFPGAaddr + actualIDX+8) = 0x00;


    //usleep(100000);
    //uint16_t lsb = *(localFPGAaddr+((actualIDX*5)+48));
    //uint16_t msb = *(localFPGAaddr+((actualIDX*5)+49));

    uint32_t reply = *(localFPGAaddr + (actualIDX + 48));
    //uint32_t reply = (msb<<16 & 0xffff0000) + (lsb & 0xffff);
    //qDebug()<<"ADC:"<<local_ADCaddress<<"\t readRegister:: lsb:"<<lsb<<" MSB:"<<msb<<" both:"<<reply;
    qDebug()<<"ADC:"<<local_ADCaddress<<"\t readRegister:: "<<reply<<" Read Addr:"<<actualIDX+48;

    return reply;
}




// ----------------------- CHANNEL SETTINGS METHODS ------------------------
int chnlClass_Simple::setChannelAddress(uint32_t * mainAddr,int addr)
{
    localFPGAaddr = mainAddr;
    local_ADCaddress = addr;
    return local_ADCaddress;
}

bool chnlClass_Simple::setChannelEnableDisable(bool enable)
{
    local_Enable = enable;
    return local_Enable;
}
bool chnlClass_Simple::isChnlEnable()
{
    return local_Enable;
}
float chnlClass_Simple::set_Channel_Factor(float fac)
{
    local_CH_factor = fac;
    return local_CH_factor;
}
int chnlClass_Simple::set_Channel_PGA_Type(CHANNEL_PGA pgaa, CHANNEL_TYPE typ)
{
    local_CH_PGA = pgaa;
    local_CH_Type = typ;
    return local_CH_PGA;
}

CHANNEL_REFERENCE chnlClass_Simple::set_Channel_Reference(CHANNEL_REFERENCE ref)
{
    local_CH_Reference = ref;
    //*(localFPGAaddr + local_ADCaddress)
    return local_CH_Reference;
}




float chnlClass_Simple::give_Channel_Factor()
{
    return  local_CH_factor;
}
CHANNEL_PGA chnlClass_Simple::give_Channel_PGA()
{
    return  local_CH_PGA;
}
CHANNEL_TYPE chnlClass_Simple::give_Channel_Type()
{
    return  local_CH_Type;
}
CHANNEL_REFERENCE chnlClass_Simple::give_Channel_Reference()
{
    return  local_CH_Reference;
}

