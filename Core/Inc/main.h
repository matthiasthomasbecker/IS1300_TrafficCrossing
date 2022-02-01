/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32l4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define B1_Pin GPIO_PIN_13
#define B1_GPIO_Port GPIOC
#define USART_TX_Pin GPIO_PIN_2
#define USART_TX_GPIO_Port GPIOA
#define USART_RX_Pin GPIO_PIN_3
#define USART_RX_GPIO_Port GPIOA
#define LD2_Pin GPIO_PIN_5
#define LD2_GPIO_Port GPIOA
#define SPI_CS_U2_Pin GPIO_PIN_6
#define SPI_CS_U2_GPIO_Port GPIOA
#define TL1_Car_Pin GPIO_PIN_4
#define TL1_Car_GPIO_Port GPIOC
#define Button3_C_Pin GPIO_PIN_5
#define Button3_C_GPIO_Port GPIOC
#define SPI_CS_U1_Pin GPIO_PIN_12
#define SPI_CS_U1_GPIO_Port GPIOB
#define TL2_Car_Pin GPIO_PIN_13
#define TL2_Car_GPIO_Port GPIOB
#define TL3_Car_Pin GPIO_PIN_14
#define TL3_Car_GPIO_Port GPIOB
#define SPI_CS_U3_Pin GPIO_PIN_15
#define SPI_CS_U3_GPIO_Port GPIOB
#define Button3_B_Pin GPIO_PIN_6
#define Button3_B_GPIO_Port GPIOC
#define Button3_A_Pin GPIO_PIN_8
#define Button3_A_GPIO_Port GPIOC
#define Disp_DataInstr_Pin GPIO_PIN_9
#define Disp_DataInstr_GPIO_Port GPIOC
#define Reset_595_Pin GPIO_PIN_9
#define Reset_595_GPIO_Port GPIOA
#define TL4_Car_Pin GPIO_PIN_10
#define TL4_Car_GPIO_Port GPIOA
#define TMS_Pin GPIO_PIN_13
#define TMS_GPIO_Port GPIOA
#define TCK_Pin GPIO_PIN_14
#define TCK_GPIO_Port GPIOA
#define PL1_Switch_Pin GPIO_PIN_15
#define PL1_Switch_GPIO_Port GPIOA
#define Disp_Reset_Pin GPIO_PIN_10
#define Disp_Reset_GPIO_Port GPIOC
#define Disp_CS_Pin GPIO_PIN_11
#define Disp_CS_GPIO_Port GPIOC
#define SWO_Pin GPIO_PIN_3
#define SWO_GPIO_Port GPIOB
#define PL2_Switch_Pin GPIO_PIN_7
#define PL2_Switch_GPIO_Port GPIOB
#define Button3_Center_Pin GPIO_PIN_8
#define Button3_Center_GPIO_Port GPIOB
#define Button3_D_Pin GPIO_PIN_9
#define Button3_D_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
