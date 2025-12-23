#include<lpc21xx.h>
#include "delay.h"
#define lcd_d 0xff
#define rs 1<<8
#define e 1<<9
unsigned char caadd1=0x80,caadd2=0xc0,car_org_add;
unsigned char ad1=0x84,ad2=0xc7,ad3=0x8a,ad4=0xcf;
void lcd_init(void);
void lcd_cmd(unsigned char );
void lcd_data(unsigned char);
void lcd_string(unsigned char*);
void lcd_int(unsigned int);
void carmo( char*);
unsigned int i=0,l=0;
char car[]={0x00,0x09,0x1b,0x1d,0x1d,0x1b,0x09,0x00,0x00,0x0d,0x1f,0x1f,0x1f,0x1b,0x1b,0x00};
void ext_int0(void)__irq
{
	EXTINT=0X01;
	i++;
	VICVectAddr=0;
	
}
int  main()
{
	lcd_init();
	PINSEL1=0X01;
	//IODIR0=1<<0;
	VICIntSelect=0;
	VICVectCntl0=(0X20)|14;
	VICVectAddr0=(unsigned long)ext_int0;
	EXTMODE=0X01;
	EXTPOLAR=0X01;
	VICIntEnable=1<<14;
	carmo(car);
	lcd_cmd(0x80);
	lcd_data(1);
	while(1)
	{
		if((i%2)!=0)
		{
			car_org_add=caadd2;		
			lcd_cmd(caadd2);
			lcd_data(1);
		}
		if((i%2)==0)
		{
			car_org_add=caadd1;		
			lcd_cmd(caadd1);
			lcd_data(1);
		}
	//delay(300);
		lcd_cmd(ad1--);
		lcd_data(0);
		lcd_cmd(ad2--);
		lcd_data(0);
		lcd_cmd(ad3--);
		lcd_data(0);
		lcd_cmd(ad4--);
		lcd_data(0);
		if(ad1==0x7f)
		{
			l++;
			ad1=0x8f;
		}
		if(ad2==0xbf)
		{
			l++;
			ad2=0xcf;
		}
		if(ad3==0x7f)
		{
			l++;
			ad3=0x8f;
		
		}
		if(ad4==0xbf)
		{
			l++;
			ad4=0xcf;
		}
			if(l>100)
				delay_ms(400);
			else if(l>60)
				delay_ms(500);
			else if(l>30)
				delay_ms(600);
			else
				delay_ms(700);
		if(car_org_add==(ad1))
		{
			lcd_cmd(0x01);
			lcd_cmd(0x80);
			lcd_string("game over");
			while(1)
			{
				lcd_cmd(0xc0);
				lcd_string("score ");
				lcd_int(l);
			}
		}
		else if(car_org_add==(ad2))
		{
			lcd_cmd(0x01);
			lcd_cmd(0x80);
			lcd_string("game over");
			while(1)
			{
				lcd_cmd(0xc0);
				lcd_string("score ");
				lcd_int(l);
			}
		}
		else if(car_org_add==(ad3))
		{
			lcd_cmd(0x01);
			lcd_cmd(0x80);
			lcd_string("game over");
			while(1)
			{
				lcd_cmd(0xc0);
				lcd_string("score ");
				lcd_int(l);
			}
		}
		else if(car_org_add==(ad4))
		{
			lcd_cmd(0x01);
			lcd_cmd(0x80);
			lcd_string("game over");
			while(1)
			{
				lcd_cmd(0xc0);
				lcd_string("score ");
				lcd_int(l);
			}
		}
		lcd_cmd(0x01);

		
	}
}
void lcd_init()
{
	IODIR0=lcd_d|rs|e;
	lcd_cmd(0x01);
	lcd_cmd(0x02);
	lcd_cmd(0x0c);
	lcd_cmd(0x38);
	lcd_cmd(0x80);
}
void lcd_cmd(unsigned char cmd)
{
	IOCLR0=lcd_d;
	IOSET0=cmd;
	IOCLR0=rs;
	IOSET0=e;
	delay_ms(2);
	IOCLR0=e;
}
void lcd_data(unsigned char d)
{
	IOCLR0=lcd_d;
	IOSET0=d;
	IOSET0=rs;
	IOSET0=e;
	delay_ms(2);
	IOCLR0=e;
}
void lcd_string(unsigned char*s)
{

	while(*s)
	{
		lcd_data(*s++);
	}
}
void carmo(char*s)
{
	lcd_cmd(0x40);
	for(i=0;i<16;i++)
	{
		lcd_data(car[i]);
	}
	i=0;
}
void lcd_int(unsigned int k)
{
	lcd_data((k/100)+48);
	lcd_data((k/10)+48);
	lcd_data((k%10)+48);
 