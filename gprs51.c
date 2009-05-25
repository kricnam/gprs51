#include "gprs_board.h"
#include "UATR.h"

__xdata unsigned char XMem[512];

void TimeDelay(int Time)
{
	int i;
	while(Time > 0)
	{
		for(i = 0;i < 8000;i++)
		{
			;//_nop_();
		}
		Time --;
	}
}
void wait(void)
{
	PCON =  0x01;
	_asm
	nop
	nop
	nop
	nop
	_endasm;
}

void main(void)
{
    __code unsigned char* hello="Hello World\r\n";
    int i;
    RUN_LED = 0;
    TimeDelay(100);
    RUN_LED = 1;
    TimeDelay(100);
    RUN_LED = 0;
    UATR1_init();
    for( i=0;i<512;i++)
    {
	XMem[i]= 'A';
    }  
    for (i=0;i<512;i++)
	UATR1_send(XMem[i]);
    UATR1_isend('O');
    UATR1_isend('K');
    UATR1_isend('\r');
    UATR1_isend('\n');
    UATR1_sendString(hello);
    
    while(1)
    {
	unsigned char i;
	i=UATR1_get();
	if (i) UATR1_isend(i);
	else wait();
    };
}
