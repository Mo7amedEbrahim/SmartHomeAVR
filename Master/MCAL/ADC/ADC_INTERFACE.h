/***************************************************/
/*************** Author : Ahmedhamdy8 **************/
/*************** Layer  : MCAL        **************/
/*************** SWC    : ADC         **************/
/*************** version: 1           **************/

#ifndef ADC_INTERFACE_H_
#define ADC_INTERFACE_H_

void ADC_voidInit(void);
u8  ADC_u8Start(u8 ADC_CHANNEL);

// Channels
#define		ADC0			0
#define		ADC1			1
#define		ADC2			2
#define		ADC3			3
#define		ADC4			4
#define		ADC5			5
#define		ADC6			6
#define		ADC7			7
#define		ADC0NOISE		8  //ADC0 - ADC0
//#define
//#define
//#define

#endif
