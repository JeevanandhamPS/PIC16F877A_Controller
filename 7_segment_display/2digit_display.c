#include<htc.h>
__CONFIG(0x1F7A);
void delay();
void delay1();


int main()
{
	while(1)
	{
		TRISD2	= 0;
		TRISD3	= 0;
		TRISB	= 0;
		RD2		= 0;
		RD3		= 1;
		PORTB	= 0x60;
		delay();
		RD2		= 1;
		RD3		= 0;
		PORTB	= 0xFC;
		delay1();
	}
}

void delay()
{
	int i;
	for(i=0;i<20;i++);
}
	

void delay1()
{
	int i;
	for(i=0;i<200;i++);
}
