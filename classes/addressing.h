#ifndef ADDRESSING_H
#define ADDRESSING_H

#include <sys/mman.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <QThread>

#define HW_REGS_BASE ( 0xFC000000 )
#define HW_REGS_SPAN ( 0x04000000 )
#define HW_REGS_MASK ( HW_REGS_SPAN - 1 )
#define ALT_LWFPGASLVS_OFST ( 0xFF200000 )


class Addressing
{
public:
    Addressing();
    int get_address_of_peripherals();
    uint32_t* givemeaddr(int a);
};

#endif // ADDRESSING_H
