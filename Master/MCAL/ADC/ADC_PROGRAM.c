/***************************************************/
/*************** Author : Ahmedhamdy8 **************/
/*************** Layer  : MCAL        **************/
/*************** SWC    : ADC         **************/
/*************** version: 1           **************/

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "ADC_CONFIG.h"
#include "ADC_PRIVATE.h"
#include "ADC_INTERFACE.h"

void ADC_voidInit(void)
{
	//select avcc as ref voltage
	SET_BIT(ADMUX,REFS0);
	CLR_BIT(ADMUX,REFS1);
	
	// active lift adjust - 8 bit resolution
	SET_BIT(ADMUX,ADLAR);
	
	// Enable ADC
	SET_BIT(ADCSRA,ADEN);
	
	// set scaler
	#if  ADC_Prescaler == 2
		CLR_BIT(ADCSRA,ADPS0);
		CLR_BIT(ADCSRA,ADPS1);
		CLR_BIT(ADCSRA,ADPS2);
	#elif ADC_Prescaler == 4
		CLR_BIT(ADCSRA,ADPS0);
		SET_BIT(ADCSRA,ADPS1);
		CLR_BIT(ADCSRA,ADPS2);
	#elif ADC_Prescaler == 8
		CLR_BIT(ADCSRA,ADPS0);
		SET_BIT(ADCSRA,ADPS1);
		SET_BIT(ADCSRA,ADPS2);
	#elif ADC_Prescaler == 16
		SET_BIT(ADCSRA,ADPS0);
		CLR_BIT(ADCSRA,ADPS1);
		CLR_BIT(ADCSRA,ADPS2);
	#elif ADC_Prescaler == 32
		SET_BIT(ADCSRA,ADPS0);
		CLR_BIT(ADCSRA,ADPS1);
		SET_BIT(ADCSRA,ADPS2);
	#elif ADC_Prescaler == 64
		SET_BIT(ADCSRA,ADPS0);
		SET_BIT(ADCSRA,ADPS1);
		CLR_BIT(ADCSRA,ADPS2);
	#elif ADC_Prescaler == 128
		SET_BIT(ADCSRA,ADPS0);
		SET_BIT(ADCSRA,ADPS1);
		SET_BIT(ADCSRA,ADPS2);
	#endif
	
}
u8 ADC_u8Start(u8 ADC_CHANNEL)
{
	//Set channel
	ADMUX |= ADC_CHANNEL;
	
	// start conversion
	SET_BIT(ADCSRA,ADSC);
	
	while ((GET_BIT(ADCSRA,ADIF))==0);
	
		SET_BIT(ADCSRA,ADIF);

	return ADCH;
}

u16  ADC_u16GetSyncReading(u8 ADC_Channel)
{
	u32 Local_u8Counter=0;
	//Avoiding Error in Channel Number
	ADMUX &= 0b11100000 ;
	ADMUX |= ADC_Channel ;
	//START Conversion
	ADCSRA |= (1<<ADSC);
	//Wait Until Conversion Done
	while  (	(GET_BIT(ADCSRA,ADIF)	==	0)	&& (Local_u8Counter	 <	50000) )
	{
		Local_u8Counter++ ;
	}
	if (GET_BIT(ADCSRA,ADIF)	==	1)
	{
		//SET Flag again
		SET_BIT(ADCSRA,ADIF);
		//Store Data
		return ADC;
	}
	else
	{
		//Do Nothing
	}
	//Store Data
	return ADC;

}
