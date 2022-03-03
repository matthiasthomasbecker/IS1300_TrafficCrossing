/*
 * environment.h
 *
 *  Created on: 3 Mar 2022
 *      Author: mabecker
 */

#ifndef INC_ENVIRONMENT_H_
#define INC_ENVIRONMENT_H_

#include "main.h"
#include "sht2x_for_stm32_hal.h"

typedef struct {
	float temp;
	float hum;
}env_data_t;

void env_init(void);

void env_update(void);

env_data_t* env_get_data(void);

#endif /* INC_ENVIRONMENT_H_ */
