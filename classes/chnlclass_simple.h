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
    int setChannelAddress(int addr);
    bool isChnlEnable();
    float giveCurrentValue();
    float Get_RawValue_fromADDRESS();


    float set_Channel_Factor(float fac);
    float set_Channel_PGA(float pgaa);
    CHANNEL_TYPE set_Channel_Type(CHANNEL_TYPE typ);
    CHANNEL_REFERENCE set_Channel_Reference(CHANNEL_REFERENCE ref);

    float give_Channel_Factor();
    float give_Channel_PGA();
    CHANNEL_TYPE give_Channel_Type();
    CHANNEL_REFERENCE give_Channel_Reference();



private:
    int32_t local_address = 0;
    bool local_Enable = false;
    float local_CH_factor = 1.0;
    float local_CH_PGA = 1.0;
    CHANNEL_TYPE local_CH_Type = BRIDGE;
    CHANNEL_REFERENCE local_CH_Reference = INTERNAL;


};

#endif // CHNLCLASS_SIMPLE_H
