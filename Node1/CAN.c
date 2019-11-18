#include "CAN.h"

char* USB_list_name[7] = {"BTN","left_slider","right_slider","joystick_X","joystick_Y","joystick_magnitude","joystick_angle"}; //list of the datas we send through the CAN bus
_Bool* USB_list_offset[7] = {0,0,0,1,1,0,1}; // list of the data that are sent with an offset of 128 because of the sign

void can_init(uint8_t mode)
{
	mcp2515_init(mode);  
}

void can_message_send(can_message* msg) 
{
    if (can_transmit_complete()==1)
    {
		// set message ID (standard ID)
        mcp2515_write(MCP_TXB0SIDH, (msg->id >> 3)); //the 5 first bits
        mcp2515_write(MCP_TXB0SIDL, (msg->id & 7) << 5);   //the 3 last bits
		// set data length 
		mcp2515_write(MCP_TXB0DLC, 0x0F & msg->length);

		// set data 
        for (uint8_t i = 0; i < msg->length; i++) //length is always 1 for us
        {
            mcp2515_write(MCP_TXB0D0 + i, msg->data[i]);  // TXBnDm: n = buffer number and m = data bit
		}
		//request to sent command TXBnCTRL.TXREQ
		mcp2515_request_to_send(MCP_RTS_TX0);
    }
}

uint8_t can_error()
{// check if these are error with CAN communication
    if ((mcp2515_read(MCP_TXB0CTRL) & 4) >>4)
    {
		printf("TRANSMISSION ERROR DETECTED");		
		return TRANSMISSION_ERROR_DETECTED;	
	}

    if ((mcp2515_read(MCP_TXB0CTRL) & 5) >>5)
    {
		printf("MESSAGE LOST ARBITRATION");
		return MESSAGE_LOST_ARBITRATION;	
	}
	return 0;
}

_Bool can_transmit_complete()
{//check if the last message asked to be sent is transmitted
	if (mcp2515_read((MCP_TXB0CTRL & 3) >> 3)==0)
	{
		return 1;	
	}
	else return 0;
}

void can_data_receive(can_message* msg)
{//return the last message to be read if there is one, prioritizing the
	//wait for a received message
	mcp2515_write(MCP_CANINTE, 0b1); 	//enable interrupt pin
	int canintf_reg = mcp2515_read(MCP_CANINTF);   //read status register
    if (canintf_reg & 0b1 == 1)
    {//highest priority register: RXB0
        //get message id
		int id_h = mcp2515_read(MCP_RXB0SIDH);
		int id_l = mcp2515_read(MCP_RXB0SIDL);
		msg->id = (id_h << 3) + (id_l>>5);
		
        //get message length
		msg->length = 0b1111 & mcp2515_read(MCP_RXB0DLC);
		
        //get message data
        for (uint8_t i = 0; i < msg->length; i++)
		{
			msg->data[i] = mcp2515_read(MCP_RXB0D0 + i);  // TXBnDm => n = buffer number and m = data bit
		}
		mcp2515_write(MCP_CANINTF, canintf_reg - 1); //clear the last bit in the register to say that we have read the message
	}
	
    if (canintf_reg & 0b10 == 1)
    {//lowest priority register: RXB1
        //get message id
        int id_h = mcp2515_read(MCP_RXB1SIDH);
		int id_l = mcp2515_read(MCP_RXB1SIDL);
		msg->id = (id_h << 3) + (id_l>>5);
		
        //get message length
        msg->length = 0b1111 & mcp2515_read(MCP_RXB1DLC);
		
        //get message data
        for (uint8_t i = 0; i < msg->length; i++)
		{
			msg->data[i] = mcp2515_read(MCP_RXB1D0 + i);  // TXBnDm => n = buffer number and m = data bit
		}
		mcp2515_write(MCP_CANINTF, canintf_reg - 2); //clear the last bit in the register to say that we have read the message		
	}
}

void print_message(can_message* msg)
{
    int16_t data = msg->data[0];
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

//----------------------------------------------------------------
//All the functions that send the sensors data through the CAN bus
//----------------------------------------------------------------
void CAN_send_btns()
{
    can_message message;
    message.id = ID_BTNS;
    message.length= 1;
    message.data[0] = read_buttons();
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

void CAN_send_XJoystick(uint8_t n)
{
    can_message message;
    message.id = ID_JOYSTICK_X;
    message.length= 1;
    message.data[0] = get_joystick_filtered(DIR_X, n)+128;
    can_message_send(&message);
    while(!can_transmit_complete);
	//print_message(&message);
}

void CAN_send_YJoystick(uint8_t n)
{
    can_message message;
    message.id = ID_JOYSTICK_Y;
    message.length= 1;
    message.data[0] = get_joystick_filtered(DIR_Y,n)+128;
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

void CAN_send_quit()
{
	can_message message;
    message.id = ID_QUIT;
    message.length= 1;
    message.data[0] = 0;
    can_message_send(&message);
    while(!can_transmit_complete);
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
