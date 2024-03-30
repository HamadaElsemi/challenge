/*
 * TIMERS_Program.c
 *
 *  Created on: Mar 27, 2024
 *      Author: Ibrahim
 */


/******************LIB**********************/
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_Types.h"

/******************MCAL*********************/
#include "TIMERS_Config.h"
#include "TIMERS_Interface.h"
#include "TIMERS_Private.h"


/**********Global pointer to array of functions***/
static void(*TIMERS_ptfCallBackFuncArr[8])(void)={NULL};

/*****************************************************/
/******************FUNCTIONS DEFINITIONS***************/
/*****************************************************/
/**************************************************************************************/
/*											TIM0									  */
/**************************************************************************************/

void TIMER0_voidInit(void)
{
	/*Set Configurable Modes*/
#if TIMER0_WAVEFORM_GENERATION_MODE == TIMER_NORMAL_MODE

	/*Initialize Waveform Generation Mode as Normal Mode*/
	CLR_BIT(TCCR0 , TCCR0_WGM00) ;
	CLR_BIT(TCCR0 , TCCR0_WGM01) ;

	/*Set the Required Preload Value*/
	TCNT0 = TIMER0_PRELOAD_VAL ;

	/*Timer0 Overflow Interrupt Enable*/
#if TIMER0_OVERFLOW_INTERRUPT == DISABLE
	CLR_BIT(TIMSK , TIMSK_TOIE0) ;
#elif TIMER0_OVERFLOW_INTERRUPT == ENABLE
	SET_BIT(TIMSK , TIMSK_TOIE0) ;
#else
#error "Wrong TIMER0_OVERFLOW_INTERRUPT Config"
#endif

#elif TIMER0_WAVEFORM_GENERATION_MODE == TIMER_PWM_MODE
	/*Initialize Waveform Generation Mode as PWM Mode*/
	SET_BIT(TCCR0 , TCCR0_WGM00) ;
	CLR_BIT(TCCR0 , TCCR0_WGM01) ;

	/*Set CTC PWM MODE*/
#if TIMER0_CTC_PWM_MODE == TIMER_OC_DISCONNECTED
	CLR_BIT(TCCR0 , TCCR0_COM00) ;
	CLR_BIT(TCCR0 , TCCR0_COM01) ;
#elif TIMER0_CTC_PWM_MODE == TIMER_CLR_ON_CTC_SET_ON_TOP
	CLR_BIT(TCCR0 , TCCR0_COM00) ;
	SET_BIT(TCCR0 , TCCR0_COM01) ;
#elif TIMER0_CTC_PWM_MODE == TIMER_SET_ON_CTC_CLR_ON_TOP
	SET_BIT(TCCR0 , TCCR0_COM00) ;
	SET_BIT(TCCR0 , TCCR0_COM01) ;
#else
#error "Wrong TIMER0_CTC_PWM_MODE Config"
#endif

	/*Set the Required CTC Value*/
	OCR0 = TIMER0_CTC_VAL ;

#elif TIMER0_WAVEFORM_GENERATION_MODE == TIMER_CTC_MODE

	/*Initialize Waveform Generation Mode as CTC Mode*/
	CLR_BIT(TCCR0 , TCCR0_WGM00) ;
	SET_BIT(TCCR0 , TCCR0_WGM01) ;

	/*Set the Required CTC Value*/
	OCR0 = TIMER0_CTC_VAL ;

	/*Timer0 Compare Match Interrupt Enable*/
#if TIMER0_CTC_INTERRUPT == DISABLE
	CLR_BIT(TIMSK , TIMSK_OCIE0) ;
#elif TIMER0_CTC_INTERRUPT == ENABLE
	SET_BIT(TIMSK , TIMSK_OCIE0) ;
#else
#error "Wrong TIMER0_OVERFLOW_INTERRUPT Config"
#endif


	/*Set CTC PWM MODE*/
#if TIMER0_OC0_MODE == TIMER_OC_DISCONNECTED
	CLR_BIT(TCCR0 , TCCR0_COM00) ;
	CLR_BIT(TCCR0 , TCCR0_COM01) ;
#elif TIMER0_OC0_MODE == TIMER_OC_TOGGEL
	CLR_BIT(TCCR0 , TCCR0_COM01) ;
	SET_BIT(TCCR0 , TCCR0_COM00) ;
#elif TIMER0_OC0_MODE == TIMER_OC_LOW
	CLR_BIT(TCCR0 , TCCR0_COM00) ;
	SET_BIT(TCCR0 , TCCR0_COM01) ;
#elif TIMER0_OC0_MODE == TIMER_OC_HIGH
	SET_BIT(TCCR0 , TCCR0_COM00) ;
	SET_BIT(TCCR0 , TCCR0_COM01) ;
#else
#error "Wrong TIMER0_OC0_MODE Configuration parameter!"
#endif

#elif TIMER0_WAVEFORM_GENERATION_MODE == TIMER_FAST_PWM_MODE

	/*Initialize Waveform Generation Mode as Fast PWM Mode*/
	SET_BIT(TCCR0 , TCCR0_WGM00) ;
	SET_BIT(TCCR0 , TCCR0_WGM01) ;

	/*Set CTC Fast PWM MODE*/
#if TIMER0_CTC_PWM_MODE == TIMER_OC_DISCONNECTED
	CLR_BIT(TCCR0 , TCCR0_COM00) ;
	CLR_BIT(TCCR0 , TCCR0_COM01) ;
#elif TIMER0_CTC_PWM_MODE == TIMER_CLR_ON_CTC_SET_ON_TOP
	CLR_BIT(TCCR0 , TCCR0_COM00) ;
	SET_BIT(TCCR0 , TCCR0_COM01) ;
#elif TIMER0_CTC_PWM_MODE == TIMER_SET_ON_CTC_CLR_ON_TOP
	SET_BIT(TCCR0 , TCCR0_COM00) ;
	SET_BIT(TCCR0 , TCCR0_COM01) ;
#else
#error "Wrong TIMER0_CTC_PWM_MODE Config"
#endif

	/*Set the Required CTC Value*/
	OCR0 = TIMER0_CTC_VAL ;

#else
#error "Wrong TIMER0_WAVEFORM_GENERATION_MODE Config"

#endif

	/*Set the Required Prescaler*/
	TCCR0 &= TIMER_PRESCALER_MASK ;
	TCCR0 |= TIMER0_PRESCALER ;
}

void TIMER0_voidSetPreload(u8 copy_u8Preload)
{
	TCNT0 = copy_u8Preload ;
}

void TIMER0_voidSetCTC(u8 copy_u8CTC)
{
	OCR0 = copy_u8CTC ;
}


void TIMER0_voidSetFastPWM(u8 copy_u8PWM)
{
#if TIMER0_WAVEFORM_GENERATION_MODE == TIMER_FAST_PWM_MODE
	/*Set the Required CTC Value*/
	OCR0 = copy_u8PWM ;
#endif
}


void TIMER0_voidSetPhaseCorrectPWM(u8 copy_u8PWM)
{
#if TIMER0_WAVEFORM_GENERATION_MODE == TIMER_PWM_MODE
	/*Set the Required CTC Value*/
	OCR0 = copy_u8PWM ;
#endif
}

u8 TIMER0_u8GetTimerCounterValue(void)
{

	return TCNT0 ;
}




/**************************************************************************************/
/*											TIM1									  */
/**************************************************************************************/
void TIMER1_voidInit(void)
{
	/*Set Configurable Modes*/

#if TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_NORMAL_MODE

	/*Set Waveform generation mode as Normal mode */
	CLR_BIT(TCCR1A,TCCR1A_WGM10);
	CLR_BIT(TCCR1A,TCCR1A_WGM11);
	CLR_BIT(TCCR1B,TCCR1B_WGM12);
	CLR_BIT(TCCR1B,TCCR1B_WGM13);

	/*Set the require Preload Value*/
	TCNT1 = TIMER1_PRELOAD_VAL ;

	/*Timer1 Overflow Interrupt Enable*/
#if TIMER1_OVERFLOW_INTERRUPT == DISABLE
	CLR_BIT(TIMSK , TIMSK_TOIE1) ;
#elif TIMER1_OVERFLOW_INTERRUPT == ENABLE
	SET_BIT(TIMSK , TIMSK_TOIE1) ;
#else
#error "Wrong TIMER1_OVERFLOW_INTERRUPT Config"
#endif

#elif (TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_CTC_OCR1A_MODE) || (TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_CTC_ICR1_MODE)

	/*Set Waveform generation mode as CTC modes */
#if TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_CTC_ICR1_MODE
	CLR_BIT(TCCR1A,TCCR1A_WGM10);
	CLR_BIT(TCCR1A,TCCR1A_WGM11);
	SET_BIT(TCCR1B,TCCR1B_WGM12);
	SET_BIT(TCCR1B,TCCR1B_WGM13);
#elif TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_CTC_OCR1A_MODE
	CLR_BIT(TCCR1A,TCCR1A_WGM10);
	CLR_BIT(TCCR1A,TCCR1A_WGM11);
	SET_BIT(TCCR1B,TCCR1B_WGM12);
	CLR_BIT(TCCR1B,TCCR1B_WGM13);
#else
#error "Wrong TIMER1_WAVEFORM_GENERATION_MODE Config"
#endif

	/*Set the require CTC Values*/
	OCR1A = TIMER1_CTCA_VAL ;
	OCR1B = TIMER1_CTCB_VAL ;

	/*Set ICR1 if TIMER1_CTC_OCR1A_MODE = TIMER1_CTC_ICR1_MODE*/
#if TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_CTC_ICR1_MODE
	ICR1 = TIMER1_ICR1_VAL ;

#if TIMER1_ICR_EDGE == RISING_EDGE
	SET_BIT(TCCR1B , TCCR1B_ICES1) ;
#elif TIMER1_ICR_EDGE == FALLING_EDGE
	CLR_BIT(TCCR1B , TCCR1B_ICES1) ;
#else
#error "Wrong TIMER1_ICR_EDGE Config"
#endif

#else
	/*Do nothing*/
#endif

	/*Set OCR1A mode*/
#if TIMER1_OCR1A_MODE == TIMER_OC_DISCONNECTED
	CLR_BIT(TCCR1A , TCCR1A_COM1A0) ;
	CLR_BIT(TCCR1A , TCCR1A_COM1A1) ;
#elif TIMER1_OCR1A_MODE == TIMER_OC_TOGGEL
	SET_BIT(TCCR1A , TCCR1A_COM1A0) ;
	CLR_BIT(TCCR1A , TCCR1A_COM1A1) ;
#elif TIMER1_OCR1A_MODE == TIMER_OC_LOW
	CLR_BIT(TCCR1A , TCCR1A_COM1A0) ;
	SET_BIT(TCCR1A , TCCR1A_COM1A1) ;
#elif TIMER1_OCR1A_MODE == TIMER_OC_HIGH
	SET_BIT(TCCR1A , TCCR1A_COM1A0) ;
	SET_BIT(TCCR1A , TCCR1A_COM1A1) ;
#else
#error "Wrong TIMER1_OCR1A_MODE Config"
#endif

	/*Set OCR1B mode*/
#if TIMER1_OCR1B_MODE == TIMER_OC_DISCONNECTED
	CLR_BIT(TCCR1A , TCCR1A_COM1B0) ;
	CLR_BIT(TCCR1A , TCCR1A_COM1B1) ;
#elif TIMER1_OCR1B_MODE == TIMER_OC_TOGGEL
	SET_BIT(TCCR1A , TCCR1A_COM1B0) ;
	CLR_BIT(TCCR1A , TCCR1A_COM1B1) ;
#elif TIMER1_OCR1B_MODE == TIMER_OC_LOW
	CLR_BIT(TCCR1A , TCCR1A_COM1B0) ;
	SET_BIT(TCCR1A , TCCR1A_COM1B1) ;
#elif TIMER1_OCR1B_MODE == TIMER_OC_HIGH
	SET_BIT(TCCR1A , TCCR1A_COM1B0) ;
	SET_BIT(TCCR1A , TCCR1A_COM1B1) ;
#else
#error "Wrong TIMER1_OCR1B_MODE Config"
#endif

	/*Timer1 CTC Interrupt Enable*/
#if TIMER1_CTCA_INTERRUPT == DISABLE
	CLR_BIT(TIMSK , TIMSK_OCIE1A) ;
#elif TIMER1_CTCA_INTERRUPT == ENABLE
	SET_BIT(TIMSK , TIMSK_OCIE1A) ;
#else
#error "Wrong TIMER1_CTCA_INTERRUPT Config"
#endif

#if TIMER1_CTCB_INTERRUPT == DISABLE
	CLR_BIT(TIMSK , TIMSK_OCIE1B) ;
#elif TIMER1_CTCB_INTERRUPT == ENABLE
	SET_BIT(TIMSK , TIMSK_OCIE1B) ;
#else
#error "Wrong TIMER1_CTCB_INTERRUPT Config"
#endif

#elif (TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_PWM_PHASE_CORRECT_OCR1A_MODE) || (TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_PWM_PHASE_CORRECT_ICR1_MODE) || (TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_PWM_PHASE_AND_FREQ_CORRECT_OCR1A_MODE) ||(TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_PWM_PHASE_AND_FREQ_CORRECT_ICR1_MODE) || (TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_PWM_10_BIT_MODE) || (TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_PWM_9_BIT_MODE) || (TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_PWM_8_BIT_MODE)

	/*Set Waveform generation mode as PWM modes */
#if TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_PWM_PHASE_CORRECT_OCR1A_MODE
	SET_BIT(TCCR1A,TCCR1A_WGM10);
	SET_BIT(TCCR1A,TCCR1A_WGM11);
	CLR_BIT(TCCR1B,TCCR1B_WGM12);
	SET_BIT(TCCR1B,TCCR1B_WGM13);
#elif TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_PWM_PHASE_CORRECT_ICR1_MODE
	CLR_BIT(TCCR1A,TCCR1A_WGM10);
	SET_BIT(TCCR1A,TCCR1A_WGM11);
	CLR_BIT(TCCR1B,TCCR1B_WGM12);
	CLR_BIT(TCCR1B,TCCR1B_WGM13);
#elif TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_PWM_PHASE_AND_FREQ_CORRECT_OCR1A_MODE
	SET_BIT(TCCR1A,TCCR1A_WGM10);
	CLR_BIT(TCCR1A,TCCR1A_WGM11);
	CLR_BIT(TCCR1B,TCCR1B_WGM12);
	SET_BIT(TCCR1B,TCCR1B_WGM13);
#elif TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_PWM_PHASE_AND_FREQ_CORRECT_ICR1_MODE
	CLR_BIT(TCCR1A,TCCR1A_WGM10);
	CLR_BIT(TCCR1A,TCCR1A_WGM11);
	CLR_BIT(TCCR1B,TCCR1B_WGM12);
	SET_BIT(TCCR1B,TCCR1B_WGM13);
#elif TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_PWM_10_BIT_MODE
	SET_BIT(TCCR1A,TCCR1A_WGM10);
	SET_BIT(TCCR1A,TCCR1A_WGM11);
	CLR_BIT(TCCR1B,TCCR1B_WGM12);
	CLR_BIT(TCCR1B,TCCR1B_WGM13);
#elif TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_PWM_9_BIT_MODE
	CLR_BIT(TCCR1A,TCCR1A_WGM10);
	SET_BIT(TCCR1A,TCCR1A_WGM11);
	CLR_BIT(TCCR1B,TCCR1B_WGM12);
	CLR_BIT(TCCR1B,TCCR1B_WGM13);
#elif TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_PWM_8_BIT_MODE
	SET_BIT(TCCR1A,TCCR1A_WGM10);
	CLR_BIT(TCCR1A,TCCR1A_WGM11);
	CLR_BIT(TCCR1B,TCCR1B_WGM12);
	CLR_BIT(TCCR1B,TCCR1B_WGM13);
#else
#error "Wrong TIMER1_WAVEFORM_GENERATION_MODE Config"
#endif

	/*Set the require CTC Values*/
	OCR1A = TIMER1_CTCA_VAL ;
	OCR1B = TIMER1_CTCB_VAL ;

	/*Set ICR1*/
#if ((TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_PWM_PHASE_CORRECT_ICR1_MODE) || (TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_PWM_PHASE_AND_FREQ_CORRECT_ICR1_MODE))
	ICR1 = TIMER1_ICR1_VAL ;

#if TIMER1_ICR_EDGE == RISING_EDGE
	SET_BIT(TCCR1B , TCCR1B_ICES1) ;
#elif TIMER1_ICR_EDGE == FALLING_EDGE
	CLR_BIT(TCCR1B , TCCR1B_ICES1) ;
#else
#error "Wrong TIMER1_ICR_EDGE Config"
#endif
#else
	/*Do nothing*/
#endif

	/*Set OCR1A mode*/
#if TIMER1_OCR1A_MODE == TIMER_OC_DISCONNECTED
	CLR_BIT(TCCR1A , TCCR1A_COM1A0) ;
	CLR_BIT(TCCR1A , TCCR1A_COM1A1) ;
#elif TIMER1_OCR1A_MODE == TIMER_CLR_ON_CTC_SET_ON_TOP
	CLR_BIT(TCCR1A , TCCR1A_COM1A0) ;
	SET_BIT(TCCR1A , TCCR1A_COM1A1) ;
#elif TIMER1_OCR1A_MODE == TIMER_SET_ON_CTC_CLR_ON_TOP
	SET_BIT(TCCR1A , TCCR1A_COM1A0) ;
	SET_BIT(TCCR1A , TCCR1A_COM1A1) ;
#else
#error "Wrong TIMER1_OCR1A_MODE Config"
#endif

	/*Set OCR1B mode*/
#if TIMER1_OCR1B_MODE == TIMER_OC_DISCONNECTED
	CLR_BIT(TCCR1A , TCCR1A_COM1B0) ;
	CLR_BIT(TCCR1A , TCCR1A_COM1B1) ;
#elif TIMER1_OCR1B_MODE == TIMER_CLR_ON_CTC_SET_ON_TOP
	CLR_BIT(TCCR1A , TCCR1A_COM1B0) ;
	SET_BIT(TCCR1A , TCCR1A_COM1B1) ;
#elif TIMER1_OCR1B_MODE == TIMER_SET_ON_CTC_CLR_ON_TOP
	SET_BIT(TCCR1A , TCCR1A_COM1B0) ;
	SET_BIT(TCCR1A , TCCR1A_COM1B1) ;
#else
#error "Wrong TIMER1_OCR1B_MODE Config"
#endif

	/*Timer1 PWM Interrupt Enable*/
#if TIMER1_OVERFLOW_INTERRUPT == DISABLE
	CLR_BIT(TIMSK , TIMSK_TOIE1) ;
#elif TIMER1_OVERFLOW_INTERRUPT == ENABLE
	SET_BIT(TIMSK , TIMSK_TOIE1) ;
#else
#error "Wrong TIMER1_OVERFLOW_INTERRUPT Config"
#endif

#if TIMER1_CTCA_INTERRUPT == DISABLE
	CLR_BIT(TIMSK , TIMSK_OCIE1A) ;
#elif TIMER1_CTCA_INTERRUPT == ENABLE
	SET_BIT(TIMSK , TIMSK_OCIE1A) ;
#else
#error "Wrong TIMER1_CTCA_INTERRUPT Config"
#endif

#if TIMER1_CTCB_INTERRUPT == DISABLE
	CLR_BIT(TIMSK , TIMSK_OCIE1B) ;
#elif TIMER1_CTCB_INTERRUPT == ENABLE
	SET_BIT(TIMSK , TIMSK_OCIE1B) ;
#else
#error "Wrong TIMER1_CTCB_INTERRUPT Config"
#endif

#if TIMER1_ICR_INTERRUPT == DISABLE
	CLR_BIT(TIMSK , TIMSK_TICIE1) ;
#elif TIMER1_ICR_INTERRUPT == ENABLE
	SET_BIT(TIMSK , TIMSK_TICIE1) ;
#else
#error "Wrong TIMER1_ICR1_INTERRUPT Config"
#endif


#elif (TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_FAST_PWM_OCR1A_MODE) || (TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_FAST_PWM_ICR1_MODE) || (TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_FAST_PWM_10_BIT_MODE) || (TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_FAST_PWM_9_BIT_MODE) || (TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_FAST_PWM_8_BIT_MODE)

	/*Set Waveform generation mode as PWM modes */
#if TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_FAST_PWM_OCR1A_MODE
	SET_BIT(TCCR1A,TCCR1A_WGM10);
	SET_BIT(TCCR1A,TCCR1A_WGM11);
	SET_BIT(TCCR1B,TCCR1B_WGM12);
	SET_BIT(TCCR1B,TCCR1B_WGM13);
#elif TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_FAST_PWM_ICR1_MODE
	CLR_BIT(TCCR1A,TCCR1A_WGM10);
	SET_BIT(TCCR1A,TCCR1A_WGM11);
	SET_BIT(TCCR1B,TCCR1B_WGM12);
	SET_BIT(TCCR1B,TCCR1B_WGM13);
#elif TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_FAST_PWM_10_BIT_MODE
	SET_BIT(TCCR1A,TCCR1A_WGM10);
	SET_BIT(TCCR1A,TCCR1A_WGM11);
	SET_BIT(TCCR1B,TCCR1B_WGM12);
	CLR_BIT(TCCR1B,TCCR1B_WGM13);
#elif TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_FAST_PWM_9_BIT_MODE
	CLR_BIT(TCCR1A,TCCR1A_WGM10);
	SET_BIT(TCCR1A,TCCR1A_WGM11);
	SET_BIT(TCCR1B,TCCR1B_WGM12);
	CLR_BIT(TCCR1B,TCCR1B_WGM13);
#elif TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_FAST_PWM_8_BIT_MODE
	SET_BIT(TCCR1A,TCCR1A_WGM10);
	CLR_BIT(TCCR1A,TCCR1A_WGM11);
	SET_BIT(TCCR1B,TCCR1B_WGM12);
	CLR_BIT(TCCR1B,TCCR1B_WGM13);
#else
#error "Wrong TIMER1_WAVEFORM_GENERATION_MODE Config"
#endif

	/*Set the require CTC Values*/
	OCR1AL = (u8)TIMER1_CTCA_VAL ;
	OCR1AH |= (TIMER1_CTCA_VAL>>8) ;

	OCR1BL = TIMER1_CTCB_VAL ;
	OCR1BH |= (TIMER1_CTCB_VAL>>8) ;
	/*Set ICR1*/
#if TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_FAST_PWM_ICR1_MODE
	ICR1L = (u8)TIMER1_ICR1_VAL ;
	ICR1H = (TIMER1_ICR1_VAL>>8) ;
#if TIMER1_ICR_EDGE == RISING_EDGE
	SET_BIT(TCCR1B , TCCR1B_ICES1) ;
#elif TIMER1_ICR_EDGE == FALLING_EDGE
	CLR_BIT(TCCR1B , TCCR1B_ICES1) ;
#else
#error "Wrong TIMER1_ICR_EDGE Config"
#endif
#else
	/*Do nothing*/
#endif

	/*Set OCR1A mode*/
#if TIMER1_OCR1A_MODE == TIMER_OC_DISCONNECTED
	CLR_BIT(TCCR1A , TCCR1A_COM1A0) ;
	CLR_BIT(TCCR1A , TCCR1A_COM1A1) ;
#elif TIMER1_OCR1A_MODE == TIMER_CLR_ON_CTC_SET_ON_TOP
	CLR_BIT(TCCR1A , TCCR1A_COM1A0) ;
	SET_BIT(TCCR1A , TCCR1A_COM1A1) ;
#elif TIMER1_OCR1A_MODE == TIMER_SET_ON_CTC_CLR_ON_TOP
	SET_BIT(TCCR1A , TCCR1A_COM1A0) ;
	SET_BIT(TCCR1A , TCCR1A_COM1A1) ;
#else
#error "Wrong TIMER1_OCR1A_MODE Config"
#endif

	/*Set OCR1B mode*/
#if TIMER1_OCR1B_MODE == TIMER_OC_DISCONNECTED
	CLR_BIT(TCCR1A , TCCR1A_COM1B0) ;
	CLR_BIT(TCCR1A , TCCR1A_COM1B1) ;
#elif TIMER1_OCR1B_MODE == TIMER_CLR_ON_CTC_SET_ON_TOP
	CLR_BIT(TCCR1A , TCCR1A_COM1B0) ;
	SET_BIT(TCCR1A , TCCR1A_COM1B1) ;
#elif TIMER1_OCR1B_MODE == TIMER_SET_ON_CTC_CLR_ON_TOP
	SET_BIT(TCCR1A , TCCR1A_COM1B0) ;
	SET_BIT(TCCR1A , TCCR1A_COM1B1) ;
#else
#error "Wrong TIMER1_OCR1B_MODE Config"
#endif

	/*Timer1 PWM Interrupt Enable*/
#if TIMER1_OVERFLOW_INTERRUPT == DISABLE
	CLR_BIT(TIMSK , TIMSK_TOIE1) ;
#elif TIMER1_OVERFLOW_INTERRUPT == ENABLE
	SET_BIT(TIMSK , TIMSK_TOIE1) ;
#else
#error "Wrong TIMER1_OVERFLOW_INTERRUPT Config"
#endif

#if TIMER1_CTCA_INTERRUPT == DISABLE
	CLR_BIT(TIMSK , TIMSK_OCIE1A) ;
#elif TIMER1_CTCA_INTERRUPT == ENABLE
	SET_BIT(TIMSK , TIMSK_OCIE1A) ;
#else
#error "Wrong TIMER1_CTCA_INTERRUPT Config"
#endif

#if TIMER1_CTCB_INTERRUPT == DISABLE
	CLR_BIT(TIMSK , TIMSK_OCIE1B) ;
#elif TIMER1_CTCB_INTERRUPT == ENABLE
	SET_BIT(TIMSK , TIMSK_OCIE1B) ;
#else
#error "Wrong TIMER1_CTCB_INTERRUPT Config"
#endif

#if TIMER1_ICR_INTERRUPT == DISABLE
	CLR_BIT(TIMSK , TIMSK_TICIE1) ;
#elif TIMER1_ICR_INTERRUPT == ENABLE
	SET_BIT(TIMSK , TIMSK_TICIE1) ;
#else
#error "Wrong TIMER1_ICR1_INTERRUPT Config"
#endif
#else
#error "Wrong TIMER1_WAVEFORM_GENERATION_MODE Config"
#endif

	/*Set the Required Prescaler*/
	TCCR1B &= TIMER_PRESCALER_MASK ;
	TCCR1B |= TIMER1_PRESCALER ;
}

void TIMER1_voidSetPreload(u16 copy_u8Preload)
{
	TCNT1L = copy_u8Preload ;
	TCNT1H |= (copy_u8Preload>>8) ;
}

void TIMER1_voidSetCTCA(u16 copy_u8CTCA)
{
	OCR1AL = copy_u8CTCA ;
	OCR1AH |= (copy_u8CTCA>>8) ;
}

void TIMER1_voidSetCTCB(u16 copy_u8CTCB)
{
	OCR1BL = copy_u8CTCB ;
	OCR1BH |= (copy_u8CTCB>>8) ;
}

u16 TIMER1_u8GetTimerCounterValue(void)
{
	u16 Local_Var;
	Local_Var = TCNT1L;
	Local_Var |= (TCNT1H<<8);

	return Local_Var;
}



/**************************************************************************************/
/*											TIM2									  */
/**************************************************************************************/
void TIMER2_voidInit(void)
{
	/*Set Configurable Modes*/
#if TIMER2_WAVEFORM_GENERATION_MODE == TIMER_NORMAL_MODE

	/*Initialize Waveform Generation Mode as Normal Mode*/
	CLR_BIT(TCCR2 , TCCR2_WGM20) ;
	CLR_BIT(TCCR2 , TCCR2_WGM21) ;

	/*Set the Required Preload Value*/
	TCNT2 = TIMER2_PRELOAD_VAL ;

	/*Timer2 Overflow Interrupt Enable*/
#if TIMER2_OVERFLOW_INTERRUPT == DISABLE
	CLR_BIT(TIMSK , TIMSK_TOIE2) ;
#elif TIMER2_OVERFLOW_INTERRUPT == ENABLE
	SET_BIT(TIMSK , TIMSK_TOIE2) ;
#else
#error "Wrong TIMER2_OVERFLOW_INTERRUPT Config"
#endif

#elif TIMER2_WAVEFORM_GENERATION_MODE == TIMER_PWM_MODE
	/*Initialize Waveform Generation Mode as PWM Mode*/
	SET_BIT(TCCR2 , TCCR2_WGM20) ;
	CLR_BIT(TCCR2 , TCCR2_WGM21) ;

	/*Set CTC PWM MODE*/
#if TIMER2_CTC_PWM_MODE == TIMER_OC_DISCONNECTED
	CLR_BIT(TCCR2 , TCCR2_COM20) ;
	CLR_BIT(TCCR2 , TCCR2_COM21) ;
#elif TIMER2_CTC_PWM_MODE == TIMER_CLR_ON_CTC_SET_ON_TOP
	CLR_BIT(TCCR2 , TCCR2_COM20) ;
	SET_BIT(TCCR2 , TCCR2_COM21) ;
#elif TIMER2_CTC_PWM_MODE == TIMER_SET_ON_CTC_CLR_ON_TOP
	SET_BIT(TCCR2 , TCCR2_COM20) ;
	SET_BIT(TCCR2 , TCCR2_COM21) ;
#else
#error "Wrong TIMER2_CTC_PWM_MODE Config"
#endif

	/*Set the Required CTC Value*/
	OCR2 = TIMER2_CTC_VAL ;

#elif TIMER2_WAVEFORM_GENERATION_MODE == TIMER_CTC_MODE

	/*Initialize Waveform Generation Mode as CTC Mode*/
	CLR_BIT(TCCR2 , TCCR2_WGM20) ;
	SET_BIT(TCCR2 , TCCR2_WGM21) ;

	/*Set the Required CTC Value*/
	OCR2 = TIMER2_CTC_VAL ;

	/*Set CTC PWM MODE*/
#if TIMER2_OC2_MODE == TIMER_OC_DISCONNECTED
	CLR_BIT(TCCR2 , TCCR2_COM20) ;
	CLR_BIT(TCCR2 , TCCR2_COM21) ;
#elif TIMER2_OC2_MODE == TIMER_OC_TOGGEL
	CLR_BIT(TCCR2 , TCCR2_COM21) ;
	SET_BIT(TCCR2 , TCCR2_COM20) ;
#elif TIMER2_OC2_MODE == TIMER_OC_LOW
	CLR_BIT(TCCR2 , TCCR2_COM20) ;
	SET_BIT(TCCR2 , TCCR2_COM21) ;
#elif TIMER2_OC2_MODE == TIMER_OC_HIGH
	SET_BIT(TCCR2 , TCCR2_COM20) ;
	SET_BIT(TCCR2 , TCCR2_COM21) ;
#else
#error "Wrong TIMER2_OC2_MODE Configuration parameter!"
#endif


	/*Timer2 Compare Match Interrupt Enable*/
#if TIMER2_CTC_INTERRUPT == DISABLE
	CLR_BIT(TIMSK , TIMSK_OCIE2) ;
#elif TIMER2_CTC_INTERRUPT == ENABLE
	SET_BIT(TIMSK , TIMSK_OCIE2) ;
#else
#error "Wrong TIMER2_OVERFLOW_INTERRUPT Config"
#endif

#elif TIMER2_WAVEFORM_GENERATION_MODE == TIMER_FAST_PWM_MODE

	/*Initialize Waveform Generation Mode as Fast PWM Mode*/
	SET_BIT(TCCR2 , TCCR2_WGM20) ;
	SET_BIT(TCCR2 , TCCR2_WGM21) ;

	/*Set CTC Fast PWM MODE*/
#if TIMER2_CTC_PWM_MODE == TIMER_OC_DISCONNECTED
	CLR_BIT(TCCR2 , TCCR2_COM20) ;
	CLR_BIT(TCCR2 , TCCR2_COM21) ;
#elif TIMER2_CTC_PWM_MODE == TIMER_CLR_ON_CTC_SET_ON_TOP
	CLR_BIT(TCCR2 , TCCR2_COM20) ;
	SET_BIT(TCCR2 , TCCR2_COM21) ;
#elif TIMER2_CTC_PWM_MODE == TIMER_SET_ON_CTC_CLR_ON_TOP
	SET_BIT(TCCR2 , TCCR2_COM20) ;
	SET_BIT(TCCR2 , TCCR2_COM21) ;
#else
#error "Wrong TIMER2_CTC_PWM_MODE Config"
#endif

	/*Set the Required CTC Value*/
	OCR2 = TIMER2_CTC_VAL ;

#else
#error "Wrong TIMER2_WAVEFORM_GENERATION_MODE Config"

#endif

	/*Set the Required Prescaler*/
	TCCR2 &= TIMER_PRESCALER_MASK ;
	TCCR2 |= TIMER2_PRESCALER ;
}

void TIMER2_voidSetPreload(u8 copy_u8Preload)
{
	TCNT2 = copy_u8Preload ;
}
void TIMER2_voidSetCTC(u8 copy_u8CTC)
{
	OCR2 = copy_u8CTC ;
}


void TIMER2_voidSetFastPWM(u8 copy_u8PWM)
{
#if TIMER2_WAVEFORM_GENERATION_MODE == TIMER_FAST_PWM_MODE
	/*Set the Required CTC Value*/
	OCR2 = copy_u8PWM ;
#endif
}


void TIMER2_voidSetPhaseCorrectPWM(u8 copy_u8PWM)
{
#if TIMER2_WAVEFORM_GENERATION_MODE == TIMER_PWM_MODE
	/*Set the Required CTC Value*/
	OCR2 = copy_u8PWM ;
#endif
}

u8 TIMER2_u8GetTimerCounterValue(void)
{
	return TCNT2 ;
}






/*****************************************************************************************************/
u8 TIMER_u8SetCallBack(void(*copy_ptfCallBackFunc)(void),u8 copy_u8VectorID)
{
	u8 Local_u8ErrorState = E_OK;
	if((copy_u8VectorID<=TIMER0_OVF_VECTOR_ID) && (copy_u8VectorID>=TIMER2_CTC_VECTOR_ID))
	{
		u8 Local_u8ArrayIndex = copy_u8VectorID - CBF_OFFSET ;
		if(copy_ptfCallBackFunc!= NULL)
		{
			TIMERS_ptfCallBackFuncArr[Local_u8ArrayIndex]= copy_ptfCallBackFunc;
		}
		else
		{
			Local_u8ErrorState = E_NOK_NULL_PTR;
		}
	}
	else
	{
		Local_u8ErrorState = E_NOK_OUT_OF_RANGE;
	}

	return Local_u8ErrorState;
}


/***************TIMER0 OVF************************/
void __vector_11(void) __attribute__((signal));
void __vector_11(void)
{
	if(TIMERS_ptfCallBackFuncArr[TIMER0_OVF_VECTOR_ID - CBF_OFFSET] != NULL)
	{
		TIMERS_ptfCallBackFuncArr[TIMER0_OVF_VECTOR_ID - CBF_OFFSET]();
	}
}


/***************TIMER0 CTC************************/
void __vector_10(void) __attribute__((signal));
void __vector_10(void)
{
	if(TIMERS_ptfCallBackFuncArr[TIMER0_CTC_VECTOR_ID - CBF_OFFSET] != NULL)
	{
		TIMERS_ptfCallBackFuncArr[TIMER0_CTC_VECTOR_ID - CBF_OFFSET]();
	}
}



/***************TIMER1 OVF************************/
void __vector_9(void) __attribute__((signal));
void __vector_9(void)
{
	if(TIMERS_ptfCallBackFuncArr[TIMER1_OVF_VECTOR_ID - CBF_OFFSET] != NULL)
	{
		TIMERS_ptfCallBackFuncArr[TIMER1_OVF_VECTOR_ID - CBF_OFFSET]();
	}
}


/***************TIMER1 CTCB***********************/
void __vector_8(void) __attribute__((signal));
void __vector_8(void)
{
	if(TIMERS_ptfCallBackFuncArr[TIMER1_CTCB_VECTOR_ID - CBF_OFFSET] != NULL)
	{
		TIMERS_ptfCallBackFuncArr[TIMER1_CTCB_VECTOR_ID - CBF_OFFSET]();
	}
}


/***************TIMER1 CTCA***********************/
void __vector_7(void) __attribute__((signal));
void __vector_7(void)
{
	if(TIMERS_ptfCallBackFuncArr[TIMER1_CTCA_VECTOR_ID - CBF_OFFSET] != NULL)
	{
		TIMERS_ptfCallBackFuncArr[TIMER1_CTCA_VECTOR_ID - CBF_OFFSET]();
	}
}


/***************TIMER1 ICU************************/
void __vector_6(void) __attribute__((signal));
void __vector_6(void)
{
	if(TIMERS_ptfCallBackFuncArr[TIMER1_ICU_VECTOR_ID - CBF_OFFSET] != NULL)
	{
		TIMERS_ptfCallBackFuncArr[TIMER1_ICU_VECTOR_ID - CBF_OFFSET]();
	}
}

/***************TIMER2 OVF************************/
void __vector_5(void) __attribute__((signal));
void __vector_5(void)
{
	if(TIMERS_ptfCallBackFuncArr[TIMER2_OVF_VECTOR_ID - CBF_OFFSET] != NULL)
	{
		TIMERS_ptfCallBackFuncArr[TIMER2_OVF_VECTOR_ID - CBF_OFFSET]();
	}
}


/***************TIMER2 CTC************************/
void __vector_4(void) __attribute__((signal));
void __vector_4(void)
{
	if(TIMERS_ptfCallBackFuncArr[TIMER2_CTC_VECTOR_ID - CBF_OFFSET] != NULL)
	{
		TIMERS_ptfCallBackFuncArr[TIMER2_CTC_VECTOR_ID - CBF_OFFSET]();
	}
}















