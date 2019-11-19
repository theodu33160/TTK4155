#include "pid.h"


//initialisation of the pid
void pid_Init(int16_t p_factor, int16_t i_factor, int16_t d_factor, struct PID_DATA *pid)
{
	// Start values for PID controller
	pid->sumError         = 0;
	pid->lastProcessValue = 0;
	pid->P_Factor = p_factor;
	pid->I_Factor = i_factor;
	pid->D_Factor = d_factor;
	
	printf("\n\rPID INIT DONE");
}



int8_t pid_Controller(int16_t setPoint, int16_t processValue, struct PID_DATA *pid)
{
	int16_t error = setPoint - processValue;
	pid->sumError = constrain(pid->sumError + pid->I_Factor*error, -MAX_SUM_ERROR,MAX_SUM_ERROR);

	int8_t ret = (int8_t) ((pid->P_Factor * error + pid->sumError) /SCALING_FACTOR); //the shift is a scaling factor
	
	//constrain the output value to be acceptable by the DAC:
	ret=constrain(ret,-MAX_INT,MAX_INT);
	printf("\n\r encoder %d\t error %d\t sumError %d\t ouput PID %d\t",processValue, error,(int16_t) (pid->sumError/SCALING_FACTOR),(int8_t) (ret));
	return (int8_t) (ret);
}