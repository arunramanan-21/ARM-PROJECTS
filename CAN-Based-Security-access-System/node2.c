#include<lpc21xx.h>
#include "can_header.h"
#include "can_driver.h"
#define motor 1<<10
#define buz 1<<11
int main(){
	CAN_MSG k1;
	IODIR0|=motor|buz;
	IOSET0=buz;
	can_init();
	uart_init();
	while(1){
		can_rx(&k1);
		if(k1.id==(var)0x111){    //var is typedefname
				IOSET0=buz;
				IOSET0=motor;
				delay(1500);
				IOCLR0=motor;
		}
		else if(k1.id==(var)0x777){	  //var is typedefname
				IOCLR0=motor;
				IOCLR0=buz;
		}
	}
}
