#include "MCP2515.h"

uint8_t mcp2515_init(){

	uint8_t value;
	SPI_init(); // Initialize

	SPImcp2515_reset(); // Send reset-command

	// Self-test
	mcp2515_read(MCP_CANSTAT, &value);
	if((value& MODE_MASK)  != MODE_CONFIG) {
		printf(”MCP2515 is NOT in configurationmode afterreset!\n”);
		return1;
	}
	// More initialization
	return0;
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
	PORTB &= ~(1<<CAN_CS); // SelectCAN-controller
	printf("flag 1");
	SPI_write(MCP_RESET); // Send reset command byte instruction
	printf("flag 2");
	PORTB |= (1<<CAN_CS); // DeselectCAN-controller

}

uint8_t mcp2515_read_status(){
	uint8_t result;
	PORTB &= ~(1<<CAN_CS); // SelectCAN-controller
	SPI_write(MCP_READ_STATUS); // Send read status command byte instruction
	result= SPI_read(); // Readresult
	PORTB |= (1<<CAN_CS); // DeselectCAN-controller
	return result;
}


