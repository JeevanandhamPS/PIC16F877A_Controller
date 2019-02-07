#include<htc.h>
__CONFIG(FOSC_HS & WDTE_OFF & PWRTE_OFF & BOREN_ON & LVP_OFF);

#define  row_1	    RD0
#define  row_2      RD1
#define  row_3      RD2
#define  row_4      RD3
                     
#define  coloumn_1  RD4
#define  coloumn_2  RD5
#define  coloumn_3  RD6
#define  coloumn_4  RD7


int main()
{
	TRISD	= 0xF0;	//Make row as output/coloumn as input..
	TRISB	= 0;	//7-segment connection.. PORTB as output...
	TRISB1	= 0;	//RD0 as output.. for 7-segment..
	RB1		= 1;
	RBIF	= 0;
	PORTD	= 0x0F;
	while(1)
	{
		row_1	= 1;
		row_2 = row_3 = row_4 = 0;
		if(PORTD == 0x11)
		{
			PORTB	= 0xE0;	
			while(coloumn_1==1);
			
		}
		else if(PORTD == 0x21)
		{
			PORTB	= 0xFE;
			while(coloumn_2==1);

		}
		else if(PORTD == 0x41)
		{
			PORTB	= 0xF6;
			while(coloumn_3==1);

		}
		else if(PORTD == 0x81)
		{
			PORTB	= 0xEE;
			while(coloumn_4==1);

		}
		else
		{
			PORTB = 0x00;
		}
		row_1	= 0;
		row_2	= 1;
		row_3	= 0;
		row_4	= 0;
		if(PORTD == 0x12)
		{
			PORTB	= 0x66;
			while(coloumn_1==1);

		}
		else if(PORTD == 0x22)
		{
			PORTB	= 0xB6;
			while(coloumn_2==1);
		}
		else if(PORTD == 0x42)
		{
			PORTB	= 0xBE;
			while(coloumn_3==1);

		}
		else if(PORTD == 0x82)
		{
			PORTB	= 0x3E;
			while(coloumn_4==1);
		}
		else
		{
			PORTB = 0x00;
		}
		row_1	= 0;
		row_2	= 0;
		row_3	= 1;
		row_4	= 0;
		if(PORTD == 0x14)
		{
			PORTB	= 0x60;
			while(coloumn_1==1);
		}
		else if(PORTD == 0x24)
		{
			PORTB	= 0xDA;
			while(coloumn_2==1);

		}
		else if(PORTD == 0x44)
		{
			PORTB	= 0xF2;
			while(coloumn_3==1);

		}
		else if(PORTD == 0x84)
		{
			PORTB	= 0x1A;
			while(coloumn_4==1);

		}	
		else
		{
			PORTB = 0x00;
		}
		row_1	= 0;
		row_2	= 0;
		row_3	= 0;
		row_4	= 1;
		if(PORTD == 0x18)
		{
			PORTB	= 0x02;
			while(coloumn_1==1);

		}
		else if(PORTD == 0x28)
		{
			PORTB	= 0xFC;
			while(coloumn_2==1);

		}
		else if(PORTD == 0x48)
		{
			PORTB	= 0x02;
			while(coloumn_3==1);

		}
		else if(PORTD == 0x88)
		{
			PORTB	= 0x7A;
			while(coloumn_4==1);

		}	
		else
		{			
			PORTB = 0x00;
		}
		
	}
}
