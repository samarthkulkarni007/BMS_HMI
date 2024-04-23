/*
 * CAN.h
 *
 *  Created on: Jul 2, 2022
 *      Author: samar
 */

#ifndef CAN_H_
#define CAN_H_

/*BMS Transmit IDs*/
#define ADDT90   0x18900140
#define ADDT91   0x18910140
#define ADDT92   0x18920140
#define ADDT93   0x18930140
#define ADDT96   0x18960140
#define ADDT98   0x18980140

/*BMS Recieve IDs*/
#define ADDR90   0x18904001
#define ADDR91   0x18914001
#define ADDR92   0x18924001
#define ADDR93   0x18934001
#define ADDR96   0x18964001
#define ADDR98   0x18984001

/*Motor Controller Recieve Data*/
#define MADDR1   0x0CF11E05
#define MADDR2   0x0CF11F05
#define MADDR3   0x0CF11E06
#define MADDR4   0x0CF11F06


typedef struct{
	uint32_t canid;
	uint8_t  rxdata[8];
	uint8_t  dlc;
}canheader;

void can_init();

void bms_can_transmit(void *pvParameters);

void can_recieve_task(void *pvParameters);


#endif /* CAN_H_ */
