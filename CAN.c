#include "CAN.h"
#include "MCP2515.h"

struct can_message{unsigned int id;uint8_t length;uint8_t data[8];};

void can_init(int mode){
	mcp2515_init(mode);  
}



void can_message_send(can_message* msg) 
{
	
	if (can_transmit_complete()==1){
		// set message ID (standard ID)
		mcp2515_write(MCP_TXB0SIDH, (msg->id >> 3));
		mcp2515_write(MCP_TXB0SIDL, (msg->id & 7) << 5);
		// set data length 
		mcp2515_write(MCP_TXB0DLC, 0x0F & msg->length);

		// set data 
		uint8_t i;
		for (i = 0; i < msg->length; i++){
			mcp2515_write(MCP_TXB0D0 + i, msg->data[i]);  // TXBnDm => n = buffer number and m = data bit
		}
		//request to sent command TXBnCTRL.TXREQ
		mcp2515_request_to_send(MCP_RTS_TX0);
		}

}

 

int can_error(){
	if ((mcp2515_read(MCP_TXB0CTRL) & 4) >>4){
		printf("TRANSMISSION ERROR DETECTED");		
		return TRANSMISSION_ERROR_DETECTED;	
	}

	if ((mcp2515_read(MCP_TXB0CTRL) & 5) >>5){
		printf("MESSAGE LOST ARBITRATION");
		return MESSAGE_LOST_ARBITRATION;	
	}
	return 0;
		
}

int can_transmit_complete(){

	if (mcp2515_read((MCP_TXB0CTRL & 3) >> 3)==0)
	{
		return 1;	
	}
	else return 0;
}

void can_data_receive(can_message* msg){


	//wait for a received message
	mcp2515_write(MCP_CANINTE, 0b1); 	//enable interrupt pin
	int canintf_reg = mcp2515_read(MCP_CANINTF);   //read status register
	int status_reg = (canintf_reg & 0b1) >> 1; 
	if (status_reg==0){
		//read message
		//id 
		int id_h = mcp2515_read(MCP_RXB0SIDH);
		int id_l = mcp2515_read(MCP_RXB0SIDL);
		msg->id = (id_h << 3) + (id_l>>5);
		
		//length
		msg->length = 0b1111 & mcp2515_read(MCP_RXB0DLC);
		
		//data
		uint8_t data[8];
		uint8_t i;
		for (i = 0; i < msg->length; i++){
			msg->data[i] = mcp2515_read(MCP_RXB0D0 + i);  // TXBnDm => n = buffer number and m = data bit
		
		printf("id: %d ", msg->id);
		printf("length: %d ", msg->length);
		//printf("data: %d ", msg->data);
		
		}

	}
	return msg;
	
}
/*
can_int_vect(){
	
}*/

