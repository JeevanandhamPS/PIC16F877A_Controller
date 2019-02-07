#include<htc.h>
__CONFIG(FOSC_HS & WDTE_OFF & PWRTE_OFF & BOREN_ON & LVP_OFF);


//#define RS RC0
//#define RW RC1
//#define EN RC2


#define  row_1		RD0
#define  row_2      RD1
#define  row_3      RD2
#define  row_4      RD3
                     
#define  coloumn_1  RD4
#define  coloumn_2  RD5
#define  coloumn_3  RD6
#define  coloumn_4  RD7

void delay();
//void lcd_cmd(unsigned char cmd);
//void lcd_data(unsigned char data);
void uart_tx(unsigned char val);
unsigned char uart_rc(void);
void uart_init(void);

int main()
{
	uart_init();
	TRISD	= 0xF0;	//Make row as output/coloumn as input..
	TRISB   = 0;
	TRISC0	= 0;
	TRISC1	= 0;
	TRISC2	= 0;
	TRISC6	= 0;
	TRISC7	= 1;
	TRISB	= 0;	
	PORTD	= 0x0F;
	
	/*lcd_cmd(0x38);
	lcd_cmd(0x01);
	lcd_cmd(0x02);
	lcd_cmd(0x0F);
	lcd_cmd(0X06);
	lcd_cmd(0X80);*/
	
	while(1)
	{
		row_1	= 1;
		row_2 = row_3 = row_4 = 0;
		if(PORTD == 0x11)
		{
			//lcd_data('7');
			uart_tx('7');
			while(coloumn_1==1);
			
		}
		else if(PORTD == 0x21)
		{
			//lcd_data('8');
			uart_tx('8');
			while(coloumn_2==1);

		}
		else if(PORTD == 0x41)
		{
			//lcd_data('9');
			uart_tx('9');
			while(coloumn_3==1);

		}
		else if(PORTD == 0x81)
		{
			//lcd_data('A');
			uart_tx('A');
			while(coloumn_4==1);

		}
		else
		{
			RS = 0;
			RW = 0;
			EN = 0;
		}
		row_1	= 0;
		row_2	= 1;
		row_3	= 0;
		row_4	= 0;
		if(PORTD == 0x12)
		{
			//lcd_data('4');
			uart_tx('4');
			while(coloumn_1==1);

		}
		else if(PORTD == 0x22)
		{
			//lcd_data('5');
			uart_tx('5');
			while(coloumn_2==1);
		}
		else if(PORTD == 0x42)
		{
			//lcd_data('6');
			uart_tx('6');
			while(coloumn_3==1);

		}
		else if(PORTD == 0x82)
		{
			//lcd_data('B');
			uart_tx('B');
			while(coloumn_4==1);
		}
		else
		{
			RS = 0;
			RW = 0;
			EN = 0;

		}
		row_1	= 0;
		row_2	= 0;
		row_3	= 1;
		row_4	= 0;
		if(PORTD == 0x14)
		{
			//lcd_data('1');
			uart_tx('1');
			while(coloumn_1==1);
		}
		else if(PORTD == 0x24)
		{
			//lcd_data('2');
			uart_tx('2');
			while(coloumn_2==1);

		}
		else if(PORTD == 0x44)
		{
			//lcd_data('3');
			uart_tx('3');
			while(coloumn_3==1);

		}
		else if(PORTD == 0x84)
		{
			//lcd_data('C');
			uart_tx('C');
			while(coloumn_4==1);

		}	
		else
		{		
			RS = 0;
			RW = 0;
			EN = 0;

		}
		row_1	= 0;
		row_2	= 0;
		row_3	= 0;
		row_4	= 1;
		if(PORTD == 0x18)
		{
			//lcd_data('/');
			uart_tx('/');
			while(coloumn_1==1);

		}
		else if(PORTD == 0x28)
		{
			//lcd_data('0');
			uart_tx('0');
			while(coloumn_2==1);

		}
		else if(PORTD == 0x48)
		{
			//lcd_data('=');
			uart_tx('=');
			while(coloumn_3==1);

		}
		else if(PORTD == 0x88)
		{
			//lcd_data('D');
			uart_tx('D');
			while(coloumn_4==1);

		}	
		else
		{
			RS = 0;
			RW = 0;
			EN = 0;
		}
		
	}
}



void lcd_cmd(unsigned char cmd)
{
	RS		= 0;
	RW		= 0;
	EN 		= 1;
	PORTB	= cmd;
	delay();
	EN		= 0;
}


void lcd_data(unsigned char data)
{
	RS		= 1;
	RW		= 0;
	EN		= 1;
	PORTB	= data;
	delay();
	EN		= 0;
}


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


void uart_tx(unsigned char val)
{

	TXREG = val;
	while(TXIF==0);
	TXIF=0;
}

unsigned char uart_rc(void)
{
	while(RCIF==0);
	RCIF=0;
	return RCREG;
}

void uart_init(void)
{
	TRISC6 = 0; //making TX as output
	TRISC7 = 1; //making RX as input

	TXSTA = 0x00; //Asynchronous mode, 8bit, low speed
	RCSTA = 0x00; //Enable UART to use RC7 and RC6 as UART module pins
	SPBRG = 31; //to generate 9600 baudrate
	TXEN = 1;
	SPEN = 1;
	TXIF=0;
	RCIF=0;
}