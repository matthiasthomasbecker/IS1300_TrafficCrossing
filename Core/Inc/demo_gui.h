/*
 * demo_gui.h
 *
 *  Created on: Mar 2, 2022
 *      Author: mabecker
 */

#ifndef INC_DEMO_GUI_H_
#define INC_DEMO_GUI_H_

#include "main.h"
#include "ssd1306.h"
#include "traffic_inputs.h"
#include "trafficlights.h"
#include "environment.h"

#define DATA_SIZE 120

typedef struct {
	uint8_t data[DATA_SIZE];
	uint8_t pos;
}demo_graph_t;

void demo_gui_update(ti_state_t* _inputs, uint32_t _poti_percentage, int16_t* acceleration, env_data_t* env);

#endif /* INC_DEMO_GUI_H_ */
