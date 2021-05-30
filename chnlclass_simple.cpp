#include "chnlclass_simple.h"

chnlClass_Simple::chnlClass_Simple()
{
    local_address = 0;
    local_Enable = false;
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

int chnlClass_Simple::setChannelAddress(int addr)
{
    local_address = addr;
    return local_address;
}


float chnlClass_Simple::giveCurrentValue()
{
    float a = local_address-2, b = local_address+2;
    float random = ((float) rand()) / (float) RAND_MAX;
    float diff = b - a;
    float r = random * diff;
    return a + r;
}
