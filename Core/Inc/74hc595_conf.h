/*
 * 74hc595_conf.h
 *
 *  Created on: Jan 31, 2022
 *      Author: mabecker
 */

#ifndef INC_74HC595_CONF_H_
#define INC_74HC595_CONF_H_

#include "main.h"

#define HC595_STCP_PORT		SPI_CS_U1_GPIO_Port
#define HC595_STCP_PIN		SPI_CS_U1_Pin
#define HC595_MR_PORT		Reset_595_GPIO_Port
#define HC595_MR_PIN		Reset_595_Pin
//#define HC595_OE_PORT		Enable_595_GPIO_Port
//#define HC595_OE_PIN		Enable_595_Pin

#endif /* INC_74HC595_CONF_H_ */
