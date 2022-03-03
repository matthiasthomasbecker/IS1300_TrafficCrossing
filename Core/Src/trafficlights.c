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

/**
 * Private variable to keep track of the current state of each light
 */
static uint8_t light_state[] = {0x00, 0x00, 0x00};

static uint8_t brightness = 0;

static uint8_t updated_lights = 0;

void tl_init() {
	hc595_init(&hspi3, 3);
	hc595_update(light_state);
	tl_brightnessUpdate();

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
	updated_lights = 1;	//indicate that at least one light has changed
}

void tl_lights_on(void) {
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

void tl_lights_off(void) {
	tl_setLight(&crossing[NORTH].street_signal->red, OFF);
	tl_setLight(&crossing[NORTH].street_signal->yellow, OFF);
	tl_setLight(&crossing[NORTH].street_signal->green, OFF);

	tl_setLight(&crossing[EAST].street_signal->red, OFF);
	tl_setLight(&crossing[EAST].street_signal->yellow, OFF);
	tl_setLight(&crossing[EAST].street_signal->green, OFF);

	tl_setLight(&crossing[SOUTH].street_signal->red, OFF);
	tl_setLight(&crossing[SOUTH].street_signal->yellow, OFF);
	tl_setLight(&crossing[SOUTH].street_signal->green, OFF);

	tl_setLight(&crossing[WEST].street_signal->red, OFF);
	tl_setLight(&crossing[WEST].street_signal->yellow, OFF);
	tl_setLight(&crossing[WEST].street_signal->green, OFF);

	tl_setLight(&crossing[WEST].pedestrian_signal->red, OFF);
	tl_setLight(&crossing[WEST].pedestrian_signal->green, OFF);
	tl_setLight(&crossing[WEST].pedestrian_signal->blue, OFF);

	tl_setLight(&crossing[NORTH].pedestrian_signal->red, OFF);
	tl_setLight(&crossing[NORTH].pedestrian_signal->green, OFF);
	tl_setLight(&crossing[NORTH].pedestrian_signal->blue, OFF);
}

/**
 * Update the LEDs.
 * Only update if one of the LED's values has changed.
 */
void tl_update(void) {
	if (updated_lights == 1) {
		hc595_update(light_state);
		updated_lights = 0;
	}
}

/**
 * Call this function to set the traffic light brightness according to the potentiometer value.
 */
void tl_brightnessControl(uint8_t _percentage) {
	brightness = _percentage;
}

void tl_brightnessUpdate(void) {
	hc595_setBrightness(brightness);
}
