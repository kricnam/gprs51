#include "STC12x5A60S2.h"
#include "gprs_board.h"
//Set COM1 
//
void UART_init()
{
	SCON = 0x50;//SMODE=2
	BRT = RELOAD;
	AUXR = 0x11;
	ES = 1;
	EA = 1; 
}
