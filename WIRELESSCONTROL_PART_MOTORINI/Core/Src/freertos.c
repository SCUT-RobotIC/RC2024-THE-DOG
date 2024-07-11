/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
#include "CONTROLLER0.h"
#include "can.h"
#include "sbus.h"

extern SBUS_CH_Struct SBUS_CH;

#include "HT03.h"

extern MotorData motor_data[8];
extern uint8_t motor_state;

#include "IMPULSE.h"


extern PULSE PULSE_data[4];

extern int stauts ;

extern float CH3,CH2,CH1;
extern float CH3_gain, LTH_gain;

int update = 10;
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
typedef StaticTask_t osStaticThreadDef_t;
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

/* USER CODE END Variables */
/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for myTask02 */
osThreadId_t myTask02Handle;
const osThreadAttr_t myTask02_attributes = {
  .name = "myTask02",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for MatlabFuction */
osThreadId_t MatlabFuctionHandle;
uint32_t MatlabFuctionBuffer[ 256 ];
osStaticThreadDef_t MatlabFuctionControlBlock;
const osThreadAttr_t MatlabFuction_attributes = {
  .name = "MatlabFuction",
  .cb_mem = &MatlabFuctionControlBlock,
  .cb_size = sizeof(MatlabFuctionControlBlock),
  .stack_mem = &MatlabFuctionBuffer[0],
  .stack_size = sizeof(MatlabFuctionBuffer),
  .priority = (osPriority_t) osPriorityHigh,
};
/* Definitions for myTask04 */
osThreadId_t myTask04Handle;
const osThreadAttr_t myTask04_attributes = {
  .name = "myTask04",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityRealtime,
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void *argument);
void StartTask02(void *argument);
void StartTask03(void *argument);
void StartTask04(void *argument);

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

  /* creation of myTask02 */
  myTask02Handle = osThreadNew(StartTask02, NULL, &myTask02_attributes);

  /* creation of MatlabFuction */
  MatlabFuctionHandle = osThreadNew(StartTask03, NULL, &MatlabFuction_attributes);

  /* creation of myTask04 */
  myTask04Handle = osThreadNew(StartTask04, NULL, &myTask04_attributes);

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
  /* Infinite loop */
  for(;;)
  {
    osDelay(10);
  }
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_StartTask02 */
/**
* @brief Function implementing the myTask02 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTask02 */
void StartTask02(void *argument)
{
  /* USER CODE BEGIN StartTask02 */
  /* Infinite loop */
  for(;;)
  {
		
	 if(stauts ==1){
		// CanComm_ControlCmd(CMD_MOTOR_MODE,0x07,hcan1);
			CanComm_SendControlPara(rtY.RF_theta_in,0,7.5,0.2,0,0x07,hcan2);
			osDelay(1);
	//	 CanComm_ControlCmd(CMD_MOTOR_MODE,0x05,hcan1);
			CanComm_SendControlPara(rtY.RF_theta_out,0,7.5,0.2,0,0x05,hcan2);
			osDelay(1);
		// CanComm_ControlCmd(CMD_MOTOR_MODE,0x06,hcan1);
			CanComm_SendControlPara(rtY.RB_theta_in,0,7.5,0.2,0,0x06,hcan2);
			osDelay(1);
	//	 CanComm_ControlCmd(CMD_MOTOR_MODE,0x04,hcan1);
			CanComm_SendControlPara(rtY.RB_theta_out,0,7.5,0.2,0,0x04,hcan1);
			osDelay(1);
	//	 CanComm_ControlCmd(CMD_MOTOR_MODE,0x01,hcan1);
			CanComm_SendControlPara(rtY.LB_theta_in,0,7.5,0.2,0,0x01,hcan1);
			 osDelay(1);
	//	 CanComm_ControlCmd(CMD_MOTOR_MODE,0x02,hcan1);
			CanComm_SendControlPara(rtY.LB_theta_out,0,7.5,0.2,0,0x02,hcan1);
			 osDelay(1);
	//	 CanComm_ControlCmd(CMD_MOTOR_MODE,0x08,hcan1);
			CanComm_SendControlPara(rtY.LF_theta_in,0,7.5,0.2,0,0x08,hcan2);
			osDelay(1);
	//		CanComm_ControlCmd(CMD_MOTOR_MODE,0x03,hcan1);
			CanComm_SendControlPara(rtY.LF_theta_out,0,7.5,0.2,0,0x03,hcan1);
			osDelay(1);
	 }
	 if( update == 10){
		update = 0;
		CanMotorUpdate_NULL();
	 }else{
		update ++ ;
	 }
	 
    osDelay(10);
  }
  /* USER CODE END StartTask02 */
}

/* USER CODE BEGIN Header_StartTask03 */
/**
* @brief Function implementing the MatlabFuction thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTask03 */
void StartTask03(void *argument)
{
  /* USER CODE BEGIN StartTask03 */
  /* Infinite loop */
  for(;;)
  {
		CONTROLLER0_step();
    rtU.RF_X = PULSE_data[RF].TIME_X_value;
    rtU.RF_Y = PULSE_data[RF].TIME_Y_value;

    rtU.RB_X = PULSE_data[RB].TIME_X_value;
    rtU.RB_Y = PULSE_data[RB].TIME_Y_value;

    rtU.LF_X = PULSE_data[LF].TIME_X_value;
    rtU.LF_Y = PULSE_data[LF].TIME_Y_value;

    rtU.LB_X = PULSE_data[LB].TIME_X_value;
    rtU.LB_Y = PULSE_data[LB].TIME_Y_value;
    
		stauts = 1;
    osDelay(10);
  }
  /* USER CODE END StartTask03 */
}

/* USER CODE BEGIN Header_StartTask04 */
/**
* @brief Function implementing the myTask04 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTask04 */
void StartTask04(void *argument)
{
  /* USER CODE BEGIN StartTask04 */
  /* Infinite loop */
  for(;;)
  {
//     CH3 = map(-0.020,0.020,200,1300,SBUS_CH.CH3);
//		 if(CH3>0.01){
//			CH3 = 0.01;
//		 }else if(CH3 <-0.01){
//			 CH3 = -0.01;
//		 }
		
//		if(SBUS_CH.CH3 >1400){
//      CH3 = 0.01*CH3_gain;
//    }
//    else if(SBUS_CH.CH3 <300){
//      CH3 = -0.01*CH3_gain;
//    }
//    else{
//      CH3 = 0;
//    }
		
		if(200==SBUS_CH.CH5){
			rtU.RF_HIGHT = 30;
			rtU.RB_HIGHT = 30;
			rtU.LF_HIGHT = 30;
			rtU.LB_HIGHT = 30;
		}else if(1000==SBUS_CH.CH5){
			rtU.RF_HIGHT = 40;
			rtU.RB_HIGHT = 40;
			rtU.LF_HIGHT = 40;
			rtU.LB_HIGHT = 40;
		}else if(1800==SBUS_CH.CH5){
			rtU.RF_HIGHT = 50;
			rtU.RB_HIGHT = 50;
			rtU.LF_HIGHT = 50;
			rtU.LB_HIGHT = 50;
		}else{
			rtU.RF_HIGHT = 20;
			rtU.RB_HIGHT = 20;
			rtU.LF_HIGHT = 20;
			rtU.LB_HIGHT = 20;
		}
		
		if(200==SBUS_CH.CH6){
			CH3_gain = 0;
		}else if(1000==SBUS_CH.CH6){
			CH3_gain = 1.2;
		}else if(1800==SBUS_CH.CH6){
			CH3_gain = 1.4;
		}else{
			CH3_gain = 1;
		}
		
		//CH3_gain = 1.2;	
		
		LTH_gain = 1 + (SBUS_CH.CH3 / 100)*0.1;
		
		if(SBUS_CH.CH1 >= 1100){
			CH3_gain = 1.2;
			rtU.RF_HIGHT = 50;
			rtU.RB_HIGHT = 50;
			rtU.LF_HIGHT = 50;
			rtU.LB_HIGHT = 50;
//      rtU.L_LENGTH = -120*LTH_gain;
//			rtU.R_LENGTH = 120*LTH_gain;
			rtU.L_LENGTH = -100*LTH_gain;
			rtU.R_LENGTH = 100*LTH_gain;
    }
    else if(SBUS_CH.CH1 <= 600){
			CH3_gain = 1.2;
			rtU.RF_HIGHT = 50;
			rtU.RB_HIGHT = 50;
			rtU.LF_HIGHT = 50;
			rtU.LB_HIGHT = 50;
//      rtU.L_LENGTH = 120*LTH_gain;
//			rtU.R_LENGTH = -120*LTH_gain;
			rtU.L_LENGTH = 100*LTH_gain;
			rtU.R_LENGTH = -100*LTH_gain;
    }
		else if(SBUS_CH.CH2 >= 1200){
			rtU.L_LENGTH = 100*LTH_gain;
			rtU.R_LENGTH = 100*LTH_gain;
		}
    else if(SBUS_CH.CH2 <= 700){
			rtU.L_LENGTH = -100*LTH_gain;
			rtU.R_LENGTH = -100*LTH_gain;
    }

  
		if(SBUS_CH.CH1> 600  &&  SBUS_CH.CH1 < 1100 && SBUS_CH.CH2 > 700 && SBUS_CH.CH2 <1200){
			rtU.L_LENGTH = 0;
			rtU.R_LENGTH = 0;
		}
		
//		if(200==SBUS_CH.CH6){//ÌøÔ¾³¢ÊÔ
//			PULSE_data[RF].TIME_X = 2;
//			PULSE_data[RF].TIME_Y = 2;
//			PULSE_data[RB].TIME_X = 0;
//			PULSE_data[RB].TIME_Y = 0;
//			PULSE_data[LF].TIME_X = 0;
//			PULSE_data[LF].TIME_Y = 0;
//			PULSE_data[LB].TIME_X = 0;
//			PULSE_data[LB].TIME_X = 2;
//			PULSE_data[LB].TIME_Y = 2;
//		}else if(1000==SBUS_CH.CH6){
//			CH3_gain = 0;
//			rtU.RF_HIGHT = 90;
//			rtU.RB_HIGHT = 90;
//			rtU.LF_HIGHT = 90;
//			rtU.LB_HIGHT = 90;
//			rtU.L_LENGTH = 0;
//			rtU.R_LENGTH = 0;
//			PULSE_data[RF].TIME_X = 0;
//			PULSE_data[RF].TIME_Y = 1;
//			PULSE_data[RB].TIME_X = 0;
//			PULSE_data[RB].TIME_Y = 1;
//			PULSE_data[LF].TIME_X = 0;
//			PULSE_data[LF].TIME_Y = 1;
//			PULSE_data[LB].TIME_X = 0;
//			PULSE_data[LB].TIME_Y = 1;
//		}else if(1800==SBUS_CH.CH6){
//			rtU.RF_HIGHT = 0;
//			rtU.RB_HIGHT = 0;
//			rtU.LF_HIGHT = 0;
//			rtU.LB_HIGHT = 0;
//			PULSE_data[RF].TIME_Y = 2;
//			PULSE_data[RB].TIME_Y = 2;
//			PULSE_data[LF].TIME_Y = 2;
//			PULSE_data[LB].TIME_Y = 2;
//		}else{
//			CH3_gain = 0;
//		}
		
		CH3 = 0.01 * CH3_gain;

		PULSE_UPDATE(CH3);
    osDelay(1);
  }
  /* USER CODE END StartTask04 */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

