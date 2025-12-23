#include<LPC21XX.h>
#include "delay_header.h"
#define LCD_D 0xFF
#define RS 1<<8
#define E 1<<9
void init(void);
void cmd(unsigned char);
void data(unsigned char);
void integer(int n);
void string(unsigned char *);
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
void integer(int n){
	unsigned char arr[5];
	signed char i=0;
	if(n==0)
			data('0');
	else{
		if(n<0){
			data('-');
			n=-n;
		}
		while(n>0){
			arr[i++]=n%10;
			n=n/10;
		}
		for(i=i-1;i>=0;i--)
			data(arr[i]+48);
	}
}
void string(unsigned char *s){
	while(*s)
		data(*s++);
}

	