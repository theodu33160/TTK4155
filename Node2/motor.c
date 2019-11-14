#include "motor.h"

void motor_init()
{
    TWI_Master_Initialise();
    sei(); // enable interrupt for TWI communication
    //set port H as an OUTPUT
    DDRH = 0xFF;
    //Enable the motor
    PORTH |=1<<PH4;

    printf("MOTOR INIT DONE\n\r");
}

void set_speed(int8_t speed) // does speed and direction
{
    if(speed <0)
    {
        PORTH |= 1<<PH1; //set the pin DIR to 1
    }
    else
    {
        PORTH &= ~(1<<PH1); //set the pin DIR to 0
    }
    uint8_t power = (uint8_t) (abs(speed)*1);
    //printf("\tpower sent to the motor %d",power);
    char msg[3] = {0b01011110,0x00,power};
    TWI_Start_Transceiver_With_Data(msg,(unsigned char) 3);
    //printf("\terr flag HEX %x\n\r",TWI_Get_State_Info());
    /*
    if(TWI_Get_State_Info()!=1) //=1 if no error
    {
        printf("communication error with DAC\n\r");
    }*/
}