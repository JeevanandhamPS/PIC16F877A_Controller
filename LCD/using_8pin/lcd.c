#include<htc.h>
#define _XTAL_FREQ 20000000
__CONFIG(FOSC_HS & WDTE_OFF & PWRTE_OFF & BOREN_ON & LVP_OFF);


#define RS RC0
#define RW RC1
#define EN RC2


void delay();
void lcd_cmd(unsigned char cmd);
void lcd_data(unsigned char data);


int main()
{
	int i;
	int a[11]={80,46,83,46,74,69,69,86,65,49,49};//{78,65,78,68,72,65,77};
	TRISD	= 0;
	TRISC	= 0;
	PORTB	= 0x00;

	lcd_cmd(0x38);
	lcd_cmd(0x01);
	lcd_cmd(0x02);
	lcd_cmd(0x0F);
	lcd_cmd(0X06);
	lcd_cmd(0X80);
	
	for(i=0;i<16;i++)
	{
		i<11?lcd_data(a[i]):lcd_data('.');
		//lcd_data('a');
	}
	while(1);
}


void delay()
{
	TMR1CS	= 0;
	T1CKPS0	= 1;
	T1CKPS1	= 1;
	TMR1H	= 0X3C;
	TMR1L	= 0XB0;
	TMR1ON	= 1;
	while(TMR1IF==0);
	TMR1IF	= 0;
	TMR1ON= 1;
}


void lcd_cmd(unsigned char cmd)
{
	RS		= 0;
	RW		= 0;
	EN 		= 1;
	PORTD	= cmd;
	delay();
	EN		= 0;
}


void lcd_data(unsigned char data)
{
	RS		= 1;
	RW		= 0;
	EN		= 1;
	PORTD	= data;
	delay();
	EN		= 0;
}