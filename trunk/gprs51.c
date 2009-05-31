#include "gprs_board.h"
#include "UATR.h"
#include "wait.h"
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

void main(void)
{
    __code unsigned char* hello="\r\nSystem Start...\r\n";
    __code unsigned char* msg="\r\nGPRS Power On";
    __code unsigned char* ATCMD="AT\n";
    bit bIO10High;
    unsigned char n;

    RUN_LED = 0;
    TimeDelay(10);
    RUN_LED = 1;
    TimeDelay(20);
    RUN_LED = 0;
    UATR_init();
    UATR1_sendString(hello);

    P4_3 = 0;
    P4_2 = 0;
    P3M1 |= 0x08;
    P4SW |= 0x10;
    P2M0 |= 0x80;
    if (P3_3)    UATR1_sendString(hello);
    //Power GPRS Module
    P1_1 = 0;
    TimeDelay(100);
    P1_1 = 1;
    //Check
    bIO10High = 0;
    n =0;
    while(!bIO10High)
    {
        if (!P3_3) n++;
	if (n > 4) bIO10High = 1;

    }

    UATR1_sendString(msg);
    
    while(!P3_3){};
    UATR1_sendString(msg); 
    
    //UATR2_sendString(ATCMD);
	//n = UATR2_get();
	//if (n) UATR1_send(n);
    while(1)
    {
	n = UATR1_get();
	if (n) 
	{
		UATR1_send(n);
		UATR2_send(n);	
	}
	UATR1_sendString(ATCMD);
	wait();
    };
}
