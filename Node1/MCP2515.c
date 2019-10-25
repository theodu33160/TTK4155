#include "MCP2515.h"

uint8_t mcp2515_init(mode){

	uint8_t value;
	SPI_MasterInit(); // Initialize

	mcp2515_reset(); // Send reset-command
	
	mcp2515_write(MCP_CANCTRL, mode);
	
	// Self-test
	_delay_us(100);
	value = mcp2515_read(MCP_CANSTAT); //, &value
	if((value & MODE_MASK)  != mode) { //value&
		printf("MCP2515 is NOT in the chosen mode after reset\n\r");
		return 1;
	}
	// More initialization
	else printf("Good config\n\r");
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
void mcp2515_request_to_send(uint8_t RTS_command){ //MCP_RTS_ALL or  MCP_RTS_TX0 or  1 or 2
	PORTB &= ~(1<<CAN_CS); // SelectCAN-controller
	SPI_write(RTS_command); // Send RTS command byte instruction
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
	SPI_write(MCP_RESET); // Send reset command byte instruction
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
