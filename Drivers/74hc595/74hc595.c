/*
 * 74HC595.c
 *
 *  Created on: Jan 31, 2022
 *      Author: mabecker
 */

#include "74hc595.h"
#include "main.h"

static SPI_HandleTypeDef *spi_handle;
extern TIM_HandleTypeDef htim3;
static uint8_t count;

/**
 *
 */
void hc595_init(SPI_HandleTypeDef *_hspi, uint8_t _count) {
	spi_handle = _hspi;	//register the SPI handle
	count = _count;		//register how many 74HC595 chips are daisy chained

	HAL_GPIO_WritePin(HC595_MR_PORT, HC595_MR_PIN, GPIO_PIN_SET);
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);
	hc595_disable();
}

/**
 * Set the brightness of the LEDs. A value between 0 and 100
 */
void hc595_setBrightness(uint8_t _percentage) {
	if (_percentage > 100) return;

	TIM3->CCR2 = 10000 - (_percentage * 100);	//period is 10000
}

/**
 *
 */
void hc595_enable(void) {
	hc595_setBrightness(100);
}

/**
 *
 */
void hc595_disable(void) {
	hc595_setBrightness(0);
}

/**
 *
 */
void hc595_update(uint8_t* buffer) {
	HAL_SPI_Transmit(spi_handle, buffer, count, 1);

	HAL_GPIO_WritePin(HC595_STCP_PORT, HC595_STCP_PIN, GPIO_PIN_SET);
	HAL_GPIO_WritePin(HC595_STCP_PORT, HC595_STCP_PIN, GPIO_PIN_RESET);
}

/**
 *
 */
void hc595_reset(void) {
	//HAL_GPIO_WritePin(HC595_OE_PORT, HC595_OE_PIN, GPIO_PIN_SET);
	HAL_GPIO_WritePin(HC595_MR_PORT, HC595_MR_PIN, GPIO_PIN_RESET);
}
