/*
 * TIMERS_Interface.h
 *
 *  Created on: Mar 27, 2024
 *      Author: Ibrahim
 */

#ifndef MCAL_TIMERS_TIMERS_INTERFACE_H_
#define MCAL_TIMERS_TIMERS_INTERFACE_H_


/*********************GENERAL MACROS*******************/
/*Define Indexes for global pointer to function for ISR*/
#define	TIMER0_OVF_VECTOR_ID 		11
#define	TIMER0_CTC_VECTOR_ID 		10

#define	TIMER1_OVF_VECTOR_ID 		9
#define	TIMER1_CTCB_VECTOR_ID 		8
#define	TIMER1_CTCA_VECTOR_ID 		7
#define	TIMER1_ICU_VECTOR_ID 		6

#define	TIMER2_OVF_VECTOR_ID 		5
#define	TIMER2_CTC_VECTOR_ID 		4

/******************FUNCTIONS PROTOTYPES***************/
/******************TIM0************************/
void TIMER0_voidInit(void);
void TIMER0_voidSetPreload(u8 copy_u8Preload);
void TIMER0_voidSetCTC(u8 copy_u8CTC);
void TIMER0_voidSetFastPWM(u8 copy_u8PWM);
void TIMER0_voidSetPhaseCorrectPWM(u8 copy_u8PWM);
u8 TIMER0_u8GetTimerCounterValue(void);


/******************TIM1************************/
void TIMER1_voidInit(void);
void TIMER1_voidSetPreload(u16 copy_u8Preload);
void TIMER1_voidSetCTCA(u16 copy_u8CTCA);
void TIMER1_voidSetCTCB(u16 copy_u8CTCB);

u16 TIMER1_u8GetTimerCounterValue(void);



/******************TIM2************************/
void TIMER2_voidInit(void);
void TIMER2_voidSetPreload(u8 copy_u8Preload);
void TIMER2_voidSetCTC(u8 copy_u8CTC);
void TIMER2_voidSetFastPWM(u8 copy_u8PWM);
void TIMER2_voidSetPhaseCorrectPWM(u8 copy_u8PWM);
u8 TIMER2_u8GetTimerCounterValue(void);


/**********************************************/
u8 TIMER_u8SetCallBack(void(*copy_ptfCallBackFunc)(void),u8 copy_u8VectorID);


#endif /* MCAL_TIMERS_TIMERS_INTERFACE_H_ */
