/*
 * trafficlights.h
 *
 *  Created on: Feb 1, 2022
 *      Author: mabecker
 */

#ifndef INC_TRAFFICLIGHTS_H_
#define INC_TRAFFICLIGHTS_H_

#include "main.h"

/**
 * Describes the different directions that are possible
 */
typedef enum {
		NORTH = 0,
		SOUTH = 1,
		WEST = 2,
		EAST = 3
} tl_direction_t;

/**
 * Describes the possible states of a light
 */
typedef enum  {
	ON,
	OFF
} tl_state_t;

/**
 * This type describes a single light
 */
typedef struct tl_light {
	uint8_t hc595_id;
	uint8_t hc595_pos;
}tl_light_t;

/**
 * This type describes a car signal
 */
typedef struct tl_car_signal{
	tl_light_t red;
	tl_light_t yellow;
	tl_light_t green;
}tl_car_signal_t;

/**
 * This type describes a pedestrian signal
 */
typedef struct tl_pedestrian_signal{
	tl_light_t red;
	tl_light_t green;
	tl_light_t blue;
}tl_pedestrian_signal_t;


/**
 * This type describes all lights available in one direction of the road that meets
 * at the crossing.
 */
typedef struct tl_street {
	tl_state_t				direction;			//direction of the street
	tl_car_signal_t* 		street_signal;		//pointer to the street signal
	tl_pedestrian_signal_t* pedestrian_signal;	//pointer to the pedestrian signal
}tl_street_t;




void tl_init();

void tl_setLight(tl_light_t* _light, tl_state_t _state);

void tl_brightnessControl(uint8_t _percentage);

void tl_brightnessUpdate(void);
void tl_update(void);

#endif /* INC_TRAFFICLIGHTS_H_ */
