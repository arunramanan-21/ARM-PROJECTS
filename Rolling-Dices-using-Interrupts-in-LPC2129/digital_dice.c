#include<LPC21XX.h>
#include "lcd_header.h"
#include "delay.h"
void ext_int0_isr(void) __irq;
unsigned int val;
unsigned int count;
int main(){
	int i;
	PINSEL1=0x01;
	VICIntSelect=0;
	
	VICVectCntl0=(0x20)|14;
	VICVectAddr0=(unsigned long)ext_int0_isr;
	
	EXTMODE=0x01;
	EXTPOLAR=0x00;
	
	VICIntEnable=(1<<14);
	init();
	cmd(0x80);
	string("DIGITAL DICES:");
	cmd(0xC0);
	string("ROLL COUNT:");
	while(1){
		cmd(0x8F);
		integer(val);
		cmd(0xCB);
		integer((count/10));
		cmd(0xCC);
		integer((count%10));
	}
}
	
void ext_int0_isr(void) __irq{
	EXTINT=0x01;
	val=0;
	count++;
	T0PR=6;
	T0TCR=0x01;
	delay(count);
	while(val==0)
		val=T0PC;
	T0TCR=0x03;
	T0TCR=0x00;
	VICVectAddr=0;
}
