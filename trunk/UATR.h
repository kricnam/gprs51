#ifndef _UATR_H_
#define _UATR_H_

__idata volatile unsigned char  gRxBuf[16];
__idata volatile unsigned char  gTxBuf[16];
__data volatile unsigned char gRxIn;
__data volatile unsigned char gRxOut;
__data volatile unsigned char gTxIn;
__data volatile unsigned char gTxOut;

volatile bit bSENDING;
volatile bit bRxOverflow;

void UATR1_init(void);

void UATR1_send(unsigned char i);
void UATR1_isend(unsigned char i);
void UATR1_sendString(unsigned char* str);

unsigned char UATR1_get(void);
void UATR1_ISR(void) __interrupt (4);


#endif
