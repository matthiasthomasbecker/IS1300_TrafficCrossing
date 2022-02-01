/*
 * trafficlights.c
 *
 *  Created on: Feb 1, 2022
 *      Author: mabecker
 */

#include "trafficlights.h"
#include "74hc595.h"
#include "trafficlights_config.h"


extern SPI_HandleTypeDef hspi2;



/**
 * Private variable to keep track of the current state of each light
 */
static uint8_t light_state[] = {0x00, 0x00, 0x00};

void tl_init() {
	hc595_init(&hspi2, 3);
	hc595_update(light_state);
	hc595_enable();

	tl_setLight(&crossing[NORTH].street_signal->red, ON);
	tl_setLight(&crossing[NORTH].street_signal->yellow, ON);
	tl_setLight(&crossing[NORTH].street_signal->green, ON);

	tl_setLight(&crossing[EAST].street_signal->red, ON);
	tl_setLight(&crossing[EAST].street_signal->yellow, ON);
	tl_setLight(&crossing[EAST].street_signal->green, ON);

	tl_setLight(&crossing[SOUTH].street_signal->red, ON);
	tl_setLight(&crossing[SOUTH].street_signal->yellow, ON);
	tl_setLight(&crossing[SOUTH].street_signal->green, ON);

	tl_setLight(&crossing[WEST].street_signal->red, ON);
	tl_setLight(&crossing[WEST].street_signal->yellow, ON);
	tl_setLight(&crossing[WEST].street_signal->green, ON);

	tl_setLight(&crossing[WEST].pedestrian_signal->red, ON);
	tl_setLight(&crossing[WEST].pedestrian_signal->green, ON);
	tl_setLight(&crossing[WEST].pedestrian_signal->blue, ON);

	tl_setLight(&crossing[NORTH].pedestrian_signal->red, ON);
	tl_setLight(&crossing[NORTH].pedestrian_signal->green, ON);
	tl_setLight(&crossing[NORTH].pedestrian_signal->blue, ON);

	HAL_Delay(500);
	hc595_setBrightness(50);
	HAL_Delay(500);
	hc595_setBrightness(10);
}

void tl_setLight(tl_light_t* _light, tl_state_t _state) {
	if (_state == OFF) {
		light_state[_light->hc595_id] &= ~(0x01 << _light->hc595_pos);
	} else {
		light_state[_light->hc595_id] = light_state[_light->hc595_id] | (0x01 << _light->hc595_pos);
	}
	hc595_update(light_state);
}