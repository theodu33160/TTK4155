#include "CAN.h"

//struct can_message{unsigned int id;uint8_t length;uint8_t data[8];};
char* USB_list_name[7] = {"BTN","left_slider","right_slider","joystick_X","joystick_Y","joystick_magnitude","joystick_angle"};
_Bool* USB_list_offset[7] = {0,0,0,1,1,0,1 };

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

uint8_t can_error(){
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

void can_data_receive(can_message* msg)
{
	//wait for a received message
	mcp2515_write(MCP_CANINTE, 0b1); 	//enable interrupt pin
	int canintf_reg = mcp2515_read(MCP_CANINTF);   //read status register
	//printf("canintf %d\n\r", canintf_reg);
	int status_reg = (canintf_reg & 0b1);
	if (status_reg==1){
		//read message
		//id 
		int id_h = mcp2515_read(MCP_RXB0SIDH);
		int id_l = mcp2515_read(MCP_RXB0SIDL);
		msg->id = (id_h << 3) + (id_l>>5);
		
		//length
		msg->length = 0b1111 & mcp2515_read(MCP_RXB0DLC);
		
		//data
		uint8_t i;
		for (i = 0; i < msg->length; i++)
		{
			msg->data[i] = mcp2515_read(MCP_RXB0D0 + i);  // TXBnDm => n = buffer number and m = data bit
		}
		print_message(msg);
		mcp2515_write(MCP_CANINTF, canintf_reg - 1); //clear the last bit in the register to say that we have read the message
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
		for (i = 0; i < msg->length; i++)
		{
			msg->data[i] = mcp2515_read(MCP_RXB1D0 + i);  // TXBnDm => n = buffer number and m = data bit
		}
		print_message(msg);
		mcp2515_write(MCP_CANINTF, canintf_reg - 2); //clear the last bit in the register to say that we have read the message
		
	}
}
/*
can_int_vect(){
	
}*/

void CAN_send_btns()
{
    can_message message;
    message.id = ID_BTNS;
    message.length= 1;
    message.data[0] = read_button(BTN_RIGHT)+read_button(BTN_LEFT)<<1+read_button(BTN_JOYSTICK)<<2;
    can_message_send(&message);
    while(!can_transmit_complete);
}

void CAN_send_left_slider()
{
    can_message message;
    message.id = ID_LEFT_SLIDER;
    message.length= 1;
    message.data[0] = get_leftSlider();
    can_message_send(&message);
    while(!can_transmit_complete);
}

void CAN_send_right_slider()
{
    can_message message;
    message.id = ID_RIGHT_SLIDER;
    message.length= 1;
    message.data[0] = get_rightSlider();
    can_message_send(&message);
    while(!can_transmit_complete);
}

void CAN_send_XJoystick()
{
    can_message message;
    message.id = ID_JOYSTICK_X;
    message.length= 1;
    message.data[0] = get_joystick(DIR_X)+128;
	//printf("x joystick = %d\t", get_joystick(DIR_X));
    can_message_send(&message);
    while(!can_transmit_complete);
	//print_message(&message);
}

void CAN_send_YJoystick()
{
    can_message message;
    message.id = ID_JOYSTICK_Y;
    message.length= 1;
    message.data[0] = get_joystick(DIR_Y)+128;
    can_message_send(&message);
    while(!can_transmit_complete);
}

void CAN_send_magintudeJoystick()
{
    can_message message;
    message.id = ID_JOYSTICK_MAGNITUDE;
    message.length= 1;
    message.data[0] = get_magnitude();
    can_message_send(&message);
    while(!can_transmit_complete);
}

void CAN_send_joystick_angle()
{
   	uint8_t angleJTCK = get_angle()/2+128;
    can_message message;
    message.id = ID_JOYSTICK_ANGLE;
    message.length= 1;
    message.data[0] = angleJTCK;
    can_message_send(&message);
    while(!can_transmit_complete);
	print_message(&message);
//    printf("message sent: %s\t",message.data);
  //  printf("CANINTF register:%x\t", mcp2515_read(MCP_CANINTF));
    //printf("EFLG register:%x\n\r", mcp2515_read(MCP_EFLG));
}

void print_message(can_message* msg)
{
	int data = msg->data[0];
	printf("Message received: id %d", msg->id);
	if (msg->id >=100 && msg->id<=106)
	{
		printf("%s",USB_list_name[msg->id-100]);
		data = data - 128* (int)USB_list_offset[msg->id-100];
	}
	if (msg->id == ID_JOYSTICK_ANGLE) // be carefull to put the multiplication by two after reøoving the offset
	{
		data = data *2;
	}
	printf("Length: %d\t msg: %d\n\r ", msg->length,  data); //We have strange values with the %d and %u for the message	
}