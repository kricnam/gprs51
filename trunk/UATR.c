#include "STC12x5A60S2.h"
#include "gprs_board.h"
#include "UATR.h"
//Set COM1 

__idata volatile unsigned char  gRx1Buf[16];
__idata volatile unsigned char  gRx2Buf[16];
__data volatile unsigned char gRx1In;
__data volatile unsigned char gRx2In;
__data volatile unsigned char gRx1Out;
__data volatile unsigned char gRx2Out;
__xdata volatile unsigned char gTx1;
__xdata volatile unsigned char gTx2[16];
__data volatile unsigned char gTx1In;
__data volatile unsigned char gTx2In;
__data volatile unsigned char gTx1Out;
__data volatile unsigned char gTx2Out;



volatile bit bRx1Full;
volatile bit bRx2Full;
volatile unsigned char * gTx1Ptr;
volatile unsigned char * gTx2Ptr;
volatile unsigned int gTx1Len;
volatile unsigned int gTx2Len;


void UATR_init()
{
	gRx1In = 0;
	gRx1Out = 0;
        gTx1In = 0;
        gTx1Out = 0;
 
	gTx1Ptr = 0;
	bRx1Overflow=0;
	bRx1Full=0;

        gRx2In = 0;
        gRx2Out = 0;
        gTx2In = 0;
        gTx2Out = 0;
 
        gTx2Ptr = 0;
        bRx2Overflow=0;
        bRx2Full=0;

	SCON = 0x50;//SMODE=2
	TMOD = 0x21;
	TH1  = RELOAD;
	TL1  = RELOAD;
	S2CON = 0x50;//SMODE=2
        PCON|= 0x80;//波特率倍增,SMOD='1'
	BRT = RELOAD;

	AUXR = 0x18;//BRTR=1;S2SMOD=1;BRx12=1;
	TR1 = 1;
	ES = 1;
	IE2 = 0x01; //enable UATR 2 imterupt
	EA = 1; 
}


void UATR1_send(unsigned char i)
{
	while (gTx1Ptr) {
	};

	_asm
	nop
        nop
        nop
	_endasm;
	ES=0;	
	gTx1Ptr=&gTx1;
	gTx1Len = 1;
	gTx1 = i;
	ES=1;
	TI = 1;
}

void UATR2_send(unsigned char i)
{
        while (gTx2Ptr) {};
        gTx2Len = 1;
	gTx2[0] = i;
        S2CON |= 0x01;
}

void UATR1_sendString(unsigned char* str)
{
	unsigned int i=0;
	while(str[i++]); 
	while(gTx1Ptr) {};
        _asm
        nop
        nop
        nop
        _endasm;
	ES=0;
	gTx1Ptr = str;
	gTx1Len = i;
	ES=1;
        _asm
        nop
        nop
        nop
        nop
        nop
        nop
        _endasm;
	TI = 1;
}

void UATR2_sendString(unsigned char* str)
{
        while(gTx2Ptr) {};
        gTx2Ptr = str;
        S2CON |= 0x01;
}

unsigned char UATR1_get(void)
{
	if (gRx1In == gRx1Out) return 0;
	gRx1Out++;
	return gRx1Buf[(gRx1Out-1)& 0x0F];
}

unsigned char UATR2_get(void)
{
        if (gRx2In == gRx2Out) return 0;
        gRx2Out++;
        return gRx2Buf[(gRx2Out-1)& 0x0F];
}


void UATR1_ISR(void) __interrupt (4)
{
     
	unsigned char i;
	char n=15;
	ES = 0;
	if (RI)
	{
		RI = 0;
		i = SBUF;
		if (!(bRx1Full && gRx1In==gRx1Out))
		{
			gRx1Buf[gRx1In & 0x0F] = i;
			gRx1In++;
			bRx1Full = (gRx1In==gRx1Out)?1:0;
		}
	}
	if (TI)
	{
		TI = 0;
		if (gTx1Len)
		{
			gTx1Len--;
			_asm
			nop
			nop
			nop
			nop
			nop
			nop
			_endasm;
			SBUF = *gTx1Ptr; 
			gTx1Ptr++;
		}
		else
		{
			gTx1Ptr=0;
		}
	}
	ES = 1;
}

void UATR2_ISR(void) __interrupt (8)
{

        unsigned char i;
        IE2 &= 0xFE;
        if (S2CON & 0x01)
        {
                S2CON &= 0xFE;
                i = S2BUF;
                bRx2Overflow |= (bRx2Full && gRx2In==gRx2Out)?1:0;
                gRx2Buf[gRx2In & 0x0F] = i;
                gRx2In++;
                bRx2Full = (gRx2In==gRx2Out)?1:0;
        }
        if (S2CON& 0x02)
        {
                S2CON &= 0xFD;
                if (gTx2Ptr && (*gTx2Ptr || gTx2Len) )
                {
                   S2BUF = *gTx2Ptr;
                   gTx2Ptr++;
                   if (gTx2Len)
                   {
                        gTx2Len--;
                        if (gTx2Len==0) gTx2Ptr=0;
                   }
                }
                else
                {
                        gTx2Ptr = 0;
                        gTx2Len = 0;
                }
        }
        IE2 |= 0x01;
}

