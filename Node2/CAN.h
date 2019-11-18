#ifndef CAN_H
#define CAN_H

#include <stdint.h>
#include "MCP2515.h"
#include "CAN_ID.h"

#define TRANSMISSION_ERROR_DETECTED 1
#define MESSAGE_LOST_ARBITRATION 2


typedef struct can_message_t{
    unsigned uint8_t id;
	uint8_t length;
	int data;
} can_message;

void can_init(uint8_t mode);
void can_message_send(can_message* msg) ;
void can_data_receive(can_message* msg);
uint8_t can_error();
_Bool can_transmit_complete();
void print_message(can_message* msg);

#endif
