#ifndef PID_H
#define PID_H

#include "stdint.h"

#define SCALING_FACTOR 512

typedef struct PID_DATA {
	int16_t lastProcessValue;
	int32_t sumError;
	int16_t P_Factor; // proportional tuning constant
	int16_t I_Factor; // integral tuning constant
	int16_t D_Factor; //derivative tuning constant


#define MAX_INT 127
#define MAX_SUM_ERROR 5120


void pid_Init(int16_t p_factor, int16_t i_factor, int16_t d_factor, struct PID_DATA *pid);
int8_t pid_Controller(int16_t setPoint, int16_t processValue, struct PID_DATA *pid);

#define constrain(amt, low, high) ((amt)<(low)?(low):((amt)>(high)?(high):(amt)))

#endif
