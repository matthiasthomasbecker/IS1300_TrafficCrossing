/*
 * environment.c
 *
 *  Created on: 3 Mar 2022
 *      Author: mabecker
 */

#include "environment.h"

extern I2C_HandleTypeDef hi2c3;

env_data_t data;

void env_init(void) {
	SHT2x_Init(&hi2c3);
	//SHT2x_SoftReset();
	SHT2x_SetResolution(RES_14_12);
}

void env_update(void) {
	data.temp = SHT2x_GetTemperature(1);
	data.hum = SHT2x_GetRelativeHumidity(1);
}

env_data_t* env_get_data(void) {
	return &data;
}
