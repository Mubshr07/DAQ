#ifndef CHNLCLASS_SIMPLE_H
#define CHNLCLASS_SIMPLE_H

#include <iostream>
#include <unistd.h>
#include <stdlib.h>


class chnlClass_Simple
{
public:
    chnlClass_Simple();

    bool setChannelEnableDisable(bool enable);
    int setChannelAddress(int addr);
    bool isChnlEnable();
    float giveCurrentValue();


private:
    int32_t local_address = 0;
    bool local_Enable = false;

};

#endif // CHNLCLASS_SIMPLE_H
