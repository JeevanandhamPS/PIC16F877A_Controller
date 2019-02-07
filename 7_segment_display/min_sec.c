#include<htc.h>
#define seg_1 RD3
#define seg_2 RD2
#define seg_3 RD1
#define seg_4 RD0



void second_1st_dig();
void second_2nd_dig();
void min_1st_dig();
void min_2nd_dig();	



__CONFIG(0x1F7A);
void delay();
void num();



int i,j,a,b,c,d,e,f;
char arr[]={0xFC,0X60,0XDA,0XF2,0X66,0XB6,0XBE,0XE0,0XFE,0XF6};



int main()
{
	TRISD3 = TRISD2 = TRISD1 = TRISD0 = 0;
	TRISB  = 0;
	while(1)
	{
		for(a=0;a<6;a++)
			for(b=0;b<10;b++)
					for(c=0;c<6;c++)
						for(d=0;d<10;d++)
								num();
	}
}



void num()
{
	for(i=0;i<10;i++)
	{
		TMR1CS	= 0;
		T1CKPS0	= 1;
		T1CKPS1	= 1;
		TMR1H	= 0X0B;
		TMR1L	= 0XDC;
		TMR1ON	= 1;
		while(!TMR1IF)
		{
			second_1st_dig(d);
			second_2nd_dig(c);
			min_1st_dig(b);
			min_2nd_dig(a);		
		}
		TMR1IF	= 0;
	}
}



void delay()
{
	for(j=0;j<1000;j++);
}



void second_1st_dig()
{
	seg_1	= 1;
	seg_4	= seg_3	= seg_2	= 0;
	PORTB	= arr[d];
	delay();
}



void second_2nd_dig()
{
	seg_2	= 1;
	seg_4	= seg_3	= seg_1	= 0;
	PORTB	= arr[c];
	delay();
}



void min_1st_dig()
{
	seg_3	= 1;
	seg_4	= seg_2	= seg_1	= 0;
	PORTB	= arr[b]+1;
	delay();
}



void min_2nd_dig()
{
	seg_4	= 1;
	seg_3	= seg_2	= seg_1	= 0;
	PORTB	= arr[a];
	delay();
}	