/*
 * demo_gui.c
 *
 *  Created on: Mar 2, 2022
 *      Author: mabecker
 */

#include "demo_gui.h"
#include "stdio.h"

#define ROW_HEIGHT 12

#define RIGHT_BLOCK 48
#define LEFT_BLOCK 0
#define DATA_LEFT_BLOCK  (LEFT_BLOCK + 38)
#define DATA_RIGHT_BLOCK (DATA_LEFT_BLOCK + RIGHT_BLOCK)

#define MAX_VIEW 2;

void demo_gui_view_1(ti_state_t* _inputs, uint32_t _poti_percentage);
void demo_gui_view_2(ti_state_t* _inputs, uint32_t _poti_percentage);

uint32_t activeView = 0;

ti_state_t button_old;

void demo_gui_update(ti_state_t* _inputs, uint32_t _poti_percentage) {
	ssd1306_Fill(Black);

	if (button_old != _inputs[JOYSTIC_CENTER]) {
		button_old = _inputs[JOYSTIC_CENTER];

		if (button_old == TI_OFF) {
			activeView++;
			activeView = activeView % MAX_VIEW;
		}
	}

	if (activeView == 0) demo_gui_view_1(_inputs, _poti_percentage);
	else if (activeView == 1) demo_gui_view_2(_inputs, _poti_percentage);
}

void demo_gui_view_1(ti_state_t* _inputs, uint32_t _poti_percentage) {
	//Block 1
		ssd1306_SetCursor(LEFT_BLOCK, 0);
		ssd1306_WriteString("CAR-N", Font_7x10, White);
		ssd1306_SetCursor(LEFT_BLOCK, ROW_HEIGHT);
		ssd1306_WriteString("CAR-W", Font_7x10, White);
		ssd1306_SetCursor(LEFT_BLOCK, ROW_HEIGHT * 2);
		ssd1306_WriteString("CAR-S", Font_7x10, White);
		ssd1306_SetCursor(LEFT_BLOCK, ROW_HEIGHT * 3);
		ssd1306_WriteString("CAR-E", Font_7x10, White);
		ssd1306_SetCursor(LEFT_BLOCK, ROW_HEIGHT * 4);
		ssd1306_WriteString("TL-N", Font_7x10, White);

		ssd1306_SetCursor(DATA_LEFT_BLOCK, 0);
		if (_inputs[CAR_NORTH] == TI_ON) ssd1306_WriteString("1", Font_7x10, White);
		else ssd1306_WriteString("0", Font_7x10, White);

		ssd1306_SetCursor(DATA_LEFT_BLOCK, ROW_HEIGHT);
		if (_inputs[CAR_WEST] == TI_ON) ssd1306_WriteString("1", Font_7x10, White);
		else ssd1306_WriteString("0", Font_7x10, White);

		ssd1306_SetCursor(DATA_LEFT_BLOCK, ROW_HEIGHT * 2);
		if (_inputs[CAR_SOUTH] == TI_ON) ssd1306_WriteString("1", Font_7x10, White);
		else ssd1306_WriteString("0", Font_7x10, White);

		ssd1306_SetCursor(DATA_LEFT_BLOCK, ROW_HEIGHT * 3);
		if (_inputs[CAR_EAST] == TI_ON) ssd1306_WriteString("1", Font_7x10, White);
		else ssd1306_WriteString("0", Font_7x10, White);

		ssd1306_SetCursor(DATA_LEFT_BLOCK, ROW_HEIGHT * 4);
		if (_inputs[PEDESTRIAN_NORTH] == TI_ON) ssd1306_WriteString("1", Font_7x10, White);
		else ssd1306_WriteString("0", Font_7x10, White);

		//Block 2
		ssd1306_SetCursor(RIGHT_BLOCK, 0);
		ssd1306_WriteString("UP", Font_7x10, White);
		ssd1306_SetCursor(RIGHT_BLOCK, ROW_HEIGHT);
		ssd1306_WriteString("DOWN", Font_7x10, White);
		ssd1306_SetCursor(RIGHT_BLOCK, ROW_HEIGHT * 2);
		ssd1306_WriteString("LEFT", Font_7x10, White);
		ssd1306_SetCursor(RIGHT_BLOCK, ROW_HEIGHT * 3);
		ssd1306_WriteString("RIGHT", Font_7x10, White);
		ssd1306_SetCursor(RIGHT_BLOCK, ROW_HEIGHT * 4);
		ssd1306_WriteString("TL-W", Font_7x10, White);

		ssd1306_SetCursor(DATA_RIGHT_BLOCK, 0);
		if (_inputs[JOYSTIC_NORTH] == TI_ON) ssd1306_WriteString("1", Font_7x10, White);
		else ssd1306_WriteString("0", Font_7x10, White);

		ssd1306_SetCursor(DATA_RIGHT_BLOCK, ROW_HEIGHT);
		if (_inputs[JOYSTIC_SOUTH] == TI_ON) ssd1306_WriteString("1", Font_7x10, White);
		else ssd1306_WriteString("0", Font_7x10, White);

		ssd1306_SetCursor(DATA_RIGHT_BLOCK, ROW_HEIGHT * 2);
		if (_inputs[JOYSTIC_WEST] == TI_ON) ssd1306_WriteString("1", Font_7x10, White);
		else ssd1306_WriteString("0", Font_7x10, White);

		ssd1306_SetCursor(DATA_RIGHT_BLOCK, ROW_HEIGHT * 3);
		if (_inputs[JOYSTIC_EAST] == TI_ON) ssd1306_WriteString("1", Font_7x10, White);
		else ssd1306_WriteString("0", Font_7x10, White);

		ssd1306_SetCursor(DATA_RIGHT_BLOCK, ROW_HEIGHT * 4);
		if (_inputs[PEDESTRIAN_WEST] == TI_ON) ssd1306_WriteString("1", Font_7x10, White);
		else ssd1306_WriteString("0", Font_7x10, White);

		uint8_t top = 63 - (uint8_t)(((float)_poti_percentage * (float)63) / (float)100);

		ssd1306_DrawRectangle(118, 0, 127, 63, White);
		//ssd1306_Line(114,top,127,top,White);
		for (int i = 0; i < 8; i++) {
			ssd1306_Line(119 + i,62,119 + i,top,White);
		}
		for (int i = 0; i < 4; i++) {
			top = 63 - (uint8_t)(((float)((i + 1) * 20) * (float)63) / (float)100);
			ssd1306_Line(115,top,118,top,White);

			ssd1306_SetCursor(100, top - 4);
			if (i == 0)	ssd1306_WriteString("20", Font_6x8, White);
			if (i == 1)	ssd1306_WriteString("40", Font_6x8, White);
			if (i == 2)	ssd1306_WriteString("60", Font_6x8, White);
			if (i == 3)	ssd1306_WriteString("80", Font_6x8, White);

		}
}

void demo_gui_view_2(ti_state_t* _inputs, uint32_t _poti_percentage) {
	ssd1306_SetCursor(20, 20);
	ssd1306_WriteString("View 2", Font_7x10, White);
}
