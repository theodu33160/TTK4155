#ifndef CAN_H
#define CAN_H

#define TRANSMISSION_ERROR_DETECTED -1
#define MESSAGE_LOST_ARBITRATION -2

#include <stdint.h>
typedef struct can_message_t{
	unsigned int id;
	uint8_t length;
	uint8_t data[8];
} can_message;

void can_init(int mode);
void can_message_send(can_message* msg) ;

void can_data_receive(can_message* msg);
int can_error();
int can_transmit_complete();

#endif
