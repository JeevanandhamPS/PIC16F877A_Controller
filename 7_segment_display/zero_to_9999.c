#include<htc.h>
__CONFIG(0x1F7A);
void delay();
void delay1();
void delay3();
void num();

int i,j,k,a,b,c,d;
char arr[]={0xFC,0X60,0XDA,0XF2,0X66,0XB6,0XBE,0XE0,0XFE,0XF6};

int main()
{
	TRISD3	= 0;
	TRISD2	= 0;
	TRISD1	= 0;
	TRISD0	= 0;
	TRISB	= 0;
	while(1)
	{
		for(a=0;a<10;a++)
			for(b=0;b<10;b++)
				for(c=0;c<10;c++)
					for(d=0;d<10;d++)
						num();
	}
}
void num()
{
	for(k=-100;k<100;k++)
	{
		RD0		= 0;
		RD1		= 0;
		RD2		= 0;
		RD3		= 1;
		PORTB	= arr[d];
		delay();
		RD0		= 0;
		RD1		= 0;
		RD2		= 1;
		RD3		= 0;
		PORTB	= arr[c];
		delay();
		RD0		= 0;
		RD1		= 1;
		RD2		= 0;
		RD3		= 0;
		PORTB	= arr[b];
		delay();
		RD0		= 1;
		RD1		= 0;
		RD2		= 0;
		RD3		= 0;
		PORTB	= arr[a];
		delay();
	}
}

void delay()
{
	for(j=0;j<10;j++);
}
	

void delay1()
{
	for(j=0;j<200;j++);
}


void delay3()
{
	for(j=-30000;j<30000;j++);
}