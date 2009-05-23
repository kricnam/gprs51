#include "STC12x5A60S2.h"
#include "gprs_board.h"
#include "UATR.h"
//Set COM1 

void UATR1_init()
{
	SCON = 0x50;//SMODE=2
	BRT = RELOAD;
	AUXR = 0x11;
	ES = 1;
	EA = 1; 
}

void UATR1_send(unsigned char i)
{
	ES = 0;
	TI = 0;
	SBUF = i;
	while(TI == 0);
	TI = 0;
	ES = 1;
}

void UATR1_ISR(void) __interrupt (4)
{
	ES = 0;
	if (TI)
	{
		TI = 0;
	}
	if (RI)
	{
		RI = 0;
	}
	ES = 1;
}
