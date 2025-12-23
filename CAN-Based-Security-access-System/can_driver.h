#include<lpc21xx.h>
#include "can_header.h"
void can_init(void){
	PINSEL1|=0x00014000;
	VPBDIV=1;
	C2MOD=0x01;
	AFMR=0x02;
	C2BTR=0x001C001D;
	C2MOD=0x00;
}
void can_tx(CAN_MSG m){
	C2TID1=m.id;
	C2TFI1=((m.dlc<<16));
	if(m.rtr==0){
		C2TFI1&=~(1<<30);
		C2TDA1=m.byteA;
		C2TDB1=m.byteB;
	}
	else{
		C2TFI1|=(1<<30);
	}
	C2CMR=(1<<0)|(1<<5);
	while((C2GSR&(1<<3))==0);
}
void can_rx(CAN_MSG *m){
	while((C2GSR & 0x01)==0);
	m->id=C2RID;
	m->dlc=(C2RFS>>16)&0x0F;
	m->rtr=(C2RFS>>30)&0x01;
	if(m->rtr==0){
		m->byteA=C2RDA;
		m->byteB=C2RDB;
	}
	C2CMR=(1<<2);
}
void uart_init(void){
	PINSEL0|=0x00000005;
	U0LCR=0x83;
	U0DLL=134;
	U0DLM=1;
	U0LCR=0x03;
}
void uart_tx(st data){
	U0THR=data;
	while((U0LSR&(1<<5))==0);
}
st uart_rx(void){
	while((U0LSR&0x01)==0);
	return U0RBR;
}
void uart_str(st *s){
	while(*s){
		uart_tx(*s++);
	}
}
		
	
			 
