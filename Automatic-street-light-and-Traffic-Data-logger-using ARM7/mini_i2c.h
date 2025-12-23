#include<lpc21xx.h>
//#inlcude "i2c_define.h"
//i2c wires
#define SCL 0x00000010
#define SDA 0x00000040
//led pins
//#define LED1 1<<17
//#define LED2 1<<18
//speed configuration
#define CCLK 60000000
#define PCLK (CCLK/4)
#define I2CSPEED 100000
#define RATE ((PCLK/I2CSPEED)/2)
//I2CONSET reg pins
#define AA 2
#define SI 3
#define STO 4
#define STA 5
#define I2EN 6
typedef unsigned char u8;
void delay(int);
void i2c_init(void);
void i2c_eeprom_write(u8,u8,u8);
u8 i2c_eeprom_read(u8,u8);
void i2c_start(void);
void i2c_write(u8);
void i2c_stop(void);
void i2c_restart(void);
u8 i2c_noack(void);
void i2c_init(void){
	PINSEL0|=SCL|SDA;
	I2SCLL=RATE;
	I2SCLH=RATE;
	I2CONSET=1<<I2EN;
}
void i2c_eeprom_write(u8 slav_addr,u8 wbuffaddr,u8 d){
	i2c_start();
	i2c_write(slav_addr<<1);
	i2c_write(wbuffaddr);
	i2c_write(d);
	i2c_stop();
	delay(10);
}
u8 i2c_eeprom_read(u8 slav_addr,u8 rbuffaddr){
	u8 data;
	i2c_start();
	i2c_write(slav_addr<<1);
	i2c_write(rbuffaddr);
	i2c_restart();
	i2c_write(slav_addr<<1|1);
	data=i2c_noack();
	i2c_stop();
	return data;
}
void i2c_start(void){
	I2CONSET=1<<STA;
	while(((I2CONSET>>SI)&1)==0);
	I2CONCLR=1<<STA;
}
void i2c_write(u8 byte){
	I2DAT=byte;
	I2CONCLR=1<<SI;
	while(((I2CONSET>>SI)&1)==0);
}
void i2c_stop(void){
	I2CONSET=1<<STO;
	I2CONCLR=1<<SI;
}
void i2c_restart(void){
	I2CONSET=1<<STA;
	I2CONCLR=1<<SI;
	while(((I2CONSET>>SI)&1)==0);
	I2CONCLR=1<<STA;
}
u8 i2c_noack(void){
	I2CONCLR=1<<AA;
	I2CONCLR=1<<SI;
	while(((I2CONSET>>SI)&1)==0);
	return I2DAT;
}
