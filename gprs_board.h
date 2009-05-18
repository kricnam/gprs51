#ifdef _GPRS51_H_
#define  _GPRS51_H_
#include "STC12x5A60S2.h"
#define FSCK 11059200   //11.058200MHz Cyrstal
#define RELOAD 0xFA	//4800 Baud Rate RELOAD value, RELOAD=256-int(FSCL/32/12)

#define RUN_LED P1_7


#endif
