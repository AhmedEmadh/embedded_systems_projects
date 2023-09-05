/*
 * SERVO_program.c
 *
 * Created: 9/5/2023 3:26:53 PM
 *  Author: Ahmed
 */ 
/* include from lib */
#include "../../lib/std_types.h"
#include "../../lib/bit_math.h"
#include "../../lib/num_str_conv.h"
/* include from DIO */
#include "../../MCAL/DIO/DIO_interface.h"
/* include from TIMERS */
#include "../../MCAL/TIMERS/TIMERS_interface.h"
#include "../../MCAL/TIMERS/TIMERS_private.h"
/* include from SERVO */
#include "SERVO_private.h"
#include "SERVO_config.h"
#include "SERVO_interface.h"
void set_angle(u8 Copy_u8Angle){
	TIMERS_u16_OCR1A_REG = (u16)(((Copy_u8Angle/180.0)*2000) + 499);
}