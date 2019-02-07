#include<htc.h>
#define _XTAL_FREQ 20000000
__CONFIG(0x1F7A);


#define RS RC0
#define RW RC1
#define EN RC2


void delay();
void lcd_cmd(unsigned char cmd);
void lcd_data(unsigned char data);


int main()
{
	int i;
	
	TRISC0 = TRISC1 = TRISC2 = 0;
	TRISD4 = TRISD5 = TRISD6 = TRISD7 = 0;

	for(i=0;i<3;i++)
	{
		lcd_cmd(0x30);
		delay();
	}
	lcd_cmd(0x01);
	lcd_cmd(0x02);
	lcd_cmd(0x06);
	lcd_cmd(0x10);
	lcd_cmd(0x0F);
	lcd_cmd(0x80);
	lcd_data('a');
	lcd_data('b');
	lcd_data('c');
	lcd_data('d');
	lcd_data('e');
}


void lcd_cmd(unsigned char cmd)
{
	RS		= 0;
	RW		= 0;
	EN		= 1;
	PORTD	= cmd & 0xF0;
	delay();
	EN		= 0;
	delay();
	RS		= 0;
	RW		= 0;
	EN		= 1;
	PORTD	= (cmd << 4) & 0xF0;
	delay();
	EN		= 0;
	delay();
}


void lcd_data(unsigned char data)
{
	RS		= 1;
	RW		= 0;
	EN		= 1;
	PORTD	= data & 0xF0;
	delay();
	EN		= 0;
	delay();
	RS		= 1;
	RW		= 0;
	EN		= 1;
	PORTD	= (data << 4) & 0xF0;
	delay();
	EN		= 0;
	delay();
}


void delay()
{
	TMR1CS	= 0;
	T1CKPS1	= 1;
	T1CKPS0	= 1;
	TMR1H	= 0x0B;
	TMR1L	= 0xDB;
	TMR1ON	= 1;
	while(!TMR1IF);
	TMR1IF	= 0;
	TMR1ON	= 1;
}