#include<htc.h>
#include<stdio.h>
#define _XTAL_FREQ 20000000
__CONFIG(FOSC_HS&WDTE_OFF&PWRTE_OFF&BOREN_ON&LVP_OFF);

void print_uart(unsigned char *str);
void i2c_init(void);
void uart_init(void);
void uart_tx(unsigned char val);
void delay();
void i2c_wait();
void i2c_start();
void i2c_write(unsigned int data);
unsigned short i2c_read(unsigned short ack);
void i2c_stop();
void i2c();
unsigned char string[50] = "First Controller is working\r";

int a[8],i,strt,chk;
unsigned char buffer[50];


int main()
{
	TRISB0	= 1;
	TRISC0	= 0;
	OPTION_REG	= 0x00;
	GIE		= 1;
	PEIE 	= 1;
	INTE 	= 1; 
	uart_init();
	i2c_init();
	delay();
	i2c_wait();
	i2c_start();
	i2c_write(0xD0);
	i2c_write(0x07);
	i2c_write(0x10);
	i2c_stop();	
	while(1)
	{
		if(strt==1)
		{
			i2c();
			strt = 0;
		}
		else
			strt = 0;
		chk = 1;
		while(chk==1);
	}
}	

void interrupt ISR(void)
{
	if(INTF)
	{
		strt = 1;
		RC0	 = 1;
		chk  = 0;
	}
	INTF = 0;
	RC0	 = 0;
}




void i2c()
{		
		i2c_wait();
		i2c_start();
		i2c_write(0xD0);
		i2c_write(0x00);
		i2c_stop();
	
		i2c_wait();
		i2c_start();
		i2c_write(0xD1);
		for(i=0;i<8;i++)
		{
			a[i] = i2c_read(1);
		}
		i2c_stop();
	
		sprintf(buffer,"%x : %x : %x\r%x\r%x : %x : %x\r",a[2],a[1],a[0],a[3],a[4],a[5],a[6]);
		print_uart(buffer);
}

void print_uart(unsigned char *str)
{
	
	while(*str)
	{
		uart_tx(*str);
		str++;
	}
}
void uart_tx(unsigned char val)
{
	TXREG=val;
	while(TXIF==0);
	TXIF=0;
}	
void i2c_init(void)
{
    SSPCON  = 0x28; 
    SSPCON2 = 0x00;
    SSPADD  = 49;
    SSPSTAT = 0x00;
}
void i2c_wait()
{
    while ((SSPCON2 & 0x1f) || (SSPSTAT & 0x04)); 
}
void i2c_start()
{
  i2c_wait(); 
  SEN = 1;    
}
void i2c_write(unsigned int data)
{
  i2c_wait(); 
  SSPBUF = data;
}
unsigned short i2c_read(unsigned short ack)
{
	unsigned short recv;
	i2c_wait();
	RCEN = 1;
	i2c_wait();
	recv = SSPBUF;
	i2c_wait();
	ACKDT = (ack)?0:1;
	ACKEN = 1;
	return recv;
}
void i2c_stop()
{
	i2c_wait();
	PEN = 1;   
}
void delay()
{
	TMR1CS=0;
	T1CKPS0=1;
	T1CKPS1=1;
	TMR1H=0X3C;
	TMR1L=0XB0;
	TMR1ON=1;
	while(!TMR1IF);
			TMR1IF=0;
	TMR1ON=0;
}
void uart_init(void)
{
	TRISC6=0;
	TRISC7=1;
	SPBRG=31;
	TXEN=1;
	SPEN=1;
	TXIF=0;
	RCIF=0;
}
