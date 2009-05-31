#include "STC12x5A60S2.h"
void wait(void)
{
        PCON |= 0x01;
        _asm
        nop
        nop
        nop
        nop
        _endasm;
}

