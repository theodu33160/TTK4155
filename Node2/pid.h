/*This file has been prepared for Doxygen automatic documentation generation.*/
/*! \file *********************************************************************
 *
 * \brief Header file for pid.c.
 *
 * - File:               pid.h
 * - Compiler:           IAR EWAAVR 4.11A
 * - Supported devices:  All AVR devices can be used.
 * - AppNote:            AVR221 - Discrete PID controller
 *
 * \author               Atmel Corporation: http://www.atmel.com \n
 *                       Support email: avr@atmel.com
 *
 * $Name: RELEASE_1_0 $
 * $Revision: 1.1 $
 * $RCSfile: pid.h,v $
 * $Date: 2006/02/16 11:46:13 $
 *****************************************************************************/

#ifndef PID_H
#define PID_H

#include "stdint.h"

#define SCALING_FACTOR 512

/*! \brief PID Status
 *
 * Setpoints and data used by the PID control algorithm
 */
typedef struct PID_DATA {
	//! Last process value, used to find derivative of process value.
	int16_t lastProcessValue;
	//! Summation of errors, used for integrate calculations
	int32_t sumError;
	//! The Proportional tuning constant, multiplied with SCALING_FACTOR
	int16_t P_Factor;
	//! The Integral tuning constant, multiplied with SCALING_FACTOR
	int16_t I_Factor;
	//! The Derivative tuning constant, multiplied with SCALING_FACTOR
	int16_t D_Factor;
	//! Maximum allowed error, avoid overflow
	int16_t maxError;
	//! Maximum allowed sumerror, avoid overflow
	int32_t maxSumError;
};

/*! \brief Maximum values
 *
 * Needed to avoid sign/overflow problems
 */
// Maximum value of variables
#define MAX_INT 127
#define MAX_SUM_ERROR 5120
//#define MAX_LONG INT32_MAX
//#define MAX_I_TERM 30*SCALING_FACTOR // (MAX_LONG / 2)

// Boolean values
#define FALSE 0
#define TRUE 1

void    pid_Init(int16_t p_factor, int16_t i_factor, int16_t d_factor, struct PID_DATA *pid);
int8_t pid_Controller(int16_t setPoint, int16_t processValue, struct PID_DATA *pid);
void    pid_Reset_Integrator(struct PID_DATA *pid_st);
//void set_PID(int16_t P,int16_t I, int16_t D, pidData_t *pid_st);
#define constrain(amt, low, high) ((amt)<(low)?(low):((amt)>(high)?(high):(amt)))
#endif