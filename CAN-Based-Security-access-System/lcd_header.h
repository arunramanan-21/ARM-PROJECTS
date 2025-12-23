#include<lpc21xx.h>
#define LCD_D 0xFF<<0
#define RS 1<<8
#define E 1<<9
typedef unsigned char varr;
void lcd_init(void);
void lcd_cmd(varr);
void lcd_data(varr);
void lcd_str(varr *);
void delay_ms(int);
void lcd_init(void){
	IODIR0|=LCD_D|RS|E;
	lcd_cmd(0x01);
	lcd_cmd(0x02);
	lcd_cmd(0x0c);
	lcd_cmd(0x38);
	lcd_cmd(0x80);
}
void lcd_cmd(varr cmd){
	IOCLR0=LCD_D;
	IOSET0=cmd;
	IOCLR0=RS;
	IOSET0=E;
	delay_ms(2);
	IOCLR0=E;
}
void lcd_data(varr data){
	IOCLR0=LCD_D;
	IOSET0=data;
	IOSET0=RS;
	IOSET0=E;
	delay_ms(2);
	IOCLR0=E;
}
void lcd_str(varr *s){
	while(*s)
		lcd_data(*s++);
}
void delay_ms(int ms){
	T0PR=60000-1;
	T0TCR=0x01;
	while(T0TC<ms);
	T0TCR=0x03;
	T0TCR=0x00;
}
