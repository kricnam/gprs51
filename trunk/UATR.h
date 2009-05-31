#ifndef _UATR_H_
#define _UATR_H_

volatile bit bRx1Overflow;
volatile bit bRx2Overflow;

void UATR_init(void);

void UATR1_send(unsigned char i);
void UATR1_sendString(unsigned char* str);
void UATR2_send(unsigned char i);
void UATR2_sendString(unsigned char* str);

unsigned char UATR1_get(void);
unsigned char UATR2_get(void);

void UATR1_ISR(void) __interrupt (4);
void UATR2_ISR(void) __interrupt (8);

#endif
