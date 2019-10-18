#include "MCP2515.h"
#include "SPI.h"
#include <avr/io.h>

uint8_t mcp2515_init(){

	uint8_t value;
	SPI_Init(); // Initialize
	printf("SPI init done\n");
	mcp2515_reset(); // Send reset-command
	printf("SPI reset done\n");
	// Self-test
	value = mcp2515_read(MCP_CANSTAT); //, &value
	if((value & MODE_MASK)  != MODE_LOOPBACK) { //value&
		printf("MCP2515 is NOT in configurationmode afterreset\n");
		return 1;
	}
	// More initialization
	//Setting mode to loopback mode 17/10/2019
	//CANCTRL=(6<<REQOP0); //Setting the 6th bit of the REQOP0 register to
	return 0;
}

uint8_t mcp2515_read(uint8_t address){
	uint8_t result;
	PORTB &= ~(1<<CAN_CS); // SelectCAN-controller
	SPI_write(MCP_READ); // Send read instruction
	SPI_write(address); // Send address
	result= SPI_read(); // Readresult
	PORTB |= (1<<CAN_CS); // DeselectCAN-controller
	return result;
}

void mcp2515_write(uint8_t address, uint8_t data){
	PORTB &= ~(1<<CAN_CS); // SelectCAN-controller
	SPI_write(MCP_WRITE); // Send write instruction
	SPI_write(address); // Send address
	SPI_write(data); // Send at least one byte of data
	PORTB |= (1<<CAN_CS); // DeselectCAN-controller

}
// ATTENTION
void mcp2515_request_to_send(){
	PORTB &= ~(1<<CAN_CS); // SelectCAN-controller
	SPI_write(MCP_RTS_ALL); // Send RTS command byte instruction
	PORTB |= (1<<CAN_CS); // DeselectCAN-controller
}

void mcp2515_bit_modify(uint8_t address,uint8_t mask,uint8_t data){
	PORTB &= ~(1<<CAN_CS); // SelectCAN-controller
	SPI_write(MCP_BITMOD); // Send bit modify instruction
	SPI_write(address); // Send register address
	SPI_write(mask); // Send mask byte : 1 allows a bit in the register to change while a 0 don't
	SPI_write(data); // Send at least one byte of data: a 1 in the mask will set the bit, 0 will clear it

}

void mcp2515_reset(){
	printf("enter\n");
 PORTB &= ~(1<<CAN_CS); // SelectCAN-controller
 printf("selected\n");
	SPI_write(MCP_RESET); // Send reset command byte instruction
	printf("written\n");
	PORTB |= (1<<CAN_CS); // DeselectCAN-controller
	printf("deselected\n");

}

uint8_t mcp2515_read_status(){
	uint8_t result;
	PORTB &= ~(1<<CAN_CS); // SelectCAN-controller
	SPI_write(MCP_READ_STATUS); // Send read status command byte instruction
	result= SPI_read(); // Readresult
	PORTB |= (1<<CAN_CS); // DeselectCAN-controller
	return result;
}
