#include<htc.h>
#define _XTL_FREQ 2000000
__CONFIG(FOSC_HS & WDTE_OFF & PWRTE_OFF & BOREN_ON & LVP_OFF);
void uart_tx(unsigned char val);
unsigned char uart_rx(void);
void uart_init(void);
void delay();


void delay()
{
	TMR1CS	= 0;
	T1CKPS0	= 1;
	T1CKPS1	= 1;
	TMR1H	= 0X3C;
	TMR1L	= 0XB0;
	TMR1ON	= 1;
	while(TMR1IF==0);
	TMR1IF	= 0;
	TMR1ON= 1;
}


int main()
{
	uart_init();
	uart_tx('a');
	delay();
	uart_tx('b');
	delay();
	uart_tx('c');
	delay();
	uart_tx('d');
	delay();
	while(1);
}


void uart_tx(unsigned char val)
{
	TXREG	= val;
	while(TXIF == 0);
	TXIF = 0;
}


unsigned char uart_rx(void)
{
	while(RCIF == 0);
	RCIF = 0;
	return RCREG;
}


void uart_init(void)
{
	TRISC6	= 0;
	TRISC7	= 1;
	TXSTA	= 0X00;
	RCSTA	= 0X00;
	SPBRG	= 31;
	TXEN	= 1;
	SPEN	= 1;
	TXIF	= 0;
	RCIF	= 0;
}