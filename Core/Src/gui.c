/*
 * gui.c
 *
 *  Created on: Feb 4, 2022
 *      Author: mabecker
 */


#include "gui.h"

static void gui_setLine(uint8_t _line);

void gui_init(void) {

}

static void gui_setLine(uint8_t _line) {
	uint8_t line_height = 12 * _line;

	ssd1306_SetCursor(2, line_height);
}

