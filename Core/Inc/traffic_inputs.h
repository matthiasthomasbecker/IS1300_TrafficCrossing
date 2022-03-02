/*
 * traffic_inputs.h
 *
 *  Created on: 2 Feb 2022
 *      Author: mabecker
 */

#ifndef INC_TRAFFIC_INPUTS_H_
#define INC_TRAFFIC_INPUTS_H_

#include "main.h"

#define TI_INPUT_COUNT 11

typedef struct {
	GPIO_TypeDef* 	gpio;
	uint16_t 		pin;
} ti_input_t;

typedef enum {
	TI_ON,
	TI_OFF
}ti_state_t;

#define CAR_WEST 			0
#define CAR_SOUTH 			1
#define CAR_EAST			2
#define CAR_NORTH			3
#define PEDESTRIAN_WEST		4
#define PEDESTRIAN_NORTH	5
#define JOYSTIC_NORTH		6
#define JOYSTIC_EAST		7
#define JOYSTIC_SOUTH		8
#define JOYSTIC_WEST		9
#define JOYSTIC_CENTER		10


void ti_init(void);
void ti_update(void);
ti_state_t ti_get_state(uint8_t _input);
void ti_get_states(ti_state_t* _dest);
ti_state_t ti_read_input(uint8_t _input);
uint32_t ti_get_poti(void);
uint8_t ti_get_poti_percent(void);
void ti_test_inputs(void);

#endif /* INC_TRAFFIC_INPUTS_H_ */
