/***************************************************/
/*************** Auther : Ahmedhamdy8 **************/
/*************** Layer  : MCAL        **************/
/*************** SWC    : TIMER0      **************/
/*************** version: 1           **************/

#ifndef TIMER0_INTERFACE_H_
#define TIMER0_INTERFACE_H_

void TIMER0_voidInit(void);
void TIMER0_voidOFSetCallBack(void(*Func)(void));
void TIMER0_voidCTCSetCallBack(void(*Func)(void));
void TIMER0_SetDuty(u8 u8_dutycycle);



#endif
