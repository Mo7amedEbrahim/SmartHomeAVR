/*
 * LCD.c
 *
 *  Created on: 23 Aug 2019
 *      Author: Yussuf
 */
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

#include "../../MCAL/DIO/DIO_INTERFACE.h"
#include "LCD_CONFIG.h"
#include "LCD_PRIVATE.h"
#include "LCD_INTERFACE.h"
#include <avr/delay.h>
#define f_cpu 8000000

extern void LCD_WriteCommand (u8 command)
{
	//RW=0
	DIO_SetPinValue (control_port,RW,DIO_LOW);
		//RS=0
		DIO_SetPinValue (control_port,RS,DIO_LOW);
		//Data
		DIO_SetPortValue (data_port,command);
		//start execution E=1
		DIO_SetPinValue(control_port,E,DIO_HIGH);
		_delay_ms(2);
		DIO_SetPinValue(control_port,E,DIO_LOW);

}
extern void LCD_WriteData (u8 data)
{
	//RW=0
	DIO_SetPinValue (control_port,RW,DIO_LOW);
	//RS=0
	DIO_SetPinValue (control_port,RS,DIO_HIGH);
	//Data
	DIO_SetPortValue (data_port,data);
	//start execution E=1
	DIO_SetPinValue(control_port,E,DIO_HIGH);
	_delay_ms(2);
	DIO_SetPinValue(control_port,E,DIO_LOW);
}
extern void LCD_Init (void)
{
	DIO_SetPinDirection(control_port,RS,DIO_OUTPUT);
	DIO_SetPinDirection(control_port,RW ,DIO_OUTPUT);
	DIO_SetPinDirection(control_port,E,DIO_OUTPUT);
	DIO_SetPortDirection(data_port,0b11111111);
	_delay_ms (50);
	LCD_WriteCommand(0b00111100);
	_delay_ms (2);
	LCD_WriteCommand(0b00001110);
	_delay_ms (2);
	LCD_WriteCommand(0b00000001);
}
void LCD_GoToXY(u8 row , u8 column)
{
	if(row==0){
		LCD_WriteCommand(128+column);
	}
	else if (row==1){
		LCD_WriteCommand(128+64+column);
	}
}
extern void LCD_WriteString (u8 line,u8 column,u8 string[])
{
	u8 i=0;
	LCD_GoToXY(line,column);
	_delay_ms(2);
	while (string[i]!= 0)
	{
		LCD_WriteData(string[i]);
		_delay_ms(2);
				i++;
	}
}
extern void LCD_WriteStringOnCursor (u8 string[])
{
	u8 i=0;
	_delay_ms(2);
	while (string[i]!= 0)
	{
		LCD_WriteData(string[i]);
		_delay_ms(2);
				i++;
	}
}


void LCD_WriteInt(u32 COPY_u32Number)
{
	u8 LOCAL_u8Num[10]={0};
	s16 i=0;
	u32 LOCAL_u32Remainder;
	if(COPY_u32Number==0)
	{
		LCD_WriteData('0');
	}

	if(COPY_u32Number>0)
	{
		while(COPY_u32Number!=0)
		{
			LOCAL_u32Remainder=COPY_u32Number%10;
			LOCAL_u8Num[i]=LOCAL_u32Remainder;
			COPY_u32Number=COPY_u32Number/10;
			i++;
		}
        i--;
		while(i>=0)
		{
			LCD_WriteData(LOCAL_u8Num[i]+48);
			i--;
		}
	}
}




void LCD_WriteSpecialChar(u8* Ptr_u8PtrChar,u8 CGRam_index,u8 Copy_u8RowNum,u8 Copy_u8ColNum)
{
	LCD_GoToXY( Copy_u8RowNum, Copy_u8ColNum);
	LCD_WriteData(CGRam_index);
	u8 Local_u8address;
	u8 Local_u8Index;
	if (CGRam_index < 8)
	{
		Local_u8address= CGRam_index * 8;
		Local_u8address=SET_BIT(Local_u8address,6);
		LCD_WriteCommand(Local_u8address);
		for(Local_u8Index = 0;Local_u8Index < 8;Local_u8Index++)
		{
			LCD_WriteData(Ptr_u8PtrChar[Local_u8Index]);
		}
	}
	LCD_WriteCommand(0x02);

}


