/***************************************************/
/*************** Author : Ahmedhamdy8 **************/
/*************** Layer  : HAL         **************/
/*************** SWC    : KPD         **************/
/*************** version: 1           **************/
#include "../../LIB/STD_TYPES.h"
#include "../../MCAL/DIO/DIO_INTERFACE.h"
#include "KPD_INTERFACE.h"
#include "KPD_CONFIG.h"
#include "KPD_PRIVATE.h"

u8 KPD_u8GetPressedKey(void)
{
	u8 Local_u8Pressed=KPD_NO_PRESSED_KEY;
	u8 Local_u8Columnidx,Local_u8Rowidx;

	static u8 Local_u8KPDArr[ROW_NUM][COLUMN_NUM]=KPD_ARR_VAL;

	static u8 Local_u8KPDColumnArr[COLUMN_NUM]={KPD_COLUMN0,KPD_COLUMN1,KPD_COLUMN2,KPD_COLUMN3};
	static u8 Local_u8KPDRowArr[ROW_NUM]	  ={KPD_ROW0	,KPD_ROW1	,KPD_ROW2	,KPD_ROW3};

	for (Local_u8Columnidx=0 ; Local_u8Columnidx < COLUMN_NUM ; Local_u8Columnidx++)
	{
		//active column = set to low
		DIO_SetPinValue(KPD_PORT,Local_u8KPDColumnArr[Local_u8Columnidx],DIO_LOW);
		for (Local_u8Rowidx=0 ; Local_u8Rowidx < ROW_NUM ; Local_u8Rowidx++)
		{
			DIO_GetPinValue(KPD_PORT,Local_u8KPDRowArr[Local_u8Rowidx]);

			if(DIO_GetPinValue(KPD_PORT,Local_u8KPDRowArr[Local_u8Rowidx]) == DIO_LOW)
			{
				Local_u8Pressed=Local_u8KPDArr[Local_u8Rowidx][Local_u8Columnidx];
				while (DIO_GetPinValue(KPD_PORT,Local_u8KPDRowArr[Local_u8Rowidx]) == DIO_LOW)
				{
					DIO_GetPinValue(KPD_PORT,Local_u8KPDRowArr[Local_u8Rowidx]);
				}
				return Local_u8Pressed;
			}
		}
		//deactive column = set to high
		DIO_SetPinValue(KPD_PORT,Local_u8KPDColumnArr[Local_u8Columnidx],DIO_HIGH);

	}
	return Local_u8Pressed;
}
void KPD_VoidInit(void)
{
	//Set keypad
		//KP columns output
		DIO_SetPinDirection(KPD_PORT,KPD_COLUMN0,DIO_OUTPUT);
		DIO_SetPinDirection(KPD_PORT,KPD_COLUMN1,DIO_OUTPUT);
		DIO_SetPinDirection(KPD_PORT,KPD_COLUMN2,DIO_OUTPUT);
		DIO_SetPinDirection(KPD_PORT,KPD_COLUMN3,DIO_OUTPUT);
		//KP rows input
		DIO_SetPinDirection(KPD_PORT,KPD_ROW0,DIO_INPUT);
		DIO_SetPinDirection(KPD_PORT,KPD_ROW1,DIO_INPUT);
		DIO_SetPinDirection(KPD_PORT,KPD_ROW2,DIO_INPUT);
		DIO_SetPinDirection(KPD_PORT,KPD_ROW3,DIO_INPUT);
		//all KP pins high (pULLED uP)
		DIO_SetPortValue(KPD_PORT,DIO_PORT_HIGH);
}
