#include<LPC21XX.h>
#include "delay_header.h"
#define LCD_D 0xFF
#define RS 1<<8
#define E 1<<9
void init(void);
void cmd(unsigned char);
void data(unsigned char);
void init(void){
	IODIR0=LCD_D|RS|E;
	cmd(0x01);
	cmd(0x02);
	cmd(0x0C);
	cmd(0x38);
	cmd(0x80);
}
void cmd(unsigned char m){
	IOCLR0=LCD_D;
	IOSET0=m;
	IOCLR0=RS;
	IOSET0=E;
	delay(2);
	IOCLR0=E;
}
void data(unsigned char d){
	IOCLR0=LCD_D;
	IOSET0=d;
	IOSET0=RS;
	IOSET0=E;
	delay(2);
	IOCLR0=E;
}
	