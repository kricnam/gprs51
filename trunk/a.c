#include <SST89x5xRDx.h>
#include "LCD_Define.h"
#include "LCD_PortConfig.h"
void LCD_DataWrite(unsigned char Dat);
void TimeDelay(int Time);
void LCD_RegWrite(LCDBYTE Command);

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

void LCD_DataWrite(unsigned char Dat)
{

	unsigned char Num;

	LCD_CS = 0;

	LCD_A0 = 1;

	for(Num=0;Num<8;Num++)

	{

		if((Dat&0x80) == 0)	LCD_SDI = 0;

		else LCD_SDI = 1;

		Dat = Dat << 1;

		LCD_CLK = 0;

		LCD_CLK = 1;

	}

	LCD_CS = 1;

}

void LCD_RegWrite(LCDBYTE Command)

{

	unsigned char Num;

	LCD_CS_CLR();// = 0;

	LCD_A0_CLR();// = 0;

	for(Num=0;Num<8;Num++)

	{

		if((Command&0x80) == 0)	LCD_SDI_CLR();// = 0;

		else LCD_SDI_SET();// = 1;

		Command = Command << 1;

		LCD_CLK_CLR();// = 0;

		LCD_CLK_SET();// = 1;

	}

	LCD_CS_SET();// = 1;

}

void LCD_Fill(unsigned char Data)
{
	unsigned char i,j;
	unsigned char uiTemp;
	uiTemp = Dis_Y_MAX;
	uiTemp = uiTemp>>3;
	for(i=0;i<=uiTemp;i++)	
	{
		LCD_RegWrite(0xb0+i);
		LCD_RegWrite(0x00);
		LCD_RegWrite(0x10);
		for(j=0;j<=Dis_X_MAX;j++)
		{
			LCD_DataWrite(Data);
		}
	}
}

void LCD_Init(void)
{

	TimeDelay(200);
	LCD_RE_CLR();
	TimeDelay(200);
	LCD_RE_SET();
	TimeDelay(20);
		
	LCD_RegWrite(M_LCD_ON);							//LCD On
	LCD_RegWrite(M_LCD_POWER_ALL);					
	
	LCD_RegWrite(M_LCD_ELE_VOL);					
	LCD_RegWrite(0x1f);								
	
	LCD_RegWrite(M_LCD_VDD_SET);					
	LCD_RegWrite(M_LCD_VDD);					
	
	LCD_RegWrite(M_LCD_COM_REV);					
	LCD_RegWrite(M_LCD_SEG_NOR);					
	LCD_RegWrite(M_LCD_ALL_LOW);				
	LCD_RegWrite(M_LCD_ALL_NOR);					
	
	LCD_RegWrite(M_LCD_STATIC_OFF);			
	LCD_RegWrite(0x00);
	
	LCD_RegWrite(M_LCD_BEGIN_LINE);					
	LCD_Fill(LCD_INITIAL_COLOR);
}


void main(void)
{
	
	unsigned char i,j;
	P3=0x00;
	P0_1=0;
	/*P0=0x00;*/
	SCON = 0x50;
	TMOD =0x20;
	TH1 = 0xF3;
	TL1 = 0xF3;
	PCON&=0x00;
	TCON = 0x40;
	i=0;
	j='A';
	RI=0;
	LCD_Init();
    	while(1)
    	{
		s:
		SBUF = j;
		while(!TI){;};
		TimeDelay(1);
		if (j < 'Z') {j=j+1;goto s;}
		SBUF='\n';
		while(!TI) {;};
		P3=~P3;
		if (!P3_0) LCD_RegWrite(M_LCD_ALL_REV);
		else LCD_RegWrite(M_LCD_ALL_NOR);
		
		TimeDelay(10);
		LCD_DataWrite(0x55);
		j='A';
	};
}
