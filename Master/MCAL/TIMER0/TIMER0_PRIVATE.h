/***************************************************/
/*************** Auther : Ahmedhamdy8 **************/
/*************** Layer  : MCAL        **************/
/*************** SWC    : TIMER0      **************/
/*************** version: 1           **************/

#ifndef TIMER0_PRIVATE_H_
#define TIMER0_PRIVATE_H_

#define		TCCR0				*((volatile u8*)0x53)
#define 	CS00				0
#define 	CS01				1
#define 	CS02				2
#define 	WGM01				3
#define 	COM00				4
#define		COM01				5
#define 	WGM00				6
#define 	FOC0				7

#define		TCNT0				*((volatile u8*)0x52) //Timer Register
#define		OCR0				*((volatile u8*)0x5C) //Timer Compare Register

#define		TIMSK				*((volatile u8*)0x59)
#define  	TOIE0				0
#define  	OCIE0				1


#endif
