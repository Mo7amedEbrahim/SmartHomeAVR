/***************************************************/
/*************** Author : Ahmedhamdy8 **************/
/*************** Layer  : HAL         **************/
/*************** SWC    : KPD         **************/
/*************** version: 1           **************/

#ifndef KPD_CONFIG_H
#define KPD_CONFIG_H

#define KPD_PORT  				DIO_PORTD
#define KPD_NO_PRESSED_KEY		0xff
#define KPD_ARR_VAL				{ {7,8,9,'%'},{4,5,6,'X'},{1,2,3,'-'},{'on/c',0,'=','+'} }

enum COLUMNs
{
	KPD_COLUMN0 = DIO_PIN0,
	KPD_COLUMN1 = DIO_PIN1,
	KPD_COLUMN2 = DIO_PIN2,
	KPD_COLUMN3 = DIO_PIN3
};
enum ROWs
{
	KPD_ROW0 = DIO_PIN4,
	KPD_ROW1 = DIO_PIN5,
	KPD_ROW2 = DIO_PIN6,
	KPD_ROW3 = DIO_PIN7
};

#endif
