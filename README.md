System specification:
> Imagine you have only one pin available on your controller.
> which connects to an Analog-to-Digital Converter (ADC)
> Though this pin you have to control various operations in the system.
 Operations AND Modes:
/***************************************************************************************/
Mode 0:
   > System has no interrupt (Maskable interrupt).
  > LCD display Mode0 in first line, No Maskable in second line.
Mode 1:
  > System has interrupt.
  > EXTI0 is enabled.
     LCD display Mode1 in first line, E: EXTI0 in second line.
     EXTI0 toggle LED0.
Mode 2:
  > System has interrupt .
  > EXTI0,EXTI1 is enabled.
  > LCD display Mode2 in first line, E: EXTI0,EXTI1 in second line.
  > EXTI0 set LED0.
  > EXTI1 clear LED0.
Mode 3:
  > System has interrupt .
  > EXTI0,EXTI1 is enabled.
  > LCD display Mode3 in first line, E: EXTI0,EXTI1 in second line
  > EXTI0 toggle LED0.
  >  EXTI1 toggle LED1.
