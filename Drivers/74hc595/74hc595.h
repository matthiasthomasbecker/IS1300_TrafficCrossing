/*
 * 74HC595.h
 *
 *  Created on: Jan 31, 2022
 *      Author: mabecker
 */

#ifndef INC_74HC595_H_
#define INC_74HC595_H_

#include <stddef.h>
#include <74hc595_conf.h>

void hc595_init(SPI_HandleTypeDef *_hspi, uint8_t _count);
void hc595_setBrightness(uint8_t _percentage);
void hc595_enable(void);
void hc595_disable(void);
void hc595_update(uint8_t* buffer);
void hc595_reset(void);

#endif /* INC_74HC595_H_ */
