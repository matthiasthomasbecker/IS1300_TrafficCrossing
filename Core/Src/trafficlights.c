/*
 * trafficlights.c
 *
 *  Created on: Feb 1, 2022
 *      Author: mabecker
 */

#include "trafficlights.h"
#include "74hc595.h"
#include "trafficlights_config.h"


extern SPI_HandleTypeDef hspi3;

extern ADC_HandleTypeDef hadc1;

/**
 * Private variable to keep track of the current state of each light
 */
static uint8_t light_state[] = {0x00, 0x00, 0x00};

void tl_init() {
	hc595_init(&hspi3, 3);
	hc595_update(light_state);
	tl_brightnessControl();

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
}

/**
 * Function turns one light on
 */
void tl_setLight(tl_light_t* _light, tl_state_t _state) {
	if (_state == OFF) {
		light_state[_light->hc595_id] &= ~(0x01 << _light->hc595_pos);
	} else {
		light_state[_light->hc595_id] = light_state[_light->hc595_id] | (0x01 << _light->hc595_pos);
	}
	hc595_update(light_state);
}

/**
 * Call this function to set the traffic light brightness according to the potentiometer value.
 */
void tl_brightnessControl(void) {
	uint32_t adcValue = 0;

	/**
	 * Get the current ADC value (0 - 4096)
	 */
	HAL_ADC_Start(&hadc1);
	HAL_ADC_PollForConversion(&hadc1,1);
	adcValue = HAL_ADC_GetValue(&hadc1);

	/**
	 * We use the range 0 - 4000. 0 Being off and 4000 being 100% on.
	 */
	hc595_setBrightness(adcValue / 40);
}
