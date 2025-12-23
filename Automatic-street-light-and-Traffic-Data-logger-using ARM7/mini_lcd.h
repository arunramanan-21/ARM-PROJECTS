#include<LPC21xx.h>
#define LCD_D 0xFF<<8
#define RS 1<<5
#define E 1<<6
void LCD_INIT(void);
void LCD_CMD(unsigned char);
void LCD_DATA(unsigned char);
void LCD_STRING(unsigned char *);
void lCD_INTEGER(int);
void delay(int);
void LCD_INIT(void){
	IODIR0|=LCD_D |RS |E;
	LCD_CMD(0x01);
	LCD_CMD(0x02);
	LCD_CMD(0x0C);
	LCD_CMD(0x38);
	LCD_CMD(0x80);
}
void LCD_CMD(unsigned char cmd){
	IOCLR0=LCD_D;
	IOSET0=cmd<<8;
	IOCLR0=RS;
	IOSET0=E;
	delay(2);
	IOCLR0=E;
}
void LCD_DATA(unsigned char d){
	IOCLR0=LCD_D;
	IOSET0=d<<8;
	IOSET0=RS;
	IOSET0=E;
	delay(2);
	IOCLR0=E;
}
void LCD_STRING(unsigned char *s){
int count=0;
	while(*s)
	{
		LCD_DATA(*s++);
		count++;
		if(count==16)
		LCD_CMD(0XC0);
		}
}
void LCD_INTEGER(int n){
	unsigned char arr[5];
	signed char i=0;
	if(n==0){
		LCD_DATA('0');
	}
	else{
		if(n<0){
			LCD_DATA('-');
			n=-n;
		}
		while(n>0){
			arr[i++]=n%10;
			n=n/10;
		}
		for(i=i-1;i>=0;i--)
			LCD_DATA(arr[i]+48);
	}
}
void delay(int ms){
	T0PR=15000-1;
	T0TCR=0x01;
	while(T0TC<ms);
	T0TCR=0x03;
	T0TCR=0x00;
}
