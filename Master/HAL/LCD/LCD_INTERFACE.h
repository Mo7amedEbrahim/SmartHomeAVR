/*
 * LCD.h
 *
 *  Created on: 23 Aug 2019
 *      Author: Yussuf
 */

#ifndef LCD_H_
#define LCD_H_

#include "../../LIB/STD_TYPES.h"

extern void LCD_Init (void);
extern void LCD_WriteCommand (u8 command);
extern void LCD_WriteData (u8 data);
extern void LCD_WriteString (u8 line,u8 row,u8 string[]);
extern void LCD_WriteString (u8 line,u8 column,u8 string[]);
extern void LCD_WriteStringOnCursor (u8 string[]);
extern void LCD_WriteInteger (u8 line ,u8 column , u32 number);
extern void LCD_viddisplayfloat(u8 line,u8 column,f32 number);
extern void LCD_viddisplayintegar2 (u8 line ,u8 column , u32 number);
extern void LCD_viddisplaynumber(u8 line,u8 column,u32 num);
void LCD_GoToXY(u8 row , u8 column);
void LCD_WriteInt(u32 COPY_u32Number);
void LCD_WriteSpecialChar(u8* Ptr_u8PtrChar,u8 CGRam_index,u8 Copy_u8RowNum,u8 Copy_u8ColNum);


#define line1 1
#define line2 2
#define lcd_clr 0b00000001
#define shiftright 0b00011100
#define shiftleft 0b00011000
#define cursorleft 0b00010000
#define cursorright 0b00010100
#endif /* LCD_H_ */
