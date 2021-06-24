#include "chnlclass_simple.h"

chnlClass_Simple::chnlClass_Simple()
{
    local_address = 0;
    local_Enable = false;
}


//------------------------ MAIN VAlUE Calculation -----------------------
float chnlClass_Simple::giveCurrentValue()
{
    // -------------------  Geting Value from ADDRESS
    float rawValue = Get_RawValue_fromADDRESS();


    float calculatedWithFactorAndPGA = (rawValue * local_CH_factor);// + local_CH_PGA;
    return calculatedWithFactorAndPGA;
}

//------------------------ MAIN ADDRESS RAW VAlue SAMPLING -----------------------
float chnlClass_Simple::Get_RawValue_fromADDRESS()
{
    float a = local_address-2, b = local_address+2;
    float random = ((float) rand()) / (float) RAND_MAX;
    float diff = b - a;
    float r = random * diff;
    return a+r;
}





// ----------------------- CHANNEL SETTINGS METHODS ------------------------
int chnlClass_Simple::setChannelAddress(int addr)
{
    local_address = addr;
    return local_address;
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
float chnlClass_Simple::set_Channel_PGA(float pgaa)
{
    local_CH_PGA = pgaa;
    return local_CH_PGA;
}
CHANNEL_TYPE chnlClass_Simple::set_Channel_Type(CHANNEL_TYPE typ)
{
    local_CH_Type = typ;
    return local_CH_Type;
}
CHANNEL_REFERENCE chnlClass_Simple::set_Channel_Reference(CHANNEL_REFERENCE ref)
{
    local_CH_Reference = ref;
    return local_CH_Reference;
}




float chnlClass_Simple::give_Channel_Factor()
{
    return  local_CH_factor;
}
float chnlClass_Simple::give_Channel_PGA()
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

