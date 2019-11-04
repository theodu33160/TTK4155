#ifndef CAN_H
#define CAN_H

#include <stdint.h>
#include "usbCard.h"
#include "MCP2515.h"
#include "CAN_ID.h"

#define TRANSMISSION_ERROR_DETECTED -1
#define MESSAGE_LOST_ARBITRATION -2


typedef struct can_message_t{
	unsigned int id;
	uint8_t length;
	uint8_t data[8];
} can_message;

void can_init(int mode);
void can_message_send(can_message* msg) ;

void can_data_receive(can_message* msg);
uint8_t can_error();
_Bool can_transmit_complete();
void print_message(can_message* msg);

//transmission of data functions

void CAN_send_btns();
void CAN_send_left_slider();
void CAN_send_right_slider();
void CAN_send_XJoystick();
void CAN_send_YJoystick();
void CAN_send_magintudeJoystick();
void CAN_send_joystick_angle();

#endif
