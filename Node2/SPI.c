#include "SPI.h"

void SPI_Init(){

	SPI_MasterInit();
	//SPI_SlaveInit();

}


void SPI_MasterInit(void){
	

	/* Set MOSI and SCK output, all others input */
	DDR_SPI |= (1<<DD_MOSI)|(1<<DD_SCK)|(1<<CAN_CS)|(1<<PB0);
	DDR_SPI &= ~(1<<DD_MISO);
	/* Enable SPI, Master, set clock rate fck/16 */
	SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);
	// For security
	//SPCR = (0<<SPR1);
	//SPSR = (0<<SPI2X);
	
}



void SPI_write(char cData){
	/* Start transmission */
	SPDR = cData;

	/* Wait for transmission complete */
	while(!(SPSR & (1<<SPIF)));	
}




void SPI_SlaveInit(void){

	/* Set MISO output, all others input */
	DDR_SPI = (1<<DD_MISO);

	/* Enable SPI */
	SPCR = (1<<SPE);
}


char SPI_read(void){
	
	SPDR = 0xFF;
	/* Wait for reception complete */
	while(!(SPSR & (1<<SPIF)));

	/* Return data register */
	return SPDR;
}
