/*
 * Accelerometer.c
 *
 *  Created on: 3 Mar 2022
 *      Author: mabecker
 */

#include "Accelerometer.h"
#include <string.h>
#include <stdio.h>

extern I2C_HandleTypeDef hi2c3;

static int32_t platform_write(void *handle, uint8_t reg, const uint8_t *bufp,
                              uint16_t len);
static int32_t platform_read(void *handle, uint8_t reg, uint8_t *bufp,
                             uint16_t len);

static int16_t data_raw_acceleration[3];
static int16_t acceleration_mg[3];
static uint8_t rst;
static stmdev_ctx_t dev_ctx;

void acc_init(void) {
	/* Initialize mems driver interface */

	//lis2dw12_reg_t int_route;
	dev_ctx.write_reg = platform_write;
	dev_ctx.read_reg = platform_read;
	dev_ctx.handle = &hi2c3;

//	lis2dw12_device_id_get(&dev_ctx, &whoamI);
//	if (whoamI != LIS2DW12_ID) {
//		printf("lis2dw12 not detected...\r\n");
//	} else {
//		printf("lis2dw12 detected!\r\n");
//	}

	/* Restore default configuration */
	lis2dw12_reset_set(&dev_ctx, PROPERTY_ENABLE);

	do {
		lis2dw12_reset_get(&dev_ctx, &rst);
	} while (rst);

	/* Enable Block Data Update */
	lis2dw12_block_data_update_set(&dev_ctx, PROPERTY_ENABLE);
	/* Set full scale */
	//lis2dw12_full_scale_set(&dev_ctx, LIS2DW12_8g);
	lis2dw12_full_scale_set(&dev_ctx, LIS2DW12_2g);
	/* Configure filtering chain
	 * Accelerometer - filter path / bandwidth
	 */
	lis2dw12_filter_path_set(&dev_ctx, LIS2DW12_LPF_ON_OUT);
	lis2dw12_filter_bandwidth_set(&dev_ctx, LIS2DW12_ODR_DIV_4);
	/* Configure power mode */
	lis2dw12_power_mode_set(&dev_ctx, LIS2DW12_HIGH_PERFORMANCE);
	//lis2dw12_power_mode_set(&dev_ctx, LIS2DW12_CONT_LOW_PWR_LOW_NOISE_12bit);
	/* Set Output Data Rate */
	lis2dw12_data_rate_set(&dev_ctx, LIS2DW12_XL_ODR_25Hz);
}

void acc_update(void) {
	uint8_t reg;
	/* Read output only if new value is available */
	lis2dw12_flag_data_ready_get(&dev_ctx, &reg);

	if (reg) {
		/* Read acceleration data */
		memset(data_raw_acceleration, 0x00, 3 * sizeof(int16_t));
		lis2dw12_acceleration_raw_get(&dev_ctx, data_raw_acceleration);
		//acceleration_mg[0] = lis2dw12_from_fs8_lp1_to_mg(data_raw_acceleration[0]);
		//acceleration_mg[1] = lis2dw12_from_fs8_lp1_to_mg(data_raw_acceleration[1]);
		//acceleration_mg[2] = lis2dw12_from_fs8_lp1_to_mg(data_raw_acceleration[2]);
//		acceleration_mg[0] = data_raw_acceleration[0];//lis2dw12_from_fs2_to_mg(
//				//data_raw_acceleration[0]);
//		acceleration_mg[1] = data_raw_acceleration[1];//lis2dw12_from_fs2_to_mg(
//				//data_raw_acceleration[1]);
//		acceleration_mg[2] = data_raw_acceleration[2];//lis2dw12_from_fs2_to_mg(
				//data_raw_acceleration[2]);
		//sprintf((char *)tx_buffer,
		//		"Acceleration [mg]:%4.2f\t%4.2f\t%4.2f\r\n",
		//		acceleration_mg[0], acceleration_mg[1], acceleration_mg[2]);
		//tx_com(tx_buffer, strlen((char const *)tx_buffer));

		acceleration_mg[0] = data_raw_acceleration[0];
		acceleration_mg[1] = data_raw_acceleration[1];
		acceleration_mg[2] = data_raw_acceleration[2];

		if (acceleration_mg[0] > 15000) acceleration_mg[0] = 15000;
		if (acceleration_mg[0] < -15000) acceleration_mg[0] = -15000;

		if (acceleration_mg[1] > 15000) acceleration_mg[1] = 15000;
		if (acceleration_mg[1] < -15000) acceleration_mg[1] = -15000;

		if (acceleration_mg[2] > 15000) acceleration_mg[2] = 15000;
		if (acceleration_mg[2] < -15000) acceleration_mg[2] = -15000;
	}
}

int16_t* acc_get_acceleration(void) {
	return acceleration_mg;
}

int16_t acc_get_acceleration_x(void) {
	return acceleration_mg[0];
}

int16_t acc_get_acceleration_y(void) {
	return acceleration_mg[1];
}

int16_t acc_get_acceleration_z(void) {
	return acceleration_mg[2];
}

static int32_t platform_write(void *handle, uint8_t reg, const uint8_t *bufp,
                              uint16_t len)
{
  HAL_I2C_Mem_Write(handle, LIS2DW12_I2C_ADD_H, reg,
                    I2C_MEMADD_SIZE_8BIT, (uint8_t*) bufp, len, 1000);
  return 0;
}

static int32_t platform_read(void *handle, uint8_t reg, uint8_t *bufp,
                             uint16_t len)
{
  HAL_I2C_Mem_Read(handle, LIS2DW12_I2C_ADD_H, reg,
                   I2C_MEMADD_SIZE_8BIT, bufp, len, 1000);
  return 0;
}
