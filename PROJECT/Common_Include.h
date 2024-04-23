/*
 * Common_Include.h
 *
 *  Created on: Jul 2, 2022
 *      Author: samar
 */

#ifndef COMMON_INCLUDE_H_
#define COMMON_INCLUDE_H_

typedef struct{
	float        soc;
	float        ah;
    float    	 voltage;
	float        current;
	float        temperature[4];
	float        cellvolatgemax;
	float        cellvolatgemin;
	uint8_t 	 error_flags[3];
}bmsdata;

/*LH Data*/
typedef struct{
	float         voltage;
	float         current;
	uint16_t      rpm;
	uint16_t      temperature;
	uint16_t      error_flags;
}motor1;

/*RH Data*/
typedef struct{
	float         voltage;
	float         current;
	uint16_t      rpm;
	uint16_t      temperature;
	uint16_t      error_flags;
}motor2;



#endif /* COMMON_INCLUDE_H_ */
