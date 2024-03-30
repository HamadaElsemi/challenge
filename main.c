/*
 * main.c
 *
 *  Created on: Mar 24, 2024
 *      Author: Eng Hamada Ahmed
 */


/*************************LIB**************************/
#include "LIB/BIT_MATH.h"
#include "LIB/STD_TYPES.h"

/*************************MCAL*************************/
#include "MCAL/DIO/DIO_Interface.h"
#include "MCAL/DIO/DIO_Config.h"
#include "MCAL/DIO/DIO_Private.h"


#include "MCAL/ADC/ADC_Private.h"
#include "MCAL/ADC/ADC_Config.h"
#include "MCAL/ADC/ADC_Interface.h"

#include "MCAL/EXTI/EXTI_Private.h"
#include "MCAL/GIE/GIE_Interface.h"

#include "MCAL/TIMERS/TIMERS_Config.h"
#include "MCAL/TIMERS/TIMERS_Interface.h"
#include "MCAL/TIMERS/TIMERS_Private.h"


/*************************HAL**************************/
#include "HAL/LCD/LCD_Interface.h"
#include "HAL/KPD/KPD_Interface.h"
#include "HAL/LM35/LM35_Interface.h"
#include "HAL/LM35/LM35_Config.h"
#include "HAL/LM35/LM35_Private.h"

#include "HAL/DC_Motor/DcMotor_Interface.h"

/*************************Delay*************************/
#include <util/delay.h>


/***********************Global Variables******************
 * Mode 0 : 0
 * Mode 1 : 1
 * Mode 2 : 2
 * Mode 3 : 3
 ********************************************************/
u8 Mode_Select=0;

void Handle_EXTI0(void){
	     if(Mode_Select == 0){
	    	 /*Mode 0: No Interrupts*/
	     }
	     else if (Mode_Select == 1){
	    	 /* Mode 1: Enable EXTI0 : Toggle LED0*/
	    	 Toggle_BIT(PORTB,pin0);
	     }

	     else if(Mode_Select == 2){
	    	 /* Mode 2: Enable EXTI0 : SET LED0*/
	    	 DIO_Vid_SetPinValue(Port_B,pin0,PinHigh);
	     }
	     else if(Mode_Select == 3){
	    	 /* Mode 3: Enable EXTI0 : Toggle LED0*/
	    	 Toggle_BIT(PORTB,pin0);
	     }

	     else{
	    	           /*Nothing*/
	     }

}

void Handle_EXTI1(void){


	/*clear EXTI 1 flag */
	SET_BIT(GIFR, GIFR_INTF1);

	 if(Mode_Select == 0){
		    	 /*Mode 0: No Interrupts*/
		     }
	else if (Mode_Select == 1){
		    	 /*Nothing By EXTI1*/
		     }

     else if(Mode_Select == 2){
		    	 /* Mode 2: Enable EXTI0 : Clear LED0*/
		    	 DIO_Vid_SetPinValue(Port_B,pin0,PinLow);
		     }
     else if(Mode_Select == 3){
		    	 /* Mode 3: Enable EXTI0 : Toggle LED1*/
		    	 Toggle_BIT(PORTB,pin1);
		     }

	  else{
		    	           /*Nothing*/
		     }

}



int main(){

	/**************************************LCD*********************************/
	DIO_Vid_SetPortDirection(Port_C,output);
	DIO_Vid_SetPinDirection(Port_D,pin5,output);
	DIO_Vid_SetPinDirection(Port_D,pin6,output);
	DIO_Vid_SetPinDirection(Port_D,pin7,output);
	LCD_Vid_Init();

	/**************************************ADC*********************************/
	DIO_Vid_SetPinDirection(Port_A,pin0,input);
	ADC_voidInit();

	/***************************************Interrupts*************************/

	DIO_Vid_SetPinDirection(Port_D,pin2,input);  //INT0
	DIO_Vid_SetPinDirection(Port_D,pin3,input);  //INT1
	GIE_VidEn();
	EXTI_voidInit();


	/*****************************************LED*******************************/
	DIO_Vid_SetPinDirection(Port_B,pin0,output);
	DIO_Vid_SetPinDirection(Port_B,pin1,output);
	DIO_Vid_SetPinValue(Port_B,pin1,PinLow);
	DIO_Vid_SetPinValue(Port_B,pin0,PinLow);

	 EXTI_u8Int0SetCallBack(Handle_EXTI0);
	 EXTI_u8Int1SetCallBack(Handle_EXTI1);


	 LCD_vid_GoTo(0,5);
	 LCD_vid_SendString("Welcome!");
	 LCD_vid_GoTo(1,4);
	 LCD_vid_SendString("Challenge 1");

	u16 Local_ADC;

	while(1){

		Local_ADC=ADC_u16GetConversionReading(CHANNEL0);
		/*NOTE: Local_ADC = Vin *(1024/Vref)
		 * Vin:From voltmeter
		 * Vref=2.56V
		 *
		 * MODE0: Vin=1.67V  --> Local_ADC = 668
		 * MODE1: Vin=2.38V  --> Local_ADC = 952
		 * MODE2: Vin=0.42V  --> Local_ADC = 168
		 * MODE3: Vin=2.14V  --> Local_ADC = 856
		 *
		 *
		 * */
		                           /*MODE 0*/
	if(Local_ADC>600 && Local_ADC<700){
			GIE_VidDisable();
			LCD_vid_DisplayClear();
			LCD_vid_GoTo(0,1);
			LCD_vid_SendString("MODE 0");
			LCD_vid_GoTo(1,0);
			LCD_vid_SendString("No Maskable");
			Mode_Select=0;
		}
									/*MODE 1*/
	else if(Local_ADC>900 && Local_ADC<1000 ){

			GIE_VidEn();
			LCD_vid_DisplayClear();
			LCD_vid_GoTo(0,1);
			LCD_vid_SendString("MODE 1");
			LCD_vid_GoTo(1,1);
			LCD_vid_SendString("EXTI 0");
			Mode_Select=1;
		}
                                   /*MODE 2*/
	else if(Local_ADC>160 && Local_ADC <200){
			GIE_VidEn();
		    LCD_vid_DisplayClear();
			LCD_vid_GoTo(0,1);
			LCD_vid_SendString("MODE 2");
			LCD_vid_GoTo(1,1);
			LCD_vid_SendString("EXTI 0 , EXTI 1");
			Mode_Select=2;
		}
	                             /*MODE 3*/
	else if(Local_ADC>800 && Local_ADC <900){
		GIE_VidEn();
		LCD_vid_DisplayClear();
		LCD_vid_GoTo(0,1);
		LCD_vid_SendString("MODE 3");
		LCD_vid_GoTo(1,1);
		LCD_vid_SendString("EXTI 0 , EXTI 1");
		Mode_Select=3;
	}
	else{
		                    /*Nothing*/
	}


	}
	return 0;
}
