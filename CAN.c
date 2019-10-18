#include "CAN.h"

struct can_message{unsigned int id;uint8_t length;uint8_t data[8];};

can_init(mode){
	mcp2515_init(mode);  
}

struct can_message{
	unsigned int id;
	uint8_t length;
	uint8_t data[8];
};

void can_message_send(struct can_message* msg) 
{
	// set message ID (standard ID)
	mcp2515_write(TXB1SIDH, (msg->id >> 3);
	mcp2515_write(TXB1SIDL, (msg->id & 7) << 6);

	// set data length 
	mcp2515_write(TXB1DLC, 0x0F & msg->length);

	// set data 
	uint8_t i;
	for (i = 0; i < msg->length; i++){
		mcp2515_write(TXB1D0 + i, data[i]);  // TXBnDm => n = buffer number and m = data bit
	}
	//request to sent command TXBnCTRL.TXREQ
	mcp2515_request_to_send(MCP_RTS_TX1):
	
}

can_error(){
	
}

can_transmit_complete(){
}

can_data_receive(){
	//wait for a received message
	mcp2515_write(CANINTE, 0b10); 	//enable interrupt pin
	canintf_reg = mcp2515_read(CANINTF);   //read status register
	status_reg = (canintf_reg & 0b10) >> 1; 
	if (status_reg){
		//read message
		id_h = read(RXB0SIDH);

	}
	
}

can_int_vect(){
}

