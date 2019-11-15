#include "motor.h"



void motor_init()
{
    TWI_Master_Initialise();
    sei(); // enable interrupt for TWI communication
    //set port H as an OUTPUT
    DDRH = 0xFF;
    //set port K as input
    DDRK = 0;
    //Enable the motor
    PORTH |=1<<PH4;
    //no reset
    PORTH |= 1<<PH6;
    _delay_us(60);
    PORTH &= ~(1<<PH6);
    _delay_us(60);
    PORTH |= 1<<PH6;

    printf("MOTOR INIT DONE\n\r");
}

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

int16_t motor_readEncorder()
{//according to the datasheet of the motor box
    uint8_t res_low = 0;
    int8_t res_high = 0;    
    PORTH &= ~(1<<PH5); //set !OE to LOW
    PORTH &= ~(1<<PH3); //set SEL to LOW to get high byte
    _delay_us(20);
    res_high = PINK;     
    PORTH |= (1<<PH3); //set SEL to HIGH to get high byte
    _delay_us(20);
    res_low = PINK; 
    /*PORTH &= ~(1<<PH6);
    _delay_us(200);
    PORTH |= (1<<PH6);*/
    PORTH |= (1<<PH5); //set !OE to HIGH: Desable
    return ((res_high<<8) | res_low);
}

void motor_calibrate()
{
    motor_set_speed(-50);
    _delay_ms(2000);
    motor_resetEncoder();
    motor_set_speed(0);
}
void motor_resetEncoder()
{
    //toggle reset
    PORTH &= ~(1<<PH6);
    _delay_us(20);
    PORTH |= 1<<PH6;
}