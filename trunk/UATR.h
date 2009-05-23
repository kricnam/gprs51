#ifndef _UATR_H_
#define _UATR_H_

__idata unsigned char gTxLen;
__idata unsigned char gRxBuf[16];
__idata unsigned char* iTxBuf;
__data unsigned char gRxIn;
__data unsigned char gRxOut;
__data unsigned char gTxLen;

bit bSENDING;
bit bRxOverflow;

void UATR1_init(void);
void UATR1_send(unsigned char i);

#endif
