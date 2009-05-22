#include "gprs_board.h"
#include "UATR.h"

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

void main(void)
{
    RUN_LED = 0;
    TimeDelay(100);
    RUN_LED = 1;
    TimeDelay(100);
    RUN_LED = 0;
    UATR_init();
    UATR_send('O');
    UATR_send('K');
    UATR_send('\r');
    UATR_send('\n');
    while(1)
    {
	UATR_send('A');
    };
}
