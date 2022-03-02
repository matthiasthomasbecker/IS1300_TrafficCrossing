/*
 * traffic_inputs.c
 *
 *  Created on: 2 Feb 2022
 *      Author: mabecker
 */

#include "traffic_inputs.h"
#include <stdio.h>
#include <string.h>

/**
 * Current state of the input
 */
ti_state_t state[TI_INPUT_COUNT];

ti_input_t inputs[] = {
	{
		TL1_Car_GPIO_Port,
		TL1_Car_Pin
	},{
		TL2_Car_GPIO_Port,
		TL2_Car_Pin
	},{
		TL3_Car_GPIO_Port,
		TL3_Car_Pin
	},{
		TL4_Car_GPIO_Port,
		TL4_Car_Pin
	},{
		PL1_Switch_GPIO_Port,
		PL1_Switch_Pin
	},{
		PL2_Switch_GPIO_Port,
		PL2_Switch_Pin
	},{
		Button3_A_GPIO_Port,
		Button3_A_Pin
	},{
		Button3_B_GPIO_Port,
		Button3_B_Pin
	},{
		Button3_C_GPIO_Port,
		Button3_C_Pin
	},{
		Button3_D_GPIO_Port,
		Button3_D_Pin
	},{
		Button3_Center_GPIO_Port,
		Button3_Center_Pin
	}
};

void ti_init(void) {
	ti_update();
}

void ti_update(void) {
	for (int i = 0; i < TI_INPUT_COUNT; i++) {
		state[i] = ti_read_input(i);
	}
}

ti_state_t ti_get_state(uint8_t _input) {
	return state[_input];
}

void ti_get_states(ti_state_t* _dest) {
	memcpy(_dest, state, sizeof(state));
}

ti_state_t ti_read_input(uint8_t _input) {
	if ( HAL_GPIO_ReadPin(inputs[_input].gpio, inputs[_input].pin) == GPIO_PIN_SET) {
		return TI_ON;
	} else return TI_OFF;
}

void ti_test_inputs(void) {
	if (ti_read_input(CAR_WEST) == TI_ON) printf("CAR_WEST = ON\r\n");
	else printf("CAR_WEST = off\r\n");

	if (ti_read_input(CAR_SOUTH) == TI_ON) printf("CAR_SOUTH = ON\r\n");
		else printf("CAR_SOUTH = off\r\n");

	if (ti_read_input(CAR_EAST) == TI_ON) printf("CAR_EAST = ON\r\n");
		else printf("CAR_EAST = off\r\n");

	if (ti_read_input(CAR_NORTH) == TI_ON) printf("CAR_NORTH = ON\r\n");
		else printf("CAR_NORTH = off\r\n");

	if (ti_read_input(PEDESTRIAN_WEST) == TI_ON) printf("PEDESTRIAN_WEST = ON\r\n");
		else printf("PEDESTRIAN_WEST = off\r\n");

	if (ti_read_input(PEDESTRIAN_NORTH) == TI_ON) printf("PEDESTRIAN_NORTH = ON\r\n");
		else printf("PEDESTRIAN_NORTH = off\r\n");

	if (ti_read_input(JOYSTIC_NORTH) == TI_ON) printf("JOYSTIC_NORTH = ON\r\n");
			else printf("JOYSTIC_NORTH = off\r\n");

	if (ti_read_input(JOYSTIC_SOUTH) == TI_ON) printf("JOYSTIC_SOUTH = ON\r\n");
			else printf("JOYSTIC_SOUTH = off\r\n");

	if (ti_read_input(JOYSTIC_EAST) == TI_ON) printf("JOYSTIC_EAST = ON\r\n");
			else printf("JOYSTIC_EAST = off\r\n");

	if (ti_read_input(JOYSTIC_WEST) == TI_ON) printf("JOYSTIC_WEST = ON\r\n");
			else printf("JOYSTIC_WEST = off\r\n");

	if (ti_read_input(JOYSTIC_CENTER) == TI_ON) printf("JOYSTIC_CENTER = ON\r\n");
			else printf("JOYSTIC_CENTER = off\r\n");
}
