#ifndef CHNLCLASS_SIMPLE_H
#define CHNLCLASS_SIMPLE_H

#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include "globalvars.h"

class chnlClass_Simple
{
public:
    chnlClass_Simple();

    bool setChannelEnableDisable(bool enable);
    int setChannelAddress(uint32_t *mainAddr, int addrP);
    bool isChnlEnable();
    float giveCurrentValueWithFactor();
    void Get_RawValue_fromADDRESS();
    float Get_RawValue_fromADDRESSAuto();


    int32_t get_rawValue();



    float set_Channel_Factor(float fac);
    int set_Channel_PGA_Type(CHANNEL_PGA pgaa, CHANNEL_TYPE type);
    CHANNEL_REFERENCE set_Channel_Reference(CHANNEL_REFERENCE ref);

    float give_Channel_Factor();
    CHANNEL_PGA give_Channel_PGA();
    CHANNEL_TYPE give_Channel_Type();
    CHANNEL_REFERENCE give_Channel_Reference();

    int reConfigFPGA_forThisChannel();

    uint32_t endResult = 0x00000000;
    float endResult_Float =0.0;
    float endResult_Float_Factor =0.0;


private:
    uint32_t *localFPGAaddr = 0;
    int local_ADCaddress = 0;
    bool local_Enable = false;
    float local_CH_factor = 1.0;
    CHANNEL_PGA local_CH_PGA = CH_PGA_1;
    CHANNEL_TYPE local_CH_Type = BRIDGE;
    CHANNEL_REFERENCE local_CH_Reference = INTERNAL;
    int local_dataRate = 10;







    uint8_t fpga_PGA = 0;



    int writeRegister(uint8_t addr, uint8_t val);
    uint32_t readRegister(uint8_t addr);

};

#endif // CHNLCLASS_SIMPLE_H
