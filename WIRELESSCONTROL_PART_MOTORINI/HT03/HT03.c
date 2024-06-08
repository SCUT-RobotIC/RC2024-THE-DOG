#include "HT03.h"
#include "main.h"
#include "can.h"


MotorData motor_data[8];
uint8_t commandbuf[8] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00};
uint8_t databuf[8]  = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
uint8_t MOTORID[8] = {0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08};
uint8_t motor_state = 0x00;



/// @brief actually not use 
void can_filter_init(void)
{
    CAN_FilterTypeDef can_filter_st1;
    can_filter_st1.FilterActivation = ENABLE;
    can_filter_st1.FilterMode = CAN_FILTERMODE_IDMASK;
    can_filter_st1.FilterScale = CAN_FILTERSCALE_32BIT;
    can_filter_st1.FilterIdHigh = 0x0000;
    can_filter_st1.FilterIdLow = 0x0000;
    can_filter_st1.FilterMaskIdHigh = 0x0000;
    can_filter_st1.FilterMaskIdLow = 0x0000;
    can_filter_st1.FilterBank = 0;
    can_filter_st1.FilterFIFOAssignment = CAN_RX_FIFO0;
		can_filter_st1.SlaveStartFilterBank = 14;
  	
	// 
		CAN_FilterTypeDef can_filter_st2;
    can_filter_st2.FilterActivation = ENABLE;
    can_filter_st2.FilterMode = CAN_FILTERMODE_IDMASK;
    can_filter_st2.FilterScale = CAN_FILTERSCALE_32BIT;
    can_filter_st2.FilterIdHigh = 0x0000;
    can_filter_st2.FilterIdLow = 0x0000;
    can_filter_st2.FilterMaskIdHigh = 0x0000;
    can_filter_st2.FilterMaskIdLow = 0x0000;
    can_filter_st2.FilterBank = 14;
	
    can_filter_st2.FilterFIFOAssignment = CAN_RX_FIFO0;
  	can_filter_st2.SlaveStartFilterBank = 28;
		
		HAL_CAN_ConfigFilter(&hcan1, &can_filter_st1);
  	HAL_CAN_ConfigFilter(&hcan2, &can_filter_st2);
		HAL_CAN_Start(&hcan1);
		HAL_CAN_Start(&hcan2);
    HAL_CAN_ActivateNotification(&hcan1, CAN_IT_RX_FIFO0_MSG_PENDING);
    HAL_CAN_ActivateNotification(&hcan2, CAN_IT_RX_FIFO0_MSG_PENDING);
	
}



/* 把buf中的内容通过CAN接口发送出去 */
void CanTransmit(uint8_t *buf, uint8_t len,uint32_t CAN_SLAVE_ID,CAN_HandleTypeDef hcan)
{
    CAN_TxHeaderTypeDef TxHead;             /**!< can通信发送协议头 */
    uint32_t canTxMailbox;
    
    if((buf != NULL) && (len != 0))
    {
        TxHead.StdId    = CAN_SLAVE_ID;     /* 指定标准标识符，该值在0x00-0x7FF */
        TxHead.IDE      = CAN_ID_STD;       /* 指定将要传输消息的标识符类型 */
        TxHead.RTR      = CAN_RTR_DATA;     /* 指定消息传输帧类型 */
        TxHead.DLC      =  len;              /* 指定将要传输的帧长度 */
        if(HAL_CAN_AddTxMessage(&hcan, &TxHead, buf, (uint32_t *)&canTxMailbox) == HAL_OK )
        {
            
        }
    }
}

/**
  * @brief  CAN init
  * @param
  * @retval 
  */
void CanMOTOR_Init()
{

  for(int i = 0; i < 8; i++)
  {
    motor_data[i].motorID = 0xFF;
    motor_data[i].position = 0;
    motor_data[i].velocity = 0;
    motor_data[i].current = 0;
  }

  // INI FROM 0-7

  do
  {
    motor_state = 0x00;

    CanComm_ControlCmd(CMD_ZERO_POSITION,0x01,hcan1);
    HAL_Delay(10);
    CanComm_ControlCmd(CMD_MOTOR_MODE,0x01,hcan1);
    HAL_Delay(10);
    
    if(motor_data[0].motorID == 0x01)
    {
       motor_state |= 1 << 0;
    }

    CanComm_ControlCmd(CMD_ZERO_POSITION,0x02,hcan1);
    HAL_Delay(10);
    CanComm_ControlCmd(CMD_MOTOR_MODE,0x02,hcan1);
    HAL_Delay(10);

    if(motor_data[1].motorID == 0x02)
    {
       motor_state |= 1 << 1;
    }

    CanComm_ControlCmd(CMD_ZERO_POSITION,0x03,hcan1);
    HAL_Delay(10);
    CanComm_ControlCmd(CMD_MOTOR_MODE,0x03,hcan1);
    HAL_Delay(10);

    if(motor_data[2].motorID == 0x03)
    {
       motor_state |= 1 << 2;
    }


    CanComm_ControlCmd(CMD_ZERO_POSITION,0x04,hcan1);
    HAL_Delay(10);
    CanComm_ControlCmd(CMD_MOTOR_MODE,0x04,hcan1);
    HAL_Delay(10);

    if(motor_data[3].motorID == 0x04)
    {
       motor_state |= 1 << 3;
    }

    CanComm_ControlCmd(CMD_ZERO_POSITION,0x05,hcan2);
    HAL_Delay(10);
    CanComm_ControlCmd(CMD_MOTOR_MODE,0x05,hcan2);
    HAL_Delay(10);

    if(motor_data[4].motorID == 0x05)
    {
       motor_state |= 1 << 4;
    }

    CanComm_ControlCmd(CMD_ZERO_POSITION,0x06,hcan2);
    HAL_Delay(10);
    CanComm_ControlCmd(CMD_MOTOR_MODE,0x06,hcan2);
    HAL_Delay(10);

    if(motor_data[5].motorID == 0x06)
    {
       motor_state |= 1 << 5;
    }

    CanComm_ControlCmd(CMD_ZERO_POSITION,0x07,hcan2);
    HAL_Delay(10);
    CanComm_ControlCmd(CMD_MOTOR_MODE,0x07,hcan2);
    HAL_Delay(10);

    if(motor_data[6].motorID == 0x07)
    {
       motor_state |= 1 << 6;
    }

    CanComm_ControlCmd(CMD_ZERO_POSITION,0x08,hcan2);
    HAL_Delay(10);
    CanComm_ControlCmd(CMD_MOTOR_MODE,0x08,hcan2);
    HAL_Delay(10);

    if(motor_data[7].motorID == 0x08)
    {
       motor_state |= 1 << 7;
    }
 



  }while(motor_state != 0xFF);

}
/**
  * @brief  Just Refresh the data
  * @param
  * @retval 
  */
void CanMotorUpdate_NULL(){
	 CanComm_ControlCmd(CMD_MOTOR_MODE,0x01,hcan1);

	 CanComm_ControlCmd(CMD_MOTOR_MODE,0x02,hcan1);
  
	 CanComm_ControlCmd(CMD_MOTOR_MODE,0x03,hcan1);
  
	 CanComm_ControlCmd(CMD_MOTOR_MODE,0x04,hcan1);
  
	 CanComm_ControlCmd(CMD_MOTOR_MODE,0x05,hcan2);
   
	 CanComm_ControlCmd(CMD_MOTOR_MODE,0x06,hcan2);
  
	 CanComm_ControlCmd(CMD_MOTOR_MODE,0x07,hcan2);
   
	 CanComm_ControlCmd(CMD_MOTOR_MODE,0x08,hcan2);
  
}

/**
  * @brief  Converts a float to an unsigned int, given range and number of bits
  * @param
  * @retval 
  */
static uint16_t float_to_uint(float x, float x_min, float x_max, uint8_t bits)
{
    float span = x_max - x_min;
    float offset = x_min;
    
    return (uint16_t) ((x-offset)*((float)((1<<bits)-1))/span);
}

/**
  * @brief  converts unsigned int to float, given range and number of bits
  * @param
  * @retval 
  */
static float uint_to_float(int x_int, float x_min, float x_max, int bits)
{
    float span = x_max - x_min;
    float offset = x_min;
    return ((float)x_int)*span/((float)((1<<bits)-1)) + offset;
}




/**
  * @brief  Can总线发送控制参数
  * @param
  * @retval 
  */
void CanComm_SendControlPara(float f_p, float f_v, float f_kp, float f_kd, float f_t,uint32_t CAN_SLAVE_ID,CAN_HandleTypeDef hcan)
{
    uint16_t p, v, kp, kd, t;
    
    
    /* 限制输入的参数在定义的范围内 */
    LIMIT_MIN_MAX(f_p,  P_MIN,  P_MAX);
    LIMIT_MIN_MAX(f_v,  V_MIN,  V_MAX);
    LIMIT_MIN_MAX(f_kp, KP_MIN, KP_MAX);
    LIMIT_MIN_MAX(f_kd, KD_MIN, KD_MAX);
    LIMIT_MIN_MAX(f_t,  T_MIN,  T_MAX);
    
    /* 根据协议，对float参数进行转换 */
    p = float_to_uint(f_p,      P_MIN,  P_MAX,  16);       // pos     
    v = float_to_uint(f_v,      V_MIN,  V_MAX,  12);       // velocity
    kp = float_to_uint(f_kp,    KP_MIN, KP_MAX, 12);       // kp
    kd = float_to_uint(f_kd,    KD_MIN, KD_MAX, 12);      // kd      
    t = float_to_uint(f_t,      T_MIN,  T_MAX,  12);     // t
    
    /* 根据传输协议，把数据转换为CAN命令数据字段 */
    databuf[0] = p>>8;
    databuf[1] = p&0xFF;
    databuf[2] = v>>4;
    databuf[3] = ((v&0xF)<<4)|(kp>>8);
    databuf[4] = kp&0xFF;
    databuf[5] = kd>>4;
    databuf[6] = ((kd&0xF)<<4)|(t>>8);
    databuf[7] = t&0xff;
    
    /* 通过CAN接口把buf中的内容发送出去 */
    CanTransmit(databuf, sizeof(databuf),CAN_SLAVE_ID,hcan);
}

/////////
////////
////////


void CanComm_ControlCmd(uint8_t cmd,uint32_t CAN_SLAVE_ID,CAN_HandleTypeDef hcan)
{
  			
    switch(cmd)
    {
        case CMD_MOTOR_MODE:
            commandbuf[7] = 0xFC;
            break;
        
        case CMD_RESET_MODE:
            commandbuf[7] = 0xFD;
        break;
        
        case CMD_ZERO_POSITION:
            commandbuf[7] = 0xFE;
        break;
        
        default:
        return; /* 直接退出函数 */
    }
    CanTransmit(commandbuf, sizeof(commandbuf),CAN_SLAVE_ID,hcan);
}


/**
  * @brief  CAN初始化
  * @param
  * @retval 
  */



/**
  * @brief  CAN接口接收数据
  * @param
  * @retval 
  */


/*
In response, the motor drive will send back the following data:
8 bit motor ID
16 bit position, scaled between P MIN and P MAX in CAN_COM.cpp12 bit velocity, between 0 and 4095,scaled V MIN and V MAX12 bit current, between 0 and 4095,scaled to -40 and 40 Amps, corresponding topeak phase current.
The 3 signals are packed into the 6 bytes in the following structure:Byte 0: Motor ID
Byte 1:Position bits 15-8
Byte 2: Position bits 7-0
Byte 3:Velocity bits 11-4
Byte 4: Velocity bits 3-0: current bits 11-8
Byte 5: Current bits 7-0
 */


void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
    uint16_t tmp_value;
    
    CAN_RxHeaderTypeDef RxHead; /**!< can通信协议头 */
    uint8_t data[8];
	
    // check can 1 or not
    if(hcan == &hcan1)
    {
        HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &RxHead, data);
        if(data[0] <= 0x08){
            if(motor_data[data[0]-1].motorID != data[0]){
						   motor_data[data[0]-1].motorID = data[0];
						}
						uint16_t position = (data[2] << 8)|data[1];
						motor_data[data[0]-1].position = uint_to_float((data[1] << 8) | data[2], P_MIN, P_MAX, 16);				
            motor_data[data[0]-1].velocity = uint_to_float((data[3] << 4) | (data[4] >> 4), V_MIN, V_MAX, 12);
            motor_data[data[0]-1].current = uint_to_float(((data[4] & 0x0F) << 8) | data[5], T_MIN, T_MAX, 12);
        }
			 HAL_CAN_ActivateNotification(hcan, CAN_IT_RX_FIFO0_MSG_PENDING);
				
				
		}else if( hcan == &hcan2){
			HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &RxHead, data);
        if(data[0] <= 0x08){           
						
						if(motor_data[data[0]-1].motorID != data[0]){
						   motor_data[data[0]-1].motorID = data[0];
						}
						uint16_t position = (data[2] << 8)|data[1];
						motor_data[data[0]-1].position = uint_to_float((data[1] << 8) | data[2], P_MIN, P_MAX, 16);
            motor_data[data[0]-1].velocity = uint_to_float((data[3] << 4) | (data[4] >> 4), V_MIN, V_MAX, 12);
            motor_data[data[0]-1].current = uint_to_float(((data[4] & 0x0F) << 8) | data[5], T_MIN, T_MAX, 12);
            // 这里可以添加处理motor_data的代码
        }
			 HAL_CAN_ActivateNotification(hcan, CAN_IT_RX_FIFO0_MSG_PENDING);
		}		
    
   
}




