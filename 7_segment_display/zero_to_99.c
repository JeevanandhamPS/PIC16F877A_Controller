#include<htc.h>
__CONFIG(0x1F7A);
void delay();
void delay1();
void num();

int i,j,k,l;
char arr[]={0xFC,0X60,0XDA,0XF2,0X66,0XB6,0XBE,0XE0,0XFE,0XF6};

int main()
{
	TRISD2	= 0;
	TRISD3	= 0;
	TRISB	= 0;
	while(1)
	{
		for(i=0;i<10;i++)
			for(l=0;l<10;l++)
			{
				num();
			}	
	}
}


void num()
{
	for(k=0;k<100;k++)
	{
		RD2		= 0;
		RD3		= 1;
		PORTB	= arr[l];
		delay();
		RD2		= 1;
		RD3		= 0;
		PORTB	= arr[i];
		delay1();
	}
}

void delay()
{
	for(j=0;j<1000;j++);
}
	

void delay1()
{
	for(j=0;j<1000;j++);
}