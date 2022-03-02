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

void demo_gui_update(ti_state_t* _inputs, uint32_t _poti_percentage);

#endif /* INC_DEMO_GUI_H_ */
