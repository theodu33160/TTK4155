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

_Bool can_transmit_complete(){

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
	printf("canintf %d\n\r", canintf_reg);
	int status_reg = (canintf_reg); 
	if ((status_reg & 0b1)==1){  //RXB0 int
		//read message
		//id 
		int id_h = mcp2515_read(MCP_RXB0SIDH);
		int id_l = mcp2515_read(MCP_RXB0SIDL);
		msg->id = (id_h << 3) + (id_l>>5);
		
		//length
		msg->length = 0b1111 & mcp2515_read(MCP_RXB0DLC);
		
		//data
		uint8_t i;
		for (i = 0; i < msg->length; i++){
			msg->data[i] = mcp2515_read(MCP_RXB0D0 + i);  // TXBnDm => n = buffer number and m = data bit
			printf("Message received: id: %d\t", msg->id);
			printf("Length: %d\t msg: %d\n\r ", msg->length, ((int8_t) msg->data[i])*2); //We have strange values with the %d and %u for the message
			mcp2515_write(MCP_CANINTF, canintf_reg - 1); //clear the last bit in the register to say that we have read the message
		}
	}
	if (status_reg & 0b10){  //RXB1 int
		//read message
		//id 
		int id_h = mcp2515_read(MCP_RXB1SIDH);
		int id_l = mcp2515_read(MCP_RXB1SIDL);
		msg->id = (id_h << 3) + (id_l>>5);
		
		//length
		msg->length = 0b1111 & mcp2515_read(MCP_RXB1DLC);
		
		//data
		uint8_t i;
		for (i = 0; i < msg->length; i++){
			msg->data[i] = mcp2515_read(MCP_RXB1D0 + i);  // TXBnDm => n = buffer number and m = data bit
		
		printf("Message received: id: %d\t", msg->id);
		printf("Length: %d\t msg: %d\n\r ", msg->length, msg->data[i]); //We have strange values with the %d and %u for the message
		mcp2515_write(MCP_CANINTF, canintf_reg - 2); //clear the last bit in the register to say that we have read the message
		}
	}	
}
/*
can_int_vect(){
	
}*/

void saveUsbValues(can_message* msg, int* listValues)
{
	listValues[BTN_right] = msg->data[0] & 1;
	listValues[BTN_left] = msg->data[0] & 2 >>1;
	listValues[BTN_joystick] = msg->data[0] & 4 >>2;
	listValues[leftslider] = msg->data[0];
}
enum USB_list_name = {"BTN_right","BTN_left","BTN_joystick","left_slider","right_slider","joystick_X","joystick_Y","joystick_magnitude","joystick_angle"};