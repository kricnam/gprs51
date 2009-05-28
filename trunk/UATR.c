#include "STC12x5A60S2.h"
#include "gprs_board.h"
#include "UATR.h"
//Set COM1 

__idata volatile unsigned char  gRx1Buf[16];
__data volatile unsigned char gRx1In;
__data volatile unsigned char gRx1Out;
volatile bit bRx1Full;
volatile unsigned char * gTx1Ptr;
volatile unsigned int gTx1Len;

void UATR1_init()
{
	SCON = 0x50;//SMODE=2
        PCON|= 0x80;//波特率倍增,SMOD='1'
	BRT = RELOAD;
	AUXR = 0x15;
	gRx1In = 0;
	gRx1Out = 0;
	gTx1Ptr = 0;
	bRx1Overflow=0;
	bRx1Full=0;
	ES = 1;
	EA = 1; 
}

void UATR1_send(unsigned char i)
{
	while (gTx1Ptr) {};
	gTx1Ptr = &i;
	gTx1Len = 1;
	TI = 1;
}

void UATR1_sendString(unsigned char* str)
{
	while(gTx1Ptr) {};
	gTx1Ptr = str;
	TI = 1;
}

unsigned char UATR1_get(void)
{
	if (gRx1In == gRx1Out) return 0;
	gRx1Out++;
	return gRx1Buf[(gRx1Out-1)& 0x0F];
}


void UATR1_ISR(void) __interrupt (4)
{

	unsigned char i;
	ES = 0;
	if (RI)
	{
		RI = 0;
		i = SBUF;
		bRx1Overflow |= (bRx1Full && gRx1In==gRx1Out)?1:0;
		gRx1Buf[gRx1In & 0x0F] = i;
		gRx1In++;
		bRx1Full = (gRx1In==gRx1Out)?1:0;
	}
	if (TI)
	{
		TI = 0;
		if (gTx1Ptr && (*gTx1Ptr || gTx1Len) )
		{
		   SBUF = *gTx1Ptr; 
		   gTx1Ptr++;
		   if (gTx1Len) 
		   {
			gTx1Len--;
			if (gTx1Len==0) gTx1Ptr=0;
		   }
		}
		else
		{
			gTx1Ptr = 0;
			gTx1Len = 0;
		}
	}
	ES = 1;
}
