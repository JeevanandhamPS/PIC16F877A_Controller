#include<htc.h>
__CONFIG(0x1F7A);

#define RS RB1
#define RW RB2
#define EN RB3


#define  row_1		RD0
#define  row_2      RD1
#define  row_3      RD2
#define  row_4      RD3
                     
#define  coloumn_1  RD4
#define  coloumn_2  RD5
#define  coloumn_3  RD6
#define  coloumn_4  RD7


void delay();
void lcd_cmd(unsigned char cmd);
void lcd_data(unsigned char data);


int main()
{
	int i;
	int a[11]={80,46,83,46,74,69,69,86,65,49,49};//{78,65,78,68,72,65,77};
	TRISD	= 0xF0;	//Make row as output/coloumn as input..
	TRISC	= 0;	//lcd connection.. PORTC as output...
	TRISB1  = TRISB2 = TRISB3 = 0;	
	PORTD	= 0x0F;
	

	lcd_cmd(0x38);
	lcd_cmd(0x01);
	lcd_cmd(0x02);
	lcd_cmd(0x0F);
	lcd_cmd(0X06);
	lcd_cmd(0X80);
	
	while(1)
	{
		row_1	= 1;
		row_2 = row_3 = row_4 = 0;
		if(PORTD == 0x11)
		{
			lcd_data(a[0]);	
			while(coloumn_1==1);
			
		}
		else if(PORTD == 0x21)
		{
			lcd_data(a[1]);
			while(coloumn_2==1);

		}
		else if(PORTD == 0x41)
		{
			lcd_data(a[2]);
			while(coloumn_3==1);

		}
		else if(PORTD == 0x81)
		{
			lcd_data(a[3]);
			while(coloumn_4==1);

		}
		row_1	= 0;
		row_2	= 1;
		row_3	= 0;
		row_4	= 0;
		if(PORTD == 0x12)
		{
			lcd_data(a[4]);
			while(coloumn_1==1);

		}
		else if(PORTD == 0x22)
		{
			lcd_data(a[5]);
			while(coloumn_2==1);
		}
		else if(PORTD == 0x42)
		{
			lcd_data(a[6]);
			while(coloumn_3==1);

		}
		else if(PORTD == 0x82)
		{
			lcd_data(a[6]);
			while(coloumn_4==1);
		}
		row_1	= 0;
		row_2	= 0;
		row_3	= 1;
		row_4	= 0;
		if(PORTD == 0x14)
		{
			lcd_data(a[7]);
			while(coloumn_1==1);
		}
		else if(PORTD == 0x24)
		{
			lcd_data(a[8]);
			while(coloumn_2==1);

		}
		else if(PORTD == 0x44)
		{
			lcd_data(a[9]);
			while(coloumn_3==1);

		}
		else if(PORTD == 0x84)
		{
			lcd_data(a[10]);
			while(coloumn_4==1);

		}
		row_1	= 0;
		row_2	= 0;
		row_3	= 0;
		row_4	= 1;
		if(PORTD == 0x18)
		{
			lcd_data(a[11]);
			while(coloumn_1==1);

		}
		else if(PORTD == 0x28)
		{
			lcd_data(a[0]);
			while(coloumn_2==1);

		}
		else if(PORTD == 0x48)
		{
			lcd_data(a[1]);
			while(coloumn_3==1);

		}
		else if(PORTD == 0x88)
		{
			lcd_data(a[2]);
			while(coloumn_4==1);

		}
	}
}


void lcd_cmd(unsigned char cmd)
{
	RS		= 0;
	RW		= 0;
	EN 		= 1;
	PORTC	= cmd;
	delay();
	EN		= 0;
}


void lcd_data(unsigned char data)
{
	RS		= 1;
	RW		= 0;
	EN		= 1;
	PORTC	= data;
	delay();
	EN		= 0;
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

