#include<lpc21xx.h>
#include "can_header.h"
#include "can_driver.h"
#include "lcd_header.h"
#define accept_led 1<<18
#define no_accept_led 1<<19
int main(){
	CAN_MSG l1;
	IODIR0|=accept_led|no_accept_led;
	can_init();
	//uart_init();
	lcd_init();
	//uart_str("CAN-BASED SECCURTIY ACESS SYSTEM/r/n");
	lcd_cmd(0x01);
	lcd_cmd(0x80);
	lcd_str("SECURITY CHECK");
	lcd_cmd(0xC0);
	lcd_str("Show Your ID");
	while(1){
		can_rx(&l1);
		if(l1.id==(var)0x111){
			//uart_str("AUTHORIZIED PERSON/r/n");
			//uart_str("WELCOME !!");
			IOSET0=no_accept_led;
			IOCLR0=accept_led;
			lcd_cmd(0x01);
			lcd_cmd(0x80);
			lcd_str("!!VERIFIED ID!!");
			lcd_cmd(0xC0);
			lcd_str("WELCOME!!");
			//delay(5000);
			IOSET0=accept_led;
		}
		else if(l1.id==(var)0x777){
			//uart_str("UNAUTHORIZIED PERSON!!/r/n");
			//uart_str("NO ENTRY!!");
			IOSET0=accept_led;
			IOCLR0=no_accept_led;
			lcd_cmd(0x01);
			lcd_cmd(0x80);
			lcd_str("ILLEGAL ENTRY!!");
			lcd_cmd(0xC0);
			lcd_str("!!ALERT!!");
			//delay(5000);
			IOSET0=no_accept_led;
		}
	}
}
			
