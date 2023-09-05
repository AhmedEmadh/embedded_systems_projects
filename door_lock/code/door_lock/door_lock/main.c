//#include "Service/RTOS/FreeRTOS.h"
//#include "Service/RTOS/task.h"
#include "LIB/std_types.h"
#include "LIB/bit_math.h"
#include "MCAL/DIO/DIO_interface.h"
//#include "Service/RTOS/semphr.h"
#include "HAL/KPD/KPD_interface.h"
#include "HAL/LCD/LCD_interface.h"
#include "MCAL/TIMERS/TIMERS_interface.h"
#include "MCAL/GI/GI_interface.h"
#include "HAL/DCM/DCM_interface.h"
#include "HAL/SERVO/SERVO_interface.h"
#define F_CPU 1000000UL
#include "util/delay.h"

#define MAX_IN_PASSWORD_SIZE 16

void getInputFromUser(u8 *Copy_pu8ReturnedInput,u8 *Copy_pu8PrintedMessage);
void PrintToUser(u8 *Copy_pu8PrintedString);
u8 is_str_equal(u8 *Copy_pu8Str1,u8 *Copy_pu8Str2);
void open_door();
void close_door();
void PrintToUser_const(const u8 *Copy_pu8PrintedString);
void getInputFromUser_const(u8 *Copy_pu8ReturnedInput,const u8 *Copy_pu8PrintedMessage);
void unlock_the_lock();
void lock_the_lock();
/*********************************************          main                 *****************************/
int main(void){/*startup code*/
	_delay_ms(100);
	DIO_voidInit();
	LCD_voidInit();
	TIMERS_voidTimer1Init();
	GI_voidEnable();
	
	u8 correctPassword[] = "1234";
	u8 input[MAX_IN_PASSWORD_SIZE];
	
	while(1){/* Looping code */
		/* ask user to enter the password */
		getInputFromUser_const(input,(const u8*)"Enter Password");
		/* check if the entered password equals the correct password */
		if(is_str_equal(input,correctPassword)){
			/* if the password is correct then open the door for while then close it */
			PrintToUser_const((const u8*)"opening...");
			unlock_the_lock();
			open_door();
			PrintToUser_const((const u8*)"door opened");
			_delay_ms(10000);
			PrintToUser_const((const u8*)"closing...");
			close_door();
			lock_the_lock();
			PrintToUser_const((const u8*)"door closed");
			}else{
			/* if incorrect password then print it */
			PrintToUser_const((const u8*)"Incorrect Pass");
		}
		_delay_ms(2000);
	}
	return 0;
}
/*********************************************          End main                 *****************************/
void PrintToUser(u8 *Copy_pu8PrintedString){
	LCD_u8SetPos(LCD_u8_LINE1,0);
	LCD_u8SendString(Copy_pu8PrintedString);
}
void PrintToUser_const(const u8 *Copy_pu8PrintedString){
	LCD_u8SetPos(LCD_u8_LINE1,0);
	LCD_voidClear();
	LCD_u8SendString_const(Copy_pu8PrintedString);
}
u8 is_str_equal(u8 *Copy_pu8Str1,u8 *Copy_pu8Str2){
	u8 Local_u8Counter = 0;
	u8 Local_u8ReturnedIsEqual = 0;
	while(Copy_pu8Str1[Local_u8Counter] != '\0'){
		if(Copy_pu8Str1[Local_u8Counter] != Copy_pu8Str2[Local_u8Counter]){
			break;
		}
		Local_u8Counter++;
	}
	if((Copy_pu8Str1[Local_u8Counter] == Copy_pu8Str2[Local_u8Counter])&&(Copy_pu8Str1[Local_u8Counter] == '\0')){
		Local_u8ReturnedIsEqual = 1;
		}else{
		Local_u8ReturnedIsEqual = 0;
	}
	return Local_u8ReturnedIsEqual;
	
}
void getInputFromUser(u8 *Copy_pu8ReturnedInput,u8 *Copy_pu8PrintedMessage){
	u8 Local_u8EnteredKey = KPD_u8_Key_Not_Pressed;
	u8 Local_u8Counter = 0;
	/* print message */
	LCD_voidClear();
	LCD_u8SetPos(LCD_u8_LINE1,0);
	/*wait for changes to take effect*/
	_delay_ms(2);
	/* go to input line to read input */
	LCD_u8SendString(Copy_pu8PrintedMessage);
	LCD_u8SetPos(LCD_u8_LINE2,0);
	/*read keypad*/
	Local_u8Counter = 0;
	while(Local_u8EnteredKey != '='){
		/* key != ok*/
		KPD_u8GetKeyStatus(&Local_u8EnteredKey);
		if((Local_u8EnteredKey >= '0')&&(Local_u8EnteredKey<='9')){/* key is a number */
			Copy_pu8ReturnedInput[Local_u8Counter] = Local_u8EnteredKey;
			LCD_voidSendChar(Local_u8EnteredKey);
			Local_u8Counter++;
			Local_u8EnteredKey = KPD_u8_Key_Not_Pressed;
		}
		}/* exited while when the user pressed OK ('+') */
		Copy_pu8ReturnedInput[Local_u8Counter] = '\0';
		LCD_voidClear();
		_delay_ms(2);
	}
	void getInputFromUser_const(u8 *Copy_pu8ReturnedInput,const u8 *Copy_pu8PrintedMessage){
		u8 Local_u8EnteredKey = KPD_u8_Key_Not_Pressed;
		u8 Local_u8Counter = 0;
		/* print message */
		LCD_voidClear();
		LCD_u8SetPos(LCD_u8_LINE1,0);
		/*wait for changes to take effect*/
		_delay_ms(2);
		/* go to input line to read input */
		LCD_u8SendString_const(Copy_pu8PrintedMessage);
		LCD_u8SetPos(LCD_u8_LINE2,0);
		/*read keypad*/
		Local_u8Counter = 0;
		while((Local_u8EnteredKey != '=')&&(Local_u8Counter<MAX_IN_PASSWORD_SIZE)){
			/* key != ok*/
			KPD_u8GetKeyStatus(&Local_u8EnteredKey);
			if((Local_u8EnteredKey >= '0')&&(Local_u8EnteredKey<='9')){/* key is a number */
				Copy_pu8ReturnedInput[Local_u8Counter] = Local_u8EnteredKey;
				LCD_voidSendChar(Local_u8EnteredKey);
				Local_u8Counter++;
				Local_u8EnteredKey = KPD_u8_Key_Not_Pressed;
				}else if((Local_u8EnteredKey == '=')&&(Local_u8Counter == 0)){
				Local_u8EnteredKey = '\0';
			}
			}/* exited while when the user pressed OK ('+') */
			Copy_pu8ReturnedInput[Local_u8Counter] = '\0';
			LCD_voidClear();
			_delay_ms(2);
		}
		void open_door(){
			DCM_voidTurnRight();
			_delay_ms(2000);
			DCM_voidTurnOff();
		}
		void close_door(){
			DCM_voidTurnLeft();
			_delay_ms(2000);
			DCM_voidTurnOff();
		}
		void unlock_the_lock(){
			set_angle(180);
			_delay_ms(300);
		}
		void lock_the_lock(){
			set_angle(0);
			_delay_ms(300);
		}