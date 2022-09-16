/*****************************Includes Used Through Project***********************************/
#include "LIB/STD_TYPES.h"
#include "MCAL/DIO/DIO_INTERFACE.h"
#include "MCAL/SPI/SPI_interface.h"
#include "MCAL/ADC/ADC_INTERFACE.h"
#include "MCAL/TIMER0/TIMER0_Interface.h"
#include "HAL/KPD/KPD_INTERFACE.h"
#include "HAL/KPD/KPD_CONFIG.h"
#include "HAL/LCD/LCD_INTERFACE.h"
#include "mainconfig.h"

#include <util/delay.h>
/********************************Variables Initialization**************************************/
u16 Temp_Read;						//Holds TEMP reading
u8 tries=0;							// Holds how many times password entered
u8 pass_status=PASS_NOT_SET;		//Holds Admin Password Status if it set or not
u8 login_status=not_logged;			//Holds Login Status if logged or not
u8 Local_u8Key=0xFF;				//Holds keypad returned value
u8 settedpass[PASS_SIZE]={NOT_STORED,NOT_STORED,NOT_STORED,NOT_STORED};//the array where it stored the Set password
u8 enteredpass[PASS_SIZE]={NOT_STORED,NOT_STORED,NOT_STORED,NOT_STORED};//the array where it stored the Entered password
/******************************** Functions Prototypes ****************************************/
/***************
 * 				NAME 	:  Servo_VoidRotate90Deg
 * 				INPUTS  :	Void
 * 				Return :	Void
 * 				Functionality : Rotating Door (Servo) 90 degree
 **********************************************************************************************/
void Servo_VoidRotate90Deg(void);
/***************
 * 				NAME 	:  Check_Temp
 * 				INPUTS  :	Void
 * 				Return :	Void
 * 				Functionality : Checking Temperature Range And Take Action According
 * 								To Temperature value
 **********************************************************************************************/
void Check_Temp(void);
/***************
 * 				NAME 	:  GetPressedKey
 * 				INPUTS  :	Void
 * 				Return :	u8
 * 				Functionality : Getting Pressed key from Keypad
 **********************************************************************************************/
u8 GetPressedKey(void);
/***************
 * 				NAME 	:  u8ComparePass
 * 				INPUTS  :	pointer to array1 , pointer to array2 ,size of Both arrays
 * 				Return :	u8
 * 				Functionality : it takes To arrays one holds Set password
 * 								and another holds Entered Password and Compare between them
 * 								and returns State of comparing ( 1 -> 2 Passwords Not equal)
 * 															   ( 0 -> 2 Passwords Are equal)
 **********************************************************************************************/
u8 u8ComparePass(const u8* pass1,const u8* pass2,const u8 size);
/***************
 * 				NAME 	:  EnterPass
 * 				INPUTS  :	Array
 * 				Return :	void
 * 				Functionality : Getting Entered Password from user via Keypad
 **********************************************************************************************/
void EnterPass(u8 pass[PASS_SIZE]);
/***************
 * 				NAME 	:  Temp_voidGetTemperature
 * 				INPUTS  :	u8 Temperature Channel
 * 				Return :	u16 Reading of LM35
 * 				Functionality : Measuring Temperature via ADC Channel
 **********************************************************************************************/
u16 Temp_voidGetTemperature(u8 TEMP_Channel);
int main()
{
	/*Initialize KeyPad*/
	KPD_VoidInit();
	LCD_Init(); //initializing LCD
	ADC_voidInit();	 //initializing ADC
	TIMER0_voidInit();
	DIO_SetPinDirection(DIO_PORTA,DIO_PIN0,DIO_INPUT);     //ADC Pin input to read temperature
	DIO_SetPinDirection(DIO_PORTA,DIO_PIN1,DIO_OUTPUT);	   //Servo motor Pin output

	DIO_SetPinDirection(DIO_PORTB,DIO_PIN5,DIO_OUTPUT);    //Lights Pin
	DIO_SetPinDirection(DIO_PORTB,DIO_PIN6,DIO_OUTPUT);     //TV Pin
	DIO_SetPinDirection(DIO_PORTB,DIO_PIN7,DIO_OUTPUT);     //Heater Pin


	while (tries!=2) /*Checking How many times password entered*/
	{
		/******************Setting Password in the start of Code****************/

		if (pass_status!=PASS_SET)/*check if password set previously or not*/
		{
			LCD_WriteStringOnCursor("Login for First time");	//send string
			_delay_ms(1000);									//Delaying to see output on LCD
			LCD_WriteCommand(lcd_clr);							//Clearing LCD
			LCD_WriteStringOnCursor("Set Admin Password");		//Send String

			EnterPass(settedpass);								/*Taking set password from user by Keypad*/
			pass_status=PASS_SET;		/*Setting status of password to set So that this piece of code don't be repeated*/

			LCD_WriteCommand(lcd_clr);							//Clearing LCD
			LCD_WriteStringOnCursor("Setting Pass Done");		//Send String
			_delay_ms(1000);									//Delaying to see output on LCD
		}

		/************************logging in*********************************************/
		if (pass_status==PASS_SET)	/*check if password is previously set*/
		{
			LCD_WriteCommand(lcd_clr);							//Clearing LCD
			LCD_WriteStringOnCursor("Enter Admin Pass");

			EnterPass(enteredpass);	//Taking entered Password from user
			u8 comparepassreturnedvalue=u8ComparePass(settedpass,enteredpass,4);//check entered pass with set password if they are equal

			while (login_status!=logged)
			{
				if(comparepassreturnedvalue==rightpass)  				//Checking entered pass if correct
				{
					LCD_WriteCommand(lcd_clr);							//Clearing LCD
					LCD_GoToXY(0,0);
					LCD_WriteStringOnCursor("Door Opening");
					_delay_ms(1000);
					Servo_VoidRotate90Deg();							//Open the door
					login_status=logged; 								//Changing login state to logged
					tries=0;			 								//Tries counter settled to zero
					LCD_WriteCommand(lcd_clr);							//Clearing LCD
					LCD_WriteStringOnCursor("Welcome");
					_delay_ms(1000);
					LCD_WriteCommand(lcd_clr);							//Clearing LCD
				}
				else if(comparepassreturnedvalue==wrongpass) //if entered pass is wrong
				{
					LCD_WriteCommand(lcd_clr);							//Clearing LCD
					LCD_WriteStringOnCursor("Wrong pass,try again");	//asking user to enter pass again
					EnterPass(enteredpass);								//Taking entered Password from user
					comparepassreturnedvalue	=	u8ComparePass(settedpass,enteredpass,4);//Comparing Set with entered password
					tries++;	//increasing tries counter
					if(tries==2) //if the tries reached 3 times
					{
						LCD_WriteCommand(lcd_clr);							//Clearing LCD
						LCD_WriteStringOnCursor("Login Failed");			//Access failed
						break;												//break of program
					}
				}
			}
		}

		while(login_status==logged)
		{
			LCD_WriteCommand(lcd_clr);							//Clearing LCD
			LCD_WriteStringOnCursor("1:Light 2:TV");			//Giving options to user
			LCD_GoToXY(1,0);									//Move to second line
			LCD_WriteStringOnCursor("3:TEMP ");			//Giving options to user

			GetPressedKey();									//Getting user Option
			if (Local_u8Key == LIGHTS)	//If user option is Lights
			{
				u8 LED_State = DIO_GetPinValue(DIO_PORTB,DIO_PIN5);
				if(LED_State==DIO_LOW)
				{
					DIO_SetPinValue(DIO_PORTB,DIO_PIN5,DIO_HIGH);	//Send order to slave to take action
				}
				else
				{
					DIO_SetPinValue(DIO_PORTB,DIO_PIN5,DIO_LOW);	//Send order to slave to take action
				}
			}
			else if (Local_u8Key == TV)//else If user option is TV
			{
				u8 TV_State = DIO_GetPinValue(DIO_PORTB,DIO_PIN6);
				if(TV_State==DIO_LOW)
				{
					DIO_SetPinValue(DIO_PORTB,DIO_PIN6,DIO_HIGH);	//Send order to slave to take action
				}
				else
				{
					DIO_SetPinValue(DIO_PORTB,DIO_PIN6,DIO_LOW);	//Send order to slave to take action
				}
			}
			else if (Local_u8Key == TEMP)//else if user option is TEMP
			{
				LCD_WriteCommand(lcd_clr);							//Clearing LCD
				Temp_Read = Temp_voidGetTemperature(ADC0);			//REad Temp from ADC Channel 0
				/*Displaying temp*/
				LCD_WriteStringOnCursor("Temp = ");
				LCD_WriteInt(Temp_Read);
				LCD_WriteStringOnCursor("C");
				_delay_ms(1000);
			}
			else // if wrong input
			{
				LCD_WriteCommand(lcd_clr);							//Clearing LCD
				LCD_WriteStringOnCursor("Wrong input");				//print error message
				_delay_ms(1000);
			}
		}

	}
}


/*************************Functions implementation**********************/

void EnterPass(u8 pass[PASS_SIZE])
{
	u8 Local_u8Key=0xFF;
	u8 pass_counter=0;//the counter of the characters of the password
	while (pass_counter<PASS_SIZE)//loop till the user finish inserting the pass
	{
		Local_u8Key=GetPressedKey();	//getting pressed key
		LCD_GoToXY(1,pass_counter);//displaying password on second line
		pass[pass_counter]=Local_u8Key;//add the entered character to the pass array
		LCD_WriteInt(pass[pass_counter]);//Display number
		_delay_ms(100);
		LCD_GoToXY(1,pass_counter);		//one Step Backward
		LCD_WriteStringOnCursor("*"); // to display (Password sign *)
		pass_counter++;					//increasing counter
	}
	//return pass[PASS_SIZE];
}



u8 GetPressedKey(void)
{
	Local_u8Key = 0xff;//return the variable that holds the pressed key from keypad to its initial value
	while (Local_u8Key == 0xff)//repeat till the user press any key
	{
		Check_Temp();	//
		Local_u8Key = KPD_u8GetPressedKey();
	}
	return Local_u8Key;
}

u8 u8ComparePass(const u8* pass1,const u8* pass2,const u8 size)
{
	u8 pin_counter=0;//the offset of the character of the pin
	u8 ret_value = 0;
	while (pin_counter<size)//loop till the pin is fully entered
	{
		if (pass1[pin_counter]!=pass2[pin_counter])//if the two characters of the entered pin and the stored pin are not equal
		{
			ret_value= 1;				//returns 1 that means the two PINs are not equal
			break;						//break the loop
		}
		pin_counter++;//increase the offset by one
	}
	return ret_value;//returns 0 that means the two PINs are equal since all characters of the PINs are equal
}



u16 Temp_voidGetTemperature(u8 TEMP_Channel)
{

	u16 local_DigitalReading;
	u16 local_AnalogReading;
	u16 Temperature ;
	local_DigitalReading= ADC_u16GetSyncReading(TEMP_Channel);
	local_AnalogReading = ((u32) local_DigitalReading * 5000UL)/1024;
	Temperature = local_AnalogReading / 620 ;
	return Temperature ;
}



void Check_Temp(void)
{
	Temp_Read = Temp_voidGetTemperature(ADC0);
	if(Temp_Read>=0	&& Temp_Read<=15)
	{
		TIMER0_SetDuty(0);//Fan off
		DIO_SetPinValue(DIO_PORTB,DIO_PIN7,DIO_HIGH);	//Heater on
	}
	else if((Temp_Read>15 && Temp_Read<=25))
	{
		TIMER0_SetDuty(0); //fan off
		DIO_SetPinValue(DIO_PORTB,DIO_PIN7,DIO_LOW);	//Heater off
	}
	else
	{
		TIMER0_SetDuty(Temp_Read *4); //Send Duty cycle (Changing Speed According to Temp read)
		DIO_SetPinValue(DIO_PORTB,DIO_PIN7,DIO_LOW);
	}
}

void Servo_VoidRotate90Deg(void)
{
	DIO_SetPinValue(DIO_PORTA,DIO_PIN1,DIO_HIGH);
	_delay_us(5000);
	DIO_SetPinValue(DIO_PORTA,DIO_PIN1,DIO_LOW);
	_delay_ms(1000);


	DIO_SetPinValue(DIO_PORTA,DIO_PIN1,DIO_HIGH);
	_delay_us(1500);
	DIO_SetPinValue(DIO_PORTA,DIO_PIN1,DIO_LOW);

}

