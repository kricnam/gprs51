#include "STC12x5A60S2.h"
//Set COM1 
//
void UART_init()
{
	SCON = 0x50;//SMODE=2
	BRT =;
	AUXR = 0x11;
	ES = 1;
	EA = 1; 
		
}
