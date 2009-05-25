#include "gprs_board.h"
#include "UATR.h"
void UATR1_ISR(void) __interrupt (4);
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
    RUN_LED = 0;
    TimeDelay(100);
    RUN_LED = 1;
    TimeDelay(100);
    RUN_LED = 0;
    UATR1_init();
    UATR1_isend('O');
    UATR1_isend('K');
    UATR1_isend('\r');
    UATR1_isend('\n');
    while(1)
    {
	unsigned char i;
	i=UATR1_get();
	if (i) UATR1_send(i);
	//else wait();
    };
}
