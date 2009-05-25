#include "STC12x5A60S2.h"
#include "gprs_board.h"
#include "UATR.h"
//Set COM1 

void UATR1_init()
{
	SCON = 0x50;//SMODE=2
	BRT = RELOAD;
	AUXR = 0x11;
	gRxIn = 0;
	gRxOut = 0;
	gTxIn = 0 ;
	gTxOut = 0;
	bSENDING = 0;
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

void UATR1_isend(unsigned char i)
{
	while (gTxIn+1 == gTxOut) {};
	if(!bSENDING)
	{
		bSENDING = 1;
		SBUF=i;
	} 
	else 
	{
		gTxBuf[gTxIn & 0x0F] = i;
		gTxIn++;
	}
}

void UATR1_sendString(unsigned char* str)
{
	while(*str)
	{
		UATR1_isend(*str);
		str++;
	}
}

unsigned char UATR1_get(void)
{
	if (gRxIn == gRxOut) return 0;
	gRxOut++;
	return gRxBuf[(gRxOut-1)& 0x0F];
}



void UATR1_ISR(void) __interrupt (4)
{

	unsigned char i;
	ES = 0;
	if (TI)
	{
		TI = 0;
		if (gTxOut != gTxIn)
		{
		   bSENDING = 1;
		   SBUF = gTxBuf[gTxOut&0x0F]; 
		   gTxOut++;
		}
		else
		   bSENDING = 0;
	}
	if (RI)
	{
		RI = 0;
		i = SBUF;
		gRxBuf[gRxIn & 0x0F] = i;
		gRxIn++;
	}
	ES = 1;
}
