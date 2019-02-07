#include<htc.h>
__CONFIG(FOSC_HS & WDTE_OFF & PWRTE_OFF & BOREN_ON & LVP_OFF);
void delay();
int main()
{
	TRISB	= 0;
	char i,a;
	while(1)
	{
		a = 0x01;
		for(i=0;i<8;i++)
		{
			PORTB	= a;
			delay();
			a = (a<<1)+1;
		}
	}
}		
void delay()
{
	unsigned char i;
	for(i=0;i<10;i++)
	{
		TMR1CS	= 0;
		T1CKPS1 = 1;
		T1CKPS0 = 1;
		TMR1ON	= 1;
		TMR1H	= 0x0B;
		TMR1L	= 0xDB;
		while(!TMR1IF);
		TMR1IF	= 0;
	}
}
