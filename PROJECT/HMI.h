/*
 * HMI.h
 *
 *  Created on: Jul 2, 2022
 *      Author: samar
 */

#ifndef HMI_H_
#define HMI_H_

/*Battery Monitor Assets*/
#define BATTERY_VOLTAGE           "B2"
#define BATTERY_CURRENT           "C2"
#define BATTERY_TEMPERATURE1      "T1_2"
#define BATTERY_TEMPERATURE2      "T2_2"
#define BATTERY_TEMPERATURE3      "T3_2"
#define BATTERY_TEMPERATURE4      "T4_2"
#define BATTERY_CELL_MAX_VOLATGE  "MAXV_2"
#define BATTERY_CELL_MIN_VOLATGE  "MINV_2"
#define BATTERY_SOC               "soc_bar"
#define BATTERY_AH				  "ah_circle"
#define BATTERY_CELL_ERROR        "BE_1"
#define BATTERY_CURRENT_ERROR	  "BE_2"
#define BATEERY_TEMP_ERROR		  "BE_3"
#define BATTERY_CELL_DIV_ERROR    "BE_4"
#define BATTERY_SOC_LABEL         "soc_label"
#define BATTERY_AH_LABEL          "ah_label"
/*Motor Monitor Assets*/
#define RH_MOTOR_VOLATGE          "rhv_2"
#define RH_MOTOR_CURRENT          "rhc_2"
#define RH_MOTOR_RPM              "rhrpm_2"
#define RH_MOTOR_TEMPERATURE      "rht_2"
#define RH_MOTOR_ERROR_0		  "rhe0"
#define RH_MOTOR_ERROR_1		  "rhe1"
#define RH_MOTOR_ERROR_2		  "rhe2"
#define RH_MOTOR_ERROR_3		  "rhe3"
#define RH_MOTOR_ERROR_4		  "rhe4"
#define RH_MOTOR_ERROR_5		  "rhe5"
#define RH_MOTOR_ERROR_6		  "rhe6"
#define RH_MOTOR_ERROR_7		  "rhe7"
#define RH_MOTOR_ERROR_8		  "rhe8"
#define RH_MOTOR_ERROR_9		  "rhe9"
#define RH_MOTOR_ERROR_10		  "rhe10"
#define RH_MOTOR_ERROR_11		  "rhe11"
#define RH_MOTOR_ERROR_12		  "rhe12"
#define RH_MOTOR_ERROR_13		  "rhe13"
#define RH_MOTOR_ERROR_14		  "rhe14"
#define RH_MOTOR_ERROR_15		  "rhe15"

#define LH_MOTOR_VOLATGE          "lhv_2"
#define LH_MOTOR_CURRENT          "lhc_2"
#define LH_MOTOR_RPM              "lhrpm_2"
#define LH_MOTOR_TEMPERATURE      "lht_2"
#define LH_MOTOR_ERROR_0		  "lhe0"
#define LH_MOTOR_ERROR_1		  "lhe1"
#define LH_MOTOR_ERROR_2		  "lhe2"
#define LH_MOTOR_ERROR_3		  "lhe3"
#define LH_MOTOR_ERROR_4		  "lhe4"
#define LH_MOTOR_ERROR_5		  "lhe5"
#define LH_MOTOR_ERROR_6		  "lhe6"
#define LH_MOTOR_ERROR_7		  "lhe7"
#define LH_MOTOR_ERROR_8		  "lhe8"
#define LH_MOTOR_ERROR_9		  "lhe9"
#define LH_MOTOR_ERROR_10		  "lhe10"
#define LH_MOTOR_ERROR_11		  "lhe11"
#define LH_MOTOR_ERROR_12		  "lhe12"
#define LH_MOTOR_ERROR_13		  "lhe13"
#define LH_MOTOR_ERROR_14		  "lhe14"
#define LH_MOTOR_ERROR_15		  "lhe15"


enum
{
	single_cell_voltage_high=0x02,
	single_cell_voltage_low=0x04,
	temperature_high_charge=0x02,
	temperatue_low_charge=0x04,
	temperature_high_discharge=0x20,
	temperature_low_discharge=0x40,
	overcurrent_in_charge=0x02,
	overcurrent_in_discharge=0x04,
	single_cell_diff_high=0x02,

};

void set_value(float value,char widget_name[]);
void set_text(char text[],char widget_name[]);
void set_progress_bar(float value,char widget_name[]);
void set_circular_bar(float value,char widget_name[]);

void computer_bms_cell_error(uint8_t error);
void computer_bms_temperature_error(uint8_t error);
void compute_bms_current_error(uint8_t error);
void computer_bms_cell_deviation_error(uint8_t error);
void computer_motor_error_rh(uint16_t error_code);
void computer_motor_error_lh(uint16_t error_code);

#endif /* HMI_H_ */
