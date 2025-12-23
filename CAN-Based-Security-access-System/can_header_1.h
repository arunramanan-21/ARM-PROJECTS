#ifndef CAN_HEADER_H
#define CAN_HEADER_H
typedef unsigned char st;
typedef unsigned int var;
typedef struct CAN{
	var id;
	var rtr;
	var dlc;
	var byteA;
	var byteB;
}CAN_MSG;
void can_init(void);
void can_tx(CAN_MSG);
void can_rx(CAN_MSG *);
void uart_init(void);
void uart_tx(st);
st uart_rx(void);
void uart_str(st *);
void delay(int);
#endif
