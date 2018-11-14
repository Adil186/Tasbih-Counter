# include <lpc214x.h>
# include "delay.h"
# define RS 8
# define EN 9
void init(void);
void comm(char);
void data(char);
void string(char *);
void lcd_num(unsigned int n);
int t=0;
int main()
{ int s;
	IO1DIR=0;
	init();
	comm(0x81);
	string("TASBIH COUNTER");
	while(1)
	{
		s=IO1PIN&(1<<16);
		{
		if(s==(1<<16))
		{ 
			comm(0xC5);	
			t=t+1;
			lcd_num(t);
			while(IO1PIN&1<<16);
		}
		else if(IO1PIN&1<<17)
		{
		 comm(0xC5);
			t=0;
      lcd_num(t);
			while(IO1PIN&1<<17);	
		}
	}
}
	}

void data(char x)
{
	IO0SET=x;
	IO0SET=1<<RS;//RS=1 FOR DATa
	IO0SET=1<<EN;// EN high
	delay(5);
	IO0CLR=1<<EN;// EN low
	IO0CLR=0xff;
}
void comm(char y)
{
	IO0SET=y;
	IO0CLR=1<<RS;//RS=0 FOR comm
	IO0SET=1<<EN;// EN high
	delay(5);
	IO0CLR=1<<EN;// EN low
	IO0CLR=0xff;
}
void init(void)
{ 
	IO0DIR=0x3ff;
	comm(0x38);// for 8 bit mode
	comm(0x06);// increment cursor
	comm(0x0E); // display on
	comm(0x01); // clear	
}
void string(char *p)
{
	while(*p!='\0')
	{
		data(*p);
		p++;
	}
}

void lcd_num(unsigned int n)
{
	
	data((n/1000)+48);
	n%=1000;
	
	data((n/100)+48);
	n%=100;
	
	data((n/10)+48);
	n%=10;
	
	data(n+48);
}