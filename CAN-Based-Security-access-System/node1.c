#include<lpc21xx.h>
#include<string.h>
#include "can_header.h"
#include "can_driver.h"
#define ms1 1<<7
#define ms2 1<<8;
typedef unsigned int y;
int main(){
	CAN_MSG m1,m2;
	char id[20];
	y i=0;
	can_init();
	uart_init();
	IODIR0|=ms1|ms2;
	IOSET0=ms1|ms2;
	m1.id=0x111;
	m1.rtr=0;
	m1.dlc=4;
	m2.id=0x777;
	m2.rtr=0;
	m2.dlc=4;
	while(1){
		while(i<12){
			id[i++]=uart_rx();
		}
		id[i]='\0';
		i=0;
		uart_str(id);
		if(strcmp(id,"0600674E634C")==0){
			m1.byteA=0x11223344;
			m1.byteB=0;
			can_tx(m1);
			IOSET0=ms2;
			IOCLR0=ms1;
		}
		else{
			m2.byteA=0x44332211;
			m2.byteB=0;
			can_tx(m2);
			IOSET0=ms1;
			IOCLR0=ms2;
		}
	}
}



