#include "SPI.h"
#include <avr/io.h>

void SPI_Init(){

	SPI_MasterInit();
	SPI_SlaveInit();

}


void SPI_MasterInit(void){

	/* Set MOSI and SCK output, all others input */
	DDR_SPI = (1<<DD_MOSI)|(1<<DD_SCK);
	/* Enable SPI, Master, set clock rate fck/16 */
	SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);

}



void SPI_write(char cData){
	printf("enter write\n");
	/* Start transmission */
	SPDR = cData;

	/* Wait for transmission complete */
	while(!(SPSR & (1<<SPIF)));
	printf("fin\n");
}




void SPI_SlaveInit(void){

	/* Set MISO output, all others input */
	DDR_SPI = (1<<DD_MISO);

	/* Enable SPI */
	SPCR = (1<<SPE);
}


char SPI_read(void){

	/* Wait for reception complete */
	while(!(SPSR & (1<<SPIF)));

	/* Return data register */
	return SPDR;
}
