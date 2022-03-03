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

extern tl_street_t crossing[];

int16_t acc[3][DATA_SIZE];
uint8_t acc_pos;

#define MAX_VIEW 5;

demo_graph_t poti_graph;

void demo_gui_view_1(ti_state_t* _inputs, uint32_t _poti_percentage, int16_t* acceleration, env_data_t* env);	//buttons
void demo_gui_view_2(ti_state_t* _inputs, uint32_t _poti_percentage, int16_t* acceleration, env_data_t* env);	//potentiometer
void demo_gui_view_3(ti_state_t* _inputs, uint32_t _poti_percentage, int16_t* acceleration, env_data_t* env);	//environment
void demo_gui_view_5(ti_state_t* _inputs, uint32_t _poti_percentage, int16_t* acceleration, env_data_t* env);	//lights
void demo_gui_view_6(ti_state_t* _inputs, uint32_t _poti_percentage, int16_t* acceleration, env_data_t* env);	//accelerometer


static uint32_t activeView = 0;

static ti_state_t button_old;

char buffer[20];
//static uint8_t view2_data[VIEW2_DATA_SIZE];

//static uint8_t view2_pos = 0;

static uint8_t count = 0;

void demo_gui_update(ti_state_t* _inputs, uint32_t _poti_percentage, int16_t* acceleration, env_data_t* env) {
	ssd1306_Fill(Black);

	if (count == 2 || count == 4) {
		acc[0][acc_pos] = (acceleration[0] * 10) / 15000;
		acc[1][acc_pos] = (acceleration[1] * 10) / 15000;
		acc[2][acc_pos] = (acceleration[2] * 10) / 15000;
		acc_pos++;
		acc_pos%= DATA_SIZE;
	}
	if (count == 4) {
		poti_graph.data[poti_graph.pos] = (uint8_t)_poti_percentage;
		poti_graph.pos++;
		poti_graph.pos %= DATA_SIZE;

		count = 0;
	}
	count ++;


	if (button_old != _inputs[JOYSTIC_CENTER]) {
		button_old = _inputs[JOYSTIC_CENTER];

		if (button_old == TI_OFF) {
			activeView++;
			activeView = activeView % MAX_VIEW;
			tl_lights_on();
		}
	}

	if (activeView == 0) demo_gui_view_1(_inputs, _poti_percentage, acceleration, env);
	else if (activeView == 1) demo_gui_view_2(_inputs, _poti_percentage, acceleration, env);
	else if (activeView == 2) demo_gui_view_3(_inputs, _poti_percentage, acceleration, env);
	else if (activeView == 3) demo_gui_view_5(_inputs, _poti_percentage, acceleration, env);
	else if (activeView == 4) demo_gui_view_6(_inputs, _poti_percentage, acceleration, env);
}

void demo_gui_view_1(ti_state_t* _inputs, uint32_t _poti_percentage, int16_t* acceleration, env_data_t* env) {
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

void demo_gui_view_2(ti_state_t* _inputs, uint32_t _poti_percentage, int16_t* acceleration, env_data_t* env) {
	ssd1306_SetCursor(0, 0);
	ssd1306_WriteString("Potentiometer:", Font_6x8, White);

	uint8_t dist_x = 0;
	uint8_t dist_y = 0;

	uint8_t data_height = 53;
	uint8_t top, top_old;

	//Draw the axis
	ssd1306_Line(0,10,0,64,White);	//y-axis
	ssd1306_Line(0,63,128,63,White);	//x-axis

	for (int i = 1; i < DATA_SIZE; i++) {

		top_old = (uint8_t)(((float)(poti_graph.data[i - 1]) * (float)data_height) / (float)100);
		top = (uint8_t)(((float)(poti_graph.data[i]) * (float)data_height) / (float)100);
		ssd1306_Line(dist_x + (i - 1),64 - dist_y - top_old,dist_x + i,64 - dist_y - top,White);
	}
}

void demo_gui_view_3(ti_state_t* _inputs, uint32_t _poti_percentage, int16_t* acceleration, env_data_t* env) {
	ssd1306_SetCursor(0, 15);

	sprintf(buffer, "T: %2u.%u C", (unsigned int)SHT2x_GetInteger(env->temp), (unsigned int)SHT2x_GetInteger(env->temp));
	ssd1306_WriteString(buffer, Font_11x18, White);

	ssd1306_SetCursor(0, 35);
	sprintf(buffer, "H: %2u.%u%%", (unsigned int)SHT2x_GetInteger(env->hum), (unsigned int)SHT2x_GetInteger(env->hum));
	ssd1306_WriteString(buffer, Font_11x18, White);
	ssd1306_DrawCircle(96, 17, 2, White);
}

void demo_gui_view_5(ti_state_t* _inputs, uint32_t _poti_percentage, int16_t* acceleration, env_data_t* env) {
	ssd1306_SetCursor(0, 0);
	ssd1306_WriteString("Lights:", Font_6x8, White);

	static uint32_t counter = 0;

	if (counter == 0) {


		tl_setLight(&crossing[NORTH].street_signal->red, OFF);
		tl_setLight(&crossing[NORTH].street_signal->yellow, OFF);
		tl_setLight(&crossing[NORTH].street_signal->green, ON);

		tl_setLight(&crossing[EAST].street_signal->red, ON);
		tl_setLight(&crossing[EAST].street_signal->yellow, OFF);
		tl_setLight(&crossing[EAST].street_signal->green, OFF);

		tl_setLight(&crossing[SOUTH].street_signal->red, OFF);
		tl_setLight(&crossing[SOUTH].street_signal->yellow, OFF);
		tl_setLight(&crossing[SOUTH].street_signal->green, ON);

		tl_setLight(&crossing[WEST].street_signal->red, ON);
		tl_setLight(&crossing[WEST].street_signal->yellow, OFF);
		tl_setLight(&crossing[WEST].street_signal->green, OFF);

		tl_setLight(&crossing[WEST].pedestrian_signal->red, ON);
		tl_setLight(&crossing[WEST].pedestrian_signal->green, OFF);
		tl_setLight(&crossing[WEST].pedestrian_signal->blue, OFF);

		tl_setLight(&crossing[NORTH].pedestrian_signal->red, ON);
		tl_setLight(&crossing[NORTH].pedestrian_signal->green, OFF);
		tl_setLight(&crossing[NORTH].pedestrian_signal->blue, OFF);
	} else if (counter == 100) {	//switch to yellow
		tl_setLight(&crossing[NORTH].street_signal->red, OFF);
		tl_setLight(&crossing[NORTH].street_signal->yellow, ON);
		tl_setLight(&crossing[NORTH].street_signal->green, OFF);

		tl_setLight(&crossing[EAST].street_signal->red, ON);
		tl_setLight(&crossing[EAST].street_signal->yellow, OFF);
		tl_setLight(&crossing[EAST].street_signal->green, OFF);

		tl_setLight(&crossing[SOUTH].street_signal->red, OFF);
		tl_setLight(&crossing[SOUTH].street_signal->yellow, ON);
		tl_setLight(&crossing[SOUTH].street_signal->green, OFF);

		tl_setLight(&crossing[WEST].street_signal->red, ON);
		tl_setLight(&crossing[WEST].street_signal->yellow, OFF);
		tl_setLight(&crossing[WEST].street_signal->green, OFF);

		tl_setLight(&crossing[WEST].pedestrian_signal->red, ON);
		tl_setLight(&crossing[WEST].pedestrian_signal->green, OFF);
		tl_setLight(&crossing[WEST].pedestrian_signal->blue, OFF);

		tl_setLight(&crossing[NORTH].pedestrian_signal->red, ON);
		tl_setLight(&crossing[NORTH].pedestrian_signal->green, OFF);
		tl_setLight(&crossing[NORTH].pedestrian_signal->blue, OFF);
	} else if (counter == 130) {	//switch to red
		tl_setLight(&crossing[NORTH].street_signal->red, ON);
		tl_setLight(&crossing[NORTH].street_signal->yellow, OFF);
		tl_setLight(&crossing[NORTH].street_signal->green, OFF);

		tl_setLight(&crossing[EAST].street_signal->red, ON);
		tl_setLight(&crossing[EAST].street_signal->yellow, OFF);
		tl_setLight(&crossing[EAST].street_signal->green, OFF);

		tl_setLight(&crossing[SOUTH].street_signal->red, ON);
		tl_setLight(&crossing[SOUTH].street_signal->yellow, OFF);
		tl_setLight(&crossing[SOUTH].street_signal->green, OFF);

		tl_setLight(&crossing[WEST].street_signal->red, ON);
		tl_setLight(&crossing[WEST].street_signal->yellow, OFF);
		tl_setLight(&crossing[WEST].street_signal->green, OFF);

		tl_setLight(&crossing[WEST].pedestrian_signal->red, ON);
		tl_setLight(&crossing[WEST].pedestrian_signal->green, OFF);
		tl_setLight(&crossing[WEST].pedestrian_signal->blue, OFF);

		tl_setLight(&crossing[NORTH].pedestrian_signal->red, ON);
		tl_setLight(&crossing[NORTH].pedestrian_signal->green, OFF);
		tl_setLight(&crossing[NORTH].pedestrian_signal->blue, OFF);
	} else if (counter == 160) {	//switch to yellow
		tl_setLight(&crossing[NORTH].street_signal->red, ON);
		tl_setLight(&crossing[NORTH].street_signal->yellow, OFF);
		tl_setLight(&crossing[NORTH].street_signal->green, OFF);

		tl_setLight(&crossing[EAST].street_signal->red, OFF);
		tl_setLight(&crossing[EAST].street_signal->yellow, ON);
		tl_setLight(&crossing[EAST].street_signal->green, OFF);

		tl_setLight(&crossing[SOUTH].street_signal->red, ON);
		tl_setLight(&crossing[SOUTH].street_signal->yellow, OFF);
		tl_setLight(&crossing[SOUTH].street_signal->green, OFF);

		tl_setLight(&crossing[WEST].street_signal->red, OFF);
		tl_setLight(&crossing[WEST].street_signal->yellow, ON);
		tl_setLight(&crossing[WEST].street_signal->green, OFF);

		tl_setLight(&crossing[WEST].pedestrian_signal->red, ON);
		tl_setLight(&crossing[WEST].pedestrian_signal->green, OFF);
		tl_setLight(&crossing[WEST].pedestrian_signal->blue, OFF);

		tl_setLight(&crossing[NORTH].pedestrian_signal->red, ON);
		tl_setLight(&crossing[NORTH].pedestrian_signal->green, OFF);
		tl_setLight(&crossing[NORTH].pedestrian_signal->blue, OFF);
	} else if (counter == 190) {	//switch to green
		tl_setLight(&crossing[NORTH].street_signal->red, ON);
		tl_setLight(&crossing[NORTH].street_signal->yellow, OFF);
		tl_setLight(&crossing[NORTH].street_signal->green, OFF);

		tl_setLight(&crossing[EAST].street_signal->red, OFF);
		tl_setLight(&crossing[EAST].street_signal->yellow, OFF);
		tl_setLight(&crossing[EAST].street_signal->green, ON);

		tl_setLight(&crossing[SOUTH].street_signal->red, ON);
		tl_setLight(&crossing[SOUTH].street_signal->yellow, OFF);
		tl_setLight(&crossing[SOUTH].street_signal->green, OFF);

		tl_setLight(&crossing[WEST].street_signal->red, OFF);
		tl_setLight(&crossing[WEST].street_signal->yellow, OFF);
		tl_setLight(&crossing[WEST].street_signal->green, ON);

		tl_setLight(&crossing[WEST].pedestrian_signal->red, ON);
		tl_setLight(&crossing[WEST].pedestrian_signal->green, OFF);
		tl_setLight(&crossing[WEST].pedestrian_signal->blue, OFF);

		tl_setLight(&crossing[NORTH].pedestrian_signal->red, ON);
		tl_setLight(&crossing[NORTH].pedestrian_signal->green, OFF);
		tl_setLight(&crossing[NORTH].pedestrian_signal->blue, OFF);
	} else if (counter == 290) {	//switch to yellow
		tl_setLight(&crossing[NORTH].street_signal->red, ON);
		tl_setLight(&crossing[NORTH].street_signal->yellow, OFF);
		tl_setLight(&crossing[NORTH].street_signal->green, OFF);

		tl_setLight(&crossing[EAST].street_signal->red, OFF);
		tl_setLight(&crossing[EAST].street_signal->yellow, ON);
		tl_setLight(&crossing[EAST].street_signal->green, OFF);

		tl_setLight(&crossing[SOUTH].street_signal->red, ON);
		tl_setLight(&crossing[SOUTH].street_signal->yellow, OFF);
		tl_setLight(&crossing[SOUTH].street_signal->green, OFF);

		tl_setLight(&crossing[WEST].street_signal->red, OFF);
		tl_setLight(&crossing[WEST].street_signal->yellow, ON);
		tl_setLight(&crossing[WEST].street_signal->green, OFF);

		tl_setLight(&crossing[WEST].pedestrian_signal->red, ON);
		tl_setLight(&crossing[WEST].pedestrian_signal->green, OFF);
		tl_setLight(&crossing[WEST].pedestrian_signal->blue, OFF);

		tl_setLight(&crossing[NORTH].pedestrian_signal->red, ON);
		tl_setLight(&crossing[NORTH].pedestrian_signal->green, OFF);
		tl_setLight(&crossing[NORTH].pedestrian_signal->blue, OFF);
	} else if (counter == 320) {	//switch to red
		tl_setLight(&crossing[NORTH].street_signal->red, ON);
		tl_setLight(&crossing[NORTH].street_signal->yellow, OFF);
		tl_setLight(&crossing[NORTH].street_signal->green, OFF);

		tl_setLight(&crossing[EAST].street_signal->red, ON);
		tl_setLight(&crossing[EAST].street_signal->yellow, OFF);
		tl_setLight(&crossing[EAST].street_signal->green, OFF);

		tl_setLight(&crossing[SOUTH].street_signal->red, ON);
		tl_setLight(&crossing[SOUTH].street_signal->yellow, OFF);
		tl_setLight(&crossing[SOUTH].street_signal->green, OFF);

		tl_setLight(&crossing[WEST].street_signal->red, ON);
		tl_setLight(&crossing[WEST].street_signal->yellow, OFF);
		tl_setLight(&crossing[WEST].street_signal->green, OFF);

		tl_setLight(&crossing[WEST].pedestrian_signal->red, ON);
		tl_setLight(&crossing[WEST].pedestrian_signal->green, OFF);
		tl_setLight(&crossing[WEST].pedestrian_signal->blue, OFF);

		tl_setLight(&crossing[NORTH].pedestrian_signal->red, ON);
		tl_setLight(&crossing[NORTH].pedestrian_signal->green, OFF);
		tl_setLight(&crossing[NORTH].pedestrian_signal->blue, OFF);
	} else if (counter == 350) {	//switch to yellow
		tl_setLight(&crossing[NORTH].street_signal->red, OFF);
		tl_setLight(&crossing[NORTH].street_signal->yellow, ON);
		tl_setLight(&crossing[NORTH].street_signal->green, OFF);

		tl_setLight(&crossing[EAST].street_signal->red, ON);
		tl_setLight(&crossing[EAST].street_signal->yellow, OFF);
		tl_setLight(&crossing[EAST].street_signal->green, OFF);

		tl_setLight(&crossing[SOUTH].street_signal->red, OFF);
		tl_setLight(&crossing[SOUTH].street_signal->yellow, ON);
		tl_setLight(&crossing[SOUTH].street_signal->green, OFF);

		tl_setLight(&crossing[WEST].street_signal->red, ON);
		tl_setLight(&crossing[WEST].street_signal->yellow, OFF);
		tl_setLight(&crossing[WEST].street_signal->green, OFF);

		tl_setLight(&crossing[WEST].pedestrian_signal->red, ON);
		tl_setLight(&crossing[WEST].pedestrian_signal->green, OFF);
		tl_setLight(&crossing[WEST].pedestrian_signal->blue, OFF);

		tl_setLight(&crossing[NORTH].pedestrian_signal->red, ON);
		tl_setLight(&crossing[NORTH].pedestrian_signal->green, OFF);
		tl_setLight(&crossing[NORTH].pedestrian_signal->blue, OFF);
	} else if (counter == 380) {	//switch to red
		tl_setLight(&crossing[NORTH].street_signal->red, OFF);
		tl_setLight(&crossing[NORTH].street_signal->yellow, OFF);
		tl_setLight(&crossing[NORTH].street_signal->green, ON);

		tl_setLight(&crossing[EAST].street_signal->red, ON);
		tl_setLight(&crossing[EAST].street_signal->yellow, OFF);
		tl_setLight(&crossing[EAST].street_signal->green, OFF);

		tl_setLight(&crossing[SOUTH].street_signal->red, OFF);
		tl_setLight(&crossing[SOUTH].street_signal->yellow, OFF);
		tl_setLight(&crossing[SOUTH].street_signal->green, ON);

		tl_setLight(&crossing[WEST].street_signal->red, ON);
		tl_setLight(&crossing[WEST].street_signal->yellow, OFF);
		tl_setLight(&crossing[WEST].street_signal->green, OFF);

		tl_setLight(&crossing[WEST].pedestrian_signal->red, ON);
		tl_setLight(&crossing[WEST].pedestrian_signal->green, OFF);
		tl_setLight(&crossing[WEST].pedestrian_signal->blue, OFF);

		tl_setLight(&crossing[NORTH].pedestrian_signal->red, ON);
		tl_setLight(&crossing[NORTH].pedestrian_signal->green, OFF);
		tl_setLight(&crossing[NORTH].pedestrian_signal->blue, OFF);
	}

	counter++;
	counter %= 380;
}

void demo_gui_view_6(ti_state_t* _inputs, uint32_t _poti_percentage, int16_t* acceleration, env_data_t* env) {
	//sprintf(buffer, "%d, %d, %d", acceleration[0], acceleration[1], acceleration[2]);
	//ssd1306_SetCursor(0, 0);
	//ssd1306_WriteString(buffer, Font_6x8, White);

	//axis 1
	ssd1306_Line(0,0,0,20,White);
	ssd1306_Line(0,10,124,10,White);

	for (int i = 1; i < DATA_SIZE; i++) {
		ssd1306_Line(1 +(i - 1),10 - acc[0][i - 1],1 + i,10 - acc[0][i],White);
	}

	//axis 2
	ssd1306_Line(0,22,0,42,White);
	ssd1306_Line(0,32,124,32,White);

	for (int i = 1; i < DATA_SIZE; i++) {
		ssd1306_Line(1 +(i - 1),32 - acc[1][i - 1],1 + i,32 - acc[1][i],White);
	}

	//axis 3
	ssd1306_Line(0,44,0,64,White);
	ssd1306_Line(0,56,124,56,White);

	for (int i = 1; i < DATA_SIZE; i++) {
		ssd1306_Line(1 +(i - 1),56 - acc[2][i - 1],1 + i,56 - acc[2][i],White);
	}
}
