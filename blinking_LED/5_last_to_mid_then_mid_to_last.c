#include<htc.h>
__CONFIG(FOSC_HS & WDTE_OFF & PWRTE_OFF & BOREN_ON & LVP_OFF);
void delay();

int main()
{
	TRISB	= 0;
	unsigned char i,a,b;
	while(1)
	{
		a=0x01;
		b=0x80;
		for(i=0;i<4;i++)
		{
			PORTB	= a+b;
			delay();
			if(i!=3)
			{
				a	= (a<<1)+1;
				b	= (b>>1)+0x80;
			}
		}
		for(i=0;i<3;i++)
		{
			a	= a>>1;
			b	= b<<1;
			if(i!=2)
			{
				PORTB	= a+b;
				delay();
			}
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