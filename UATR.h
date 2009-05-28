#ifndef _UATR_H_
#define _UATR_H_

volatile bit bRx1Overflow;
void UATR1_init(void);

void UATR1_send(unsigned char i);
void UATR1_sendString(unsigned char* str);

unsigned char UATR1_get(void);
void UATR1_ISR(void) __interrupt (4);


#endif
