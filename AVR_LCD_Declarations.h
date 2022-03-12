
#ifndef AVR_LCD_DECLARATIONS_H_
#define AVR_LCD_DECLARATIONS_H_

#include "AVR_Input_and_Output.h"
#include "LCD_User_Selection.h"

void Port_Direction (char base, char state);
void Pin_Direction (char base, char pin, char state);
void Pin_Set (char base, char pin);
void Pin_Reset (char base, char pin);
char Port_Read (char base);
void Port_Write (char base, char value);
char Pin_Read (char base, char pin);
void Pin_Write (char base, char pin, char value);
void LCD_Initialize();
void LCD_Command(char cmd);
void LCD_Out(unsigned char value);
void LCD_Print(char * str);
void LCD_Print_xy(char row, char pos, char * str);
void LCD_Clear();

#endif /* AVR_LCD_DECLARATIONS_H_ */