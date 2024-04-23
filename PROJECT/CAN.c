/*
 * CAN.c
 *
 *  Created on: Jul 2, 2022
 *      Author: samar
 */

#include "main.h"

SemaphoreHandle_t bmstransmit;
extern UART_HandleTypeDef huart1;
extern CAN_HandleTypeDef hcan1;

CAN_TxHeaderTypeDef    TxHeader;

 uint8_t               TxData[8]={0};

 uint32_t              TxMailbox;

 CAN_FilterTypeDef     sFilterConfig;

 CAN_FilterTypeDef     sFilterConfig1;

/*BMS ID Masking*/
 uint32_t filter_id=0x18904001;

 uint32_t filter_mask=0x1f00ffff;

 /*Motor Controller ID Masking*/
 uint32_t filter_id1=0x0CF11F05;

 uint32_t filter_mask1=0x0FF11000;


 CAN_RxHeaderTypeDef   RxHeader;

 uint8_t               RxData[8];

 uint32_t              Rxbox;

 canheader candata_tx,candata_rx;

 QueueHandle_t can_transmit_queue;

 BaseType_t xHigherPriorityTaskWoken;

 SemaphoreHandle_t complete_update;

 extern bmsdata bmsupdate;

 bmsdata bmsupdate;

 extern motor1 rh_data;
 extern motor2 lh_data;
 motor1 rh_data;
 motor2 lh_data;
 void can_init(){

	  if(HAL_CAN_Init(&hcan1) != HAL_OK)
	  {
	    /* Initialization Error */
	    Error_Handler();
	  }

	  complete_update=xSemaphoreCreateMutex();

	  sFilterConfig.FilterBank = 0;
	  sFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK ;
	  sFilterConfig.FilterScale = CAN_FILTERSCALE_32BIT;
	  sFilterConfig.FilterIdHigh = filter_id >> 13 & 0xFFFF;
	  sFilterConfig.FilterIdLow = filter_id << 3 & 0xFFF8;
	  sFilterConfig.FilterMaskIdHigh = filter_mask >> 13 & 0xFFFF;
	  sFilterConfig.FilterMaskIdLow = filter_mask << 3 & 0xFFF8;
	  sFilterConfig.FilterFIFOAssignment = CAN_RX_FIFO0;
	  sFilterConfig.FilterActivation = ENABLE;

	  sFilterConfig1.FilterBank = 1;
	  sFilterConfig1.FilterMode = CAN_FILTERMODE_IDMASK ;
	  sFilterConfig1.FilterScale = CAN_FILTERSCALE_32BIT;
	  sFilterConfig1.FilterIdHigh = filter_id1 >> 13 & 0xFFFF;
	  sFilterConfig1.FilterIdLow = filter_id1 << 3 & 0xFFF8;
	  sFilterConfig1.FilterMaskIdHigh = filter_mask1 >> 13 & 0xFFFF;
	  sFilterConfig1.FilterMaskIdLow = filter_mask1 << 3 & 0xFFF8;
	  sFilterConfig1.FilterFIFOAssignment = CAN_RX_FIFO0;
	  sFilterConfig1.FilterActivation = ENABLE;

	  if(HAL_CAN_ConfigFilter(&hcan1, &sFilterConfig) != HAL_OK)
	  {
	    /* Filter configuration Error */
	    Error_Handler();
	  }

	  if(HAL_CAN_ConfigFilter(&hcan1, &sFilterConfig1) != HAL_OK)
	  {

	    Error_Handler();
	  }





	  HAL_CAN_ActivateNotification(&hcan1, CAN_IT_RX_FIFO0_MSG_PENDING);
	  if (HAL_CAN_Start(&hcan1) != HAL_OK)
	  {
	    /* Start Error */
	    Error_Handler();
	  }
	  can_transmit_queue=xQueueCreate(15,sizeof(canheader));

 }

 void bms_can_transmit(void *pvParameters){
	 int i=0;
	 TxHeader.DLC=8;
	 TxHeader.RTR=CAN_RTR_DATA;
	 TxHeader.IDE=CAN_ID_EXT;
	 for(;;)
	 {

			switch(i){
				case 0:
					TxHeader.ExtId=ADDT90;
					HAL_CAN_AddTxMessage(&hcan1,&TxHeader,TxData,&TxMailbox);
					break;
				case 1:
					TxHeader.ExtId=ADDT91;
					HAL_CAN_AddTxMessage(&hcan1,&TxHeader,TxData,&TxMailbox);
					break;
				case 2:
					TxHeader.ExtId=ADDT92;
					HAL_CAN_AddTxMessage(&hcan1,&TxHeader,TxData,&TxMailbox);
					break;
				case 3:
					TxHeader.ExtId=ADDT93;
					HAL_CAN_AddTxMessage(&hcan1,&TxHeader,TxData,&TxMailbox);
					break;
				case 4:
					TxHeader.ExtId=ADDT96;
					HAL_CAN_AddTxMessage(&hcan1,&TxHeader,TxData,&TxMailbox);
					break;
				case 5:
					TxHeader.ExtId=ADDT98;
					HAL_CAN_AddTxMessage(&hcan1,&TxHeader,TxData,&TxMailbox);
					break;

			}
			if(i>5){
				i=0;
			}
			else{
				i++;
			}
			vTaskDelay(pdMS_TO_TICKS(100));


	 }
 }
 void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
 {
	 HAL_CAN_GetRxMessage(&hcan1, CAN_RX_FIFO0, &RxHeader, RxData);
	 xHigherPriorityTaskWoken = pdFALSE;
	 candata_tx.canid=RxHeader.ExtId;
	 candata_tx.dlc=RxHeader.DLC;
	 candata_tx.rxdata[0]=RxData[0];
	 candata_tx.rxdata[1]=RxData[1];
	 candata_tx.rxdata[2]=RxData[2];
	 candata_tx.rxdata[3]=RxData[3];
	 candata_tx.rxdata[4]=RxData[4];
	 candata_tx.rxdata[5]=RxData[5];
	 candata_tx.rxdata[6]=RxData[6];
	 candata_tx.rxdata[7]=RxData[7];
	 xQueueSendFromISR( can_transmit_queue, &candata_tx, &xHigherPriorityTaskWoken );
	 //printf("Can Data Recived %x\n",RxHeader.ExtId);


}

void can_recieve_task(void *pvParameters)
{

	for(;;)
	{
		if(xQueueReceive(can_transmit_queue,&candata_rx,portMAX_DELAY)==pdTRUE)
		{
			xSemaphoreTake(complete_update,0);
			switch(candata_rx.canid)
			{
				case ADDR90:
					bmsupdate.voltage=(float)((candata_rx.rxdata[0] << 8) | candata_rx.rxdata[1])/10;
					bmsupdate.current=(float)((candata_rx.rxdata[4]<<8|candata_rx.rxdata[5])/10)-3000;
					bmsupdate.soc=(float)((candata_rx.rxdata[6] << 8) | candata_rx.rxdata[7])/10;
					set_value(bmsupdate.voltage,BATTERY_VOLTAGE);
					set_value(bmsupdate.current,BATTERY_CURRENT);
					set_bms_soc(&bmsupdate.soc);
					break;
				case ADDR91:
					bmsupdate.cellvolatgemax=(float)((candata_rx.rxdata[0] << 8) | candata_rx.rxdata[1])/1000;
					bmsupdate.cellvolatgemin=(float)((candata_rx.rxdata[3] << 8) | candata_rx.rxdata[4])/1000;
					set_value(bmsupdate.cellvolatgemax,BATTERY_CELL_MAX_VOLATGE);
					set_value(bmsupdate.cellvolatgemin,BATTERY_CELL_MIN_VOLATGE);
					break;
				case ADDR93:
					bmsupdate.ah=(float)((candata_rx.rxdata[4] << 24) |(candata_rx.rxdata[5] << 16) |(candata_rx.rxdata[6] << 8) | candata_rx.rxdata[7])/1000;
					set_bms_ah(&bmsupdate.ah);
				case ADDR96:
					if(candata_rx.rxdata[0]==0x01)
					{
						bmsupdate.temperature[0]=(float) (candata_rx.rxdata[1]-40);
						bmsupdate.temperature[1]=(float) (candata_rx.rxdata[2]-40);
						bmsupdate.temperature[2]=(float) (candata_rx.rxdata[3]-40);
						bmsupdate.temperature[3]=(float) (candata_rx.rxdata[4]-40);
						set_value(bmsupdate.temperature[0],BATTERY_TEMPERATURE1);
						set_value(bmsupdate.temperature[1],BATTERY_TEMPERATURE2);
						set_value(bmsupdate.temperature[2],BATTERY_TEMPERATURE3);
						set_value(bmsupdate.temperature[3],BATTERY_TEMPERATURE4);

					}
					break;
				case ADDR98:
					bmsupdate.error_flags[0]=candata_rx.rxdata[0]; /*storing cell voltage High/low*/
					bmsupdate.error_flags[1]=candata_rx.rxdata[1]; /*storing cell Temperature High/low during charge and discharge*/
					bmsupdate.error_flags[2]=candata_rx.rxdata[2]; /*storing cell Over current in  charge and discharge*/
					bmsupdate.error_flags[3]=candata_rx.rxdata[3]; /*storing cell deviation*/
					computer_bms_cell_error(bmsupdate.error_flags[0]);
					computer_bms_temperature_error(bmsupdate.error_flags[1]);
					compute_bms_current_error(bmsupdate.error_flags[2]);
					computer_bms_cell_deviation_error(bmsupdate.error_flags[3]);
					break;
				case MADDR1:
					rh_data.rpm=(candata_rx.rxdata[1]*256)+candata_rx.rxdata[0];
					rh_data.voltage=(float)((candata_rx.rxdata[5]*256)+candata_rx.rxdata[4])/10;
					rh_data.current=(float)((candata_rx.rxdata[3]*256)+candata_rx.rxdata[2])/10;
					rh_data.error_flags=(candata_rx.rxdata[7]<<8)|(candata_rx.rxdata[6]);
					set_value(rh_data.rpm,RH_MOTOR_RPM );
					set_value(rh_data.voltage,RH_MOTOR_VOLATGE );
					set_value(rh_data.current,RH_MOTOR_CURRENT);
					computer_motor_error_rh(rh_data.error_flags);
					break;
				case MADDR2:
					rh_data.temperature=(candata_rx.rxdata[1])-40;
					set_value(rh_data.temperature,RH_MOTOR_TEMPERATURE);
					break;
				case MADDR3:
					lh_data.rpm=(candata_rx.rxdata[1]*256)+candata_rx.rxdata[0];
					lh_data.voltage=(float)((candata_rx.rxdata[5]*256)+candata_rx.rxdata[4])/10;
					lh_data.current=(float)((candata_rx.rxdata[3]*256)+candata_rx.rxdata[2])/10;
					lh_data.error_flags=(candata_rx.rxdata[7]<<8)|(candata_rx.rxdata[6]);
					set_value(lh_data.rpm,LH_MOTOR_RPM);
					set_value(lh_data.voltage,LH_MOTOR_VOLATGE);
					set_value(lh_data.current,LH_MOTOR_CURRENT);
					computer_motor_error_lh(lh_data.error_flags);
					break;
				case MADDR4:
					lh_data.temperature=(candata_rx.rxdata[1])-40;
					set_value(lh_data.temperature,LH_MOTOR_TEMPERATURE);
					break;
			}
			xSemaphoreGive(complete_update);
		}


	}




}


