#include<htc.h>
__CONFIG(0x1F7A);
void delay();
int main()
{
	unsigned char i,x = 0x08, y = 0x10;
	TRISB	= 0;
	while(1)
	{
		for(i=0;i<4;i++)
		{
			PORTB = x+y;
			delay();
			if(i!=3)
			{
				x=(x>>1)|8;
				y=(y<<1)|0x10;
			}
		}
		for(i=0;i<3;i++)
		{
			x=(x<<1)^0x10;
			y=(y>>1)^8;
			if(i!=2)
			{
				PORTB = x+y;
				delay();
			}
		}
	}
}
void delay()
{
  int i;
  for(i=0;i<10;i++)
  {
	TMR1CS	= 0;
	T1CKPS1	= 1;
	T1CKPS0	= 1;
	TMR1H	= 0X0B;
	TMR1L	= 0XDB;
	TMR1ON	= 1;
	while(!TMR1IF);
	TMR1IF  = 0;
  }
}    