#include<lpc21xx.h>
#include "mini_lcd.h"
#include "mini_i2c.h"
#define RESET 1<<0
#define LDR 1<<16
#define ST_LIGHT 1<<17
#define CAR_DET 1<<18
int flag=1;
unsigned int count=0;
int main(){
	IODIR0|=ST_LIGHT;
	IOSET0=ST_LIGHT;
	LCD_INIT();
	LCD_CMD(0x01);
	LCD_CMD(0x80);
	LCD_STRING("SMART LIGHT AND");
	LCD_CMD(0xC0);
	LCD_STRING("TRAFFIC DATA LOGGER");
	//LCD_STRING("VEHICLE COUNT:");
	
	i2c_init();
	count=i2c_eeprom_read(0x50,0x00);
	while(1){
		//LCD_CMD(0xC0);
		//LCD_INTEGER(count);
		if((IOPIN0&CAR_DET)==0){
			if(flag==1){
				count++;
				delay(300);
				LCD_CMD(0x01);
				LCD_CMD(0x80);
				LCD_STRING("VEHICLE COUNT:");
				LCD_CMD(0xC0);
				LCD_INTEGER(count);
				i2c_eeprom_write(0x50,0x00,count);
				flag=0;
			}
		}
		else
			flag=1;
		if((IOPIN0&RESET)==0){
			count=0;
			LCD_CMD(0x01);
			LCD_CMD(0x80);
			LCD_STRING("VEHICLE COUNT:");
			LCD_CMD(0xC0);
			LCD_INTEGER(count);
			i2c_eeprom_write(0x50,0x00,count);
		}
		if((IOPIN0&LDR)==0)
			IOSET0=ST_LIGHT;
		else
			IOCLR0=ST_LIGHT;

	}
}

