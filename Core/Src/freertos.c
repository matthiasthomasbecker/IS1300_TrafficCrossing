/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
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

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "trafficlights.h"
#include "traffic_inputs.h"
#include "SEGGER_SYSVIEW.h"
#include "semphr.h"
#include "ssd1306.h"
#include "demo_gui.h"
#include "Accelerometer.h"
#include "environment.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

SemaphoreHandle_t dataMutex;

/* USER CODE END Variables */
/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for input_task */
osThreadId_t input_taskHandle;
const osThreadAttr_t input_task_attributes = {
  .name = "input_task",
  .stack_size = 128 * 8,
  .priority = (osPriority_t) 3,
};
/* Definitions for output_task */
osThreadId_t output_taskHandle;
const osThreadAttr_t output_task_attributes = {
  .name = "output_task",
  .stack_size = 128 * 8,
  .priority = (osPriority_t) 1,
};
/* Definitions for sensor_task */
//osThreadId_t sensor_taskHandle;
//const osThreadAttr_t sensor_task_attributes = {
//  .name = "sensor_task",
//  .stack_size = 128 * 4,
//  .priority = (osPriority_t) osPriorityLow,
//};

/* Definitions for sensor_task */
osThreadId_t processing_taskHandle;
const osThreadAttr_t processing_task_attributes = {
  .name = "processing_task",
  .stack_size = 128 * 8,
  .priority = (osPriority_t) 2,
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void *argument);
void StartInputTask(void *argument);
void StartOutputTask(void *argument);
//void StartSensorTask(void *argument);
void StartProcessingTask(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of defaultTask */
  defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

  /* creation of input_task */
  input_taskHandle = osThreadNew(StartInputTask, NULL, &input_task_attributes);

  /* creation of output_task */
  output_taskHandle = osThreadNew(StartOutputTask, NULL, &output_task_attributes);

  /* creation of sensor_task */
  //sensor_taskHandle = osThreadNew(StartSensorTask, NULL, &sensor_task_attributes);

  /* creation of processing_task */
  processing_taskHandle = osThreadNew(StartProcessingTask, NULL, &processing_task_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */

  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void *argument)
{

  /* USER CODE BEGIN StartDefaultTask */
	SEGGER_SYSVIEW_Start();
	dataMutex = xSemaphoreCreateMutex();
	vTaskSuspend(NULL);
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_StartInputTask */
/**
* @brief Function implementing the input_task thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartInputTask */
void StartInputTask(void *argument)
{
  /* USER CODE BEGIN StartInputTask */
	TickType_t xLastWakeTime;
	const TickType_t xPeriod = pdMS_TO_TICKS(100) ;
	xLastWakeTime = xTaskGetTickCount();

	/* Infinite loop */
	for(;;)
	{

		/**
		 * Copy the input data to the shared state
		 */
		if(xSemaphoreTake(dataMutex, portMAX_DELAY) == pdTRUE) {
			ti_update();
			acc_update();
			env_update();
			xSemaphoreGive(dataMutex);
		}

		vTaskDelayUntil( &xLastWakeTime, xPeriod);
	}
  /* USER CODE END StartInputTask */
}

/* USER CODE BEGIN Header_StartOutputTask */
/**
* @brief Function implementing the output_task thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartOutputTask */
void StartOutputTask(void *argument)
{
	/* USER CODE BEGIN StartOutputTask */
	TickType_t xLastWakeTime;
	const TickType_t xPeriod = pdMS_TO_TICKS(100) ;
	xLastWakeTime = xTaskGetTickCount();

	/* Infinite loop */
	for(;;)
	{
		if(xSemaphoreTake(dataMutex, portMAX_DELAY) == pdTRUE) {
			tl_update();
			ssd1306_UpdateScreen();
			tl_brightnessUpdate();
			xSemaphoreGive(dataMutex);
		}
		vTaskDelayUntil( &xLastWakeTime, xPeriod);
	}
	/* USER CODE END StartOutputTask */
}

/* USER CODE BEGIN Header_StartSensorTask */
/**
* @brief Function implementing the sensor_task thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartSensorTask */
//void StartSensorTask(void *argument)
//{
//	/* USER CODE BEGIN StartSensorTask */
//	/* Infinite loop */
//	TickType_t xLastWakeTime;
//	const TickType_t xPeriod = pdMS_TO_TICKS(20) ;
//	xLastWakeTime = xTaskGetTickCount();
//
//	/* Infinite loop */
//	for(;;)
//	{
//		vTaskDelayUntil( &xLastWakeTime, xPeriod);
//	}
//	/* USER CODE END StartSensorTask */
//}

/* USER CODE BEGIN Header_StartProcessingTask */
/**
* @brief Function implementing the processing_task thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartProcessingTask */
void StartProcessingTask(void *argument)
{
	/* USER CODE BEGIN StartSensorTask */

	// Copy of the inputs
	ti_state_t input_state[TI_INPUT_COUNT];

	TickType_t xLastWakeTime;
	const TickType_t xPeriod = pdMS_TO_TICKS(100) ;
	xLastWakeTime = xTaskGetTickCount();

	/* Infinite loop */
	for(;;)
	{
		if(xSemaphoreTake(dataMutex, portMAX_DELAY) == pdTRUE) {
			ti_get_states(input_state);
			xSemaphoreGive(dataMutex);
		}
		demo_gui_update(input_state, ti_get_poti_percent(), acc_get_acceleration(), env_get_data());
		tl_brightnessControl(ti_get_poti_percent());
		vTaskDelayUntil( &xLastWakeTime, xPeriod);
	}
	/* USER CODE END StartSensorTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

