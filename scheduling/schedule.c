#include<htc.h>
__CONFIG(FOSC_HS & WDTE_OFF & PWRTE_OFF & BOREN_ON & LVP_OFF);
unsigned char ptrc = 0x00,ptrd = 0x00,count = 1,wait = 0; 
unsigned char val1 = 0,val2 = 0;
void portc(void);
void portd(void);
void delay_s(void);


int main()
{
	TMR0IF	= 0;
	GIE 	= 1;
	PEIE	= 1;
	TRISC = TRISD	= 0x00;
	delay_s();
	while(1)
	{
		switch(count)
		{
			case 400:
				portc();
				break;
			case 800:
				portc();
				portd();
				break;
			default:
				break;
		}
		wait = 1;
		while(wait==1);
	}
}

void interrupt ISR(void)
{
	
	if(TMR0IF == 1)
	{
		TMR0IE	= 0;
		TMR0IF	= 0;
		wait 	= 0;
		
		if(count<=1000)
			count = count + 1;
		else
			count = 1;
		
		TMR0	= 31;
		TMR0IE	= 1;
	}
}



void delay_s()	
{
	T0CS 	= 0;
	T0SE 	= 0;
	PSA 	= 0;
	PS0		= 0;
	PS1		= 0;
	PS2 	= 1;
	TMR0IF  = 0;
	TMR0IE	= 1;
	TMR0	= 31;
}

void portc(void)
{
	ptrc  = ~ptrc;
	PORTC = ptrc;
}

void portd(void)
{
	ptrd = ~ptrd;
	PORTD = ptrd;
}
