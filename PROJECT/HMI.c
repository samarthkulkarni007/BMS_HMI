/*
 * HMI.c
 *
 *  Created on: Jul 2, 2022
 *      Author: samar
 */
#include "main.h"

extern UART_HandleTypeDef huart2;
extern UART_HandleTypeDef huart1;

char err_rh[16][6]={RH_MOTOR_ERROR_0,RH_MOTOR_ERROR_1,RH_MOTOR_ERROR_2,RH_MOTOR_ERROR_3,RH_MOTOR_ERROR_4,RH_MOTOR_ERROR_5,RH_MOTOR_ERROR_6,RH_MOTOR_ERROR_7,RH_MOTOR_ERROR_8,RH_MOTOR_ERROR_9,RH_MOTOR_ERROR_10,RH_MOTOR_ERROR_11,RH_MOTOR_ERROR_12,RH_MOTOR_ERROR_13,RH_MOTOR_ERROR_14,RH_MOTOR_ERROR_15};

char err_lh[16][6]={LH_MOTOR_ERROR_0,LH_MOTOR_ERROR_1,LH_MOTOR_ERROR_2,LH_MOTOR_ERROR_3,LH_MOTOR_ERROR_4,LH_MOTOR_ERROR_5,LH_MOTOR_ERROR_6,LH_MOTOR_ERROR_7,LH_MOTOR_ERROR_8,LH_MOTOR_ERROR_9,LH_MOTOR_ERROR_10,LH_MOTOR_ERROR_11,LH_MOTOR_ERROR_12,LH_MOTOR_ERROR_13,LH_MOTOR_ERROR_14,LH_MOTOR_ERROR_15};



void set_value(float value,char widget_name[])
{
	printf("ST<{\"cmd_code\":\"set_value\",\"type\":\"label\",\"widget\":\"%s\",\"value\":%0.2f}>ET\n     ",widget_name,value);
}

void set_text(char text[],char widget_name[])
{
	printf("ST<{\"cmd_code\":\"set_text\",\"type\":\"label\",\"widget\":\"%s\",\"text\":\"%s\"}>ET\n      ",widget_name,text);
}

void set_progress_bar(float value,char widget_name[])
{
	printf("ST<{\"cmd_code\":\"set_value\",\"type\":\"progress_bar\",\"widget\":\"%s\",\"value\":%f}>ET\n  ",widget_name,value);

}

void set_circular_bar(float value,char widget_name[])
{
	printf("ST<{\"cmd_code\":\"set_value\",\"type\":\"progress_circle\",\"widget\":\"%s\",\"value\":%f}>ET\n   ",widget_name,value);
}

void computer_bms_cell_error(uint8_t error)
{
	if(error>0)
	{
		if((error&single_cell_voltage_high)==single_cell_voltage_high)
		{
			printf("ST<{\"cmd_code\":\"set_text\",\"type\":\"label\",\"widget\":\"%s\",\"text\":\"Single Cell Voltage High\"}>ET\n    ",BATTERY_CELL_ERROR);
		}
		if((error&single_cell_voltage_low)==single_cell_voltage_low)
		{
			printf("ST<{\"cmd_code\":\"set_text\",\"type\":\"label\",\"widget\":\"%s\",\"text\":\"Single Cell Voltage Low\"}>ET\n     ",BATTERY_CELL_ERROR);
		}
	}
	else
	{
		printf("ST<{\"cmd_code\":\"set_text\",\"type\":\"label\",\"widget\":\"%s\",\"text\":\"\"}>ET\n      ",BATTERY_CELL_ERROR);
	}
}

void computer_bms_temperature_error(uint8_t error)
{
	if(error)
	{
		if((error&temperature_high_charge)==temperature_high_charge)
		{
			printf("ST<{\"cmd_code\":\"set_text\",\"type\":\"label\",\"widget\":\"%s\",\"text\":\"Temperature High in charge\"}>ET\n     ",BATEERY_TEMP_ERROR);
		}

		if((error&temperatue_low_charge)==temperatue_low_charge)
		{
			printf("ST<{\"cmd_code\":\"set_text\",\"type\":\"label\",\"widget\":\"%s\",\"text\":\"Temperature Low in charge\"}>ET\n      ",BATEERY_TEMP_ERROR);
		}

		if((error&temperature_high_discharge)==temperature_high_discharge)
		{
			printf("ST<{\"cmd_code\":\"set_text\",\"type\":\"label\",\"widget\":\"%s\",\"text\":\"Temperature High in discharge\"}>ET\n   ",BATEERY_TEMP_ERROR);
		}

		if((error&temperature_low_discharge)==temperature_low_discharge)
		{
			printf("ST<{\"cmd_code\":\"set_text\",\"type\":\"label\",\"widget\":\"%s\",\"text\":\"Temperature Low in discharge\"}>ET\n    ",BATEERY_TEMP_ERROR);
		}


	}
	else
	{
		printf("ST<{\"cmd_code\":\"set_text\",\"type\":\"label\",\"widget\":\"%s\",\"text\":\"\"}>ET\n       ",BATEERY_TEMP_ERROR);
	}
}

void compute_bms_current_error(uint8_t error)
{
	if(error>0)
	{
		if((error&overcurrent_in_charge)==overcurrent_in_charge)
		{
			printf("ST<{\"cmd_code\":\"set_text\",\"type\":\"label\",\"widget\":\"%s\",\"text\":\"Overcurrent in charge\"}>ET\n    ",BATTERY_CURRENT_ERROR);
		}

		if((error&overcurrent_in_discharge)==overcurrent_in_discharge)
		{
			printf("ST<{\"cmd_code\":\"set_text\",\"type\":\"label\",\"widget\":\"%s\",\"text\":\"Overcurrent in discharge\"}>ET\n    ",BATTERY_CURRENT_ERROR);
		}

	}
	else
	{
		printf("ST<{\"cmd_code\":\"set_text\",\"type\":\"label\",\"widget\":\"%s\",\"text\":\"\"}>ET\n    ",BATTERY_CURRENT_ERROR);
	}
}
void set_bms_soc(float *soc)
{

	set_value(*soc,BATTERY_SOC_LABEL);
	set_progress_bar(*soc,BATTERY_SOC);
}

void set_bms_ah(float *ah)
{
	set_value(*ah,BATTERY_AH_LABEL);
	set_circular_bar(*ah,BATTERY_AH);
}

void computer_bms_cell_deviation_error(uint8_t error)
{
	if(error>0)
	{
		if((error&single_cell_diff_high)==single_cell_diff_high)
		{
			printf("ST<{\"cmd_code\":\"set_text\",\"type\":\"label\",\"widget\":\"%s\",\"text\":\"Cell Voltage Difference High\"}>ET\n   ",BATTERY_CELL_DIV_ERROR);
		}

	}
	else
	{
		printf("ST<{\"cmd_code\":\"set_text\",\"type\":\"label\",\"widget\":\"%s\",\"text\":\"\"}>ET\n    ",BATTERY_CELL_DIV_ERROR);
	}

}

void computer_motor_error_rh(uint16_t error_code)
{
	uint16_t temp;
	for(uint16_t i=0;i<16;i++)
	{
		temp=(error_code>>i)&0x0001;
		if(temp==1)
		{
			printf("ST<{\"cmd_code\":\"set_visible\",\"type\":\"widget\",\"widget\":\"%s\",\"visible\":true}>ET\n       ",err_rh[i]);
		}
		else
		{
			printf("ST<{\"cmd_code\":\"set_visible\",\"type\":\"widget\",\"widget\":\"%s\",\"visible\":false}>ET\n      ",err_rh[i]);

		}
	}
}

void computer_motor_error_lh(uint16_t error_code)
{
	uint16_t temp;
	for(uint16_t i=0;i<16;i++)
	{
		temp=(error_code>>i)&0x0001;
		if(temp==1)
		{
		   printf("ST<{\"cmd_code\":\"set_visible\",\"type\":\"widget\",\"widget\":\"%s\",\"visible\":true}>ET\n      ",err_lh[i]);
		}
		else
		{
		   printf("ST<{\"cmd_code\":\"set_visible\",\"type\":\"widget\",\"widget\":\"%s\",\"visible\":false}>ET\n     ",err_lh[i]);
		}
	}
}

