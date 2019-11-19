#include "motor.h"

// Function to initialize the motor_box so that the motor works correctly
void motor_init()
{
    TWI_Master_Initialise();
    sei(); // enable interrupt for TWI communication
    DDRH = 0xFF; //set port H as an OUTPUT
    DDRK = 0;  //set port K as input
    PORTH |=1<<PH4; //Enable the motor
    //no reset
    PORTH |= 1<<PH6;
    _delay_us(60);
    PORTH &= ~(1<<PH6);
    _delay_us(60);
    PORTH |= 1<<PH6;
    printf("Motor Init Done.\n\r");
}

//Function implemented to change the speed of the motor by request
void motor_set_speed(int8_t speed) // does speed and direction
{
    if(speed <0)
    {
        PORTH |= 1<<PH1; //set the pin DIR to 1
    }
    else
    {
        PORTH &= ~(1<<PH1); //set the pin DIR to 0
    }
    uint8_t power = (uint8_t) (abs(speed)*2);
    char msg[3] = {0b01011110,0x00,power};
    TWI_Start_Transceiver_With_Data(msg,(unsigned char) 3);
}

// Function to read the position of the motor from the encoder.
int16_t motor_readEncorder()
{
    //according to the datasheet of the motor box
    uint8_t res_low = 0;
    int8_t res_high = 0;
    PORTH &= ~(1<<PH5); //set !OE to LOW
    PORTH &= ~(1<<PH3); //set SEL to LOW to get high byte
    _delay_us(20);
    res_high = PINK;
    PORTH |= (1<<PH3); //set SEL to HIGH to get high byte
    _delay_us(20);
    res_low = PINK;
    PORTH |= (1<<PH5); //set !OE to HIGH: Desable
    return ((res_high<<8) | res_low);
}

//Function to calibrate the motor position in the start.
//We move the motor to the leftmost corner, and reset the position.
void motor_calibrate()
{
    motor_set_speed(-50);
    _delay_ms(2000);
    motor_resetEncoder();
    motor_set_speed(0);
}

//We toggle PH6 to reset the values in the encoder.
void motor_resetEncoder()
{
    //toggle reset
    PORTH &= ~(1<<PH6);
    _delay_us(20);
    PORTH |= 1<<PH6;
}
