/***************************************************/
/*************** Author : Ahmedhamdy8 **************/
/*************** Layer  : MCAL        **************/
/*************** SWC    : TIMER0      **************/
/*************** version: 1           **************/

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "TIMER0_CONFIG.h"
#include "TIMER0_PRIVATE.h"
#include "TIMER0_INTERFACE.h"
//#include "stdlib.h"

static void (*TIMER0_OFFunc)(void)= NULL;
static void (*TIMER0_CTCFunc)(void)= NULL;

void TIMER0_voidInit(void)
{

	// Set mode
	#if  TIMER0_Mode == 1			// normal
		CLR_BIT(TCCR0,WGM00);
		CLR_BIT(TCCR0,WGM01);
		//enable over folw flag	
		SET_BIT(TIMSK,TOIE0);		
	#elif TIMER0_Mode == 2			// PWM
		CLR_BIT(TCCR0,WGM00);
		SET_BIT(TCCR0,WGM01);
	#elif TIMER0_Mode == 3			// compare match
		SET_BIT(TCCR0,WGM00);
		CLR_BIT(TCCR0,WGM01);
		//enable compare match flag
		SET_BIT(TIMSK,OCIE0);		
		// set compare match value
		OCR0=CTCvalue;
	#elif TIMER0_Mode == 4			// fast PWM
		SET_BIT(TCCR0,WGM00);
		SET_BIT(TCCR0,WGM01);
		
		CLR_BIT(TCCR0,COM00);		// set on top clear on comp
		SET_BIT(TCCR0,COM01);	
	#endif
	
	// set scaler
	#if  TIMER0_Prescaler == 0
		CLR_BIT(TCCR0,CS02);
		CLR_BIT(TCCR0,CS01);
		CLR_BIT(TCCR0,CS00);
	#elif TIMER0_Prescaler == 1
		CLR_BIT(TCCR0,CS02);
		CLR_BIT(TCCR0,CS01);
		SET_BIT(TCCR0,CS00);
	#elif TIMER0_Prescaler == 8
		CLR_BIT(TCCR0,CS02);
		SET_BIT(TCCR0,CS01);
		CLR_BIT(TCCR0,CS00);
	#elif TIMER0_Prescaler == 64
		CLR_BIT(TCCR0,CS02);
		SET_BIT(TCCR0,CS01);
		SET_BIT(TCCR0,CS00);
	#elif TIMER0_Prescaler == 256
		SET_BIT(TCCR0,CS02);
		CLR_BIT(TCCR0,CS01);
		CLR_BIT(TCCR0,CS00);
	#elif TIMER0_Prescaler == 1024
		SET_BIT(TCCR0,CS02);
		CLR_BIT(TCCR0,CS01);
		SET_BIT(TCCR0,CS00);
	#elif TIMER0_Prescaler == 2
		SET_BIT(TCCR0,CS02);
		SET_BIT(TCCR0,CS01);
		CLR_BIT(TCCR0,CS00);
	#elif TIMER0_Prescaler == 3
		SET_BIT(TCCR0,CS02);
		SET_BIT(TCCR0,CS01);
		SET_BIT(TCCR0,CS00);
	#endif
	
}

void TIMER0_SetDuty(u8 u8_dutycycle)
{

	OCR0 =  u8_dutycycle;
}


void TIMER0_voidOFSetCallBack(void(*Func)(void))
{
	if(Func != NULL)
	{
		TIMER0_OFFunc=Func;
	}
	else
	{
		
	}
}


void TIMER0_voidCTCSetCallBack(void(*Func)(void))
{
	if(Func != NULL)
	{
		TIMER0_CTCFunc=Func;
	}
	else
	{
		
	}
}


void __vector_11(void) __attribute__((signal));
void __vector_11(void)
{
	if ( TIMER0_OFFunc != NULL)
	{
		TIMER0_OFFunc();
	}
	else
	{
		
	}
}


void __vector_10(void) __attribute__((signal));
void __vector_10(void)
{
	if ( TIMER0_CTCFunc != NULL)
	{
		TIMER0_CTCFunc();
	}
	else
	{
		
	}
}





