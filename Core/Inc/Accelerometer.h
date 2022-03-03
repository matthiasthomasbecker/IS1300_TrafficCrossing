/*
 * Accelerometer.h
 *
 *  Created on: 3 Mar 2022
 *      Author: mabecker
 */

#ifndef INC_ACCELEROMETER_H_
#define INC_ACCELEROMETER_H_

#include "main.h"
#include "lis2dw12_reg.h"

void acc_init(void);
void acc_update(void);
int16_t* acc_get_acceleration(void);
int16_t acc_get_acceleration_x(void);
int16_t acc_get_acceleration_y(void);
int16_t acc_get_acceleration_z(void);

#endif /* INC_ACCELEROMETER_H_ */
