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

unsigned char string[]="PIC initialized...\r";

int main()
{
	int a[8],i=0;
	TRISB = 0;
	unsigned char buffer[50];
	
	uart_init();
	i2c_init();
	
	print_uart(string);

	
	i2c_wait();
	i2c_start();
	i2c_write(0xD0);//sending device addres with write flag
	i2c_write(0x00);//sending ram address 0x00
	i2c_stop();
	
	delay();
	i2c_wait();
	
	i2c_start();
	i2c_write(0xD0);//sending device addres with write flag
	i2c_write(0x00);//sending ram address 0x00
	i2c_stop();
	
	i2c_start();
	i2c_write(0xD7);
	i2c_write(0x90);
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
	while(1);
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
    SSPCON = 0x28; //I2C master mode and "enabling MSSP module to set I/O pins to I2C pins"
    SSPCON2 = 0x00; //Clearing SSPCON2
    SSPADD  = 49;//calculated values
    SSPSTAT = 0x00; //clearing SSPSTAT
}
void i2c_wait()
{
    while ((SSPCON2 & 0x1f) || (SSPSTAT & 0x04)   ) ; //check  this on registers to make sure the IIC is not in progress
	//while(!SSPIF);
	//SSPIF	= 0;
}
void i2c_start()
{
  i2c_wait();  //wait if I2C is busy 
  SEN = 1;     //Set start condition
}
void i2c_write(unsigned int data)
{
  i2c_wait(); //wait if I2C is busy 
  SSPBUF = data;//writing data to send
}
unsigned short i2c_read(unsigned short ack)
{
	unsigned short recv;
	i2c_wait();
	RCEN = 1;
	i2c_wait();
	recv = SSPBUF;//get the data saved in SSPBUF
	i2c_wait();
	ACKDT = (ack)?0:1;//check if ack bit received 
	ACKEN = 1;//pg 85/234
	return recv;
}
void i2c_stop()
{
	i2c_wait(); //wait if I2C is busy  
	PEN = 1;    //Set stop condition
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