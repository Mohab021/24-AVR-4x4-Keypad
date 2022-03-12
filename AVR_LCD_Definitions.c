
#define F_CPU 8000000UL
#include <util/delay.h>
#include "AVR_LCD_Declarations.h"

void Port_Direction (char base, char state) //use DDRX
{
	if (state == output)
	*(volatile unsigned char *)(base+1) = 0xff; //1
	else
	*(volatile unsigned char *)(base+1) = 0x00; //0
}

void Pin_Direction (char base, char pin, char state) //use DDRX
{
	if (state == output)
	*(volatile unsigned char *)(base+1) |= (1<<pin); //1
	else
	*(volatile unsigned char *)(base+1) &= ~(1<<pin); //0
}

void Pin_Set (char base, char pin) //use PORTX
{
	*(volatile unsigned char *)(base+2) |= (1<<pin); //1
}

void Pin_Reset (char base, char pin) //use PORTX
{
	*(volatile unsigned char *)(base+2) &= ~(1<<pin); //0
}

char Port_Read (char base) //use PINX
{
	return *(volatile unsigned char *)(base);
}

void Port_Write (char base, char value) //use PORTX
{
	*(volatile unsigned char *)(base+2) = value;
}

char Pin_Read (char base, char pin) //use PINX
{
	unsigned char pin_value;
	pin_value = *(volatile unsigned char *)(base) & (1<<pin);
	
	if (pin_value) return 1;
	else return 0;
}

void Pin_Write (char base, char pin, char value) //use PORTX
{
	if(value == 1)
	{
		*(volatile unsigned char *)(base+2) |= (1<<pin); //1
	}
	else
	{
		*(volatile unsigned char *)(base+2) &= ~(1<<pin); //0
	}
}

void LCD_Initialize()
{
	Port_Direction (data, output); //put data port as output
	Pin_Direction (command, RS, output); //put command pin RS as output
	Pin_Direction (command, E, output); //put command pin E as output
	Port_Write(data, 0); //initialize data port with zero values
	Pin_Reset(command, E); //initialize E pin with zero, before sending the pulse
	
	if(mode == 4)
	{
		_delay_us(2000); /////
		LCD_Command(0x33);
		LCD_Command(0x32);
		LCD_Command(0x28);
		LCD_Command(0x0e);
		LCD_Command(0x01);
		_delay_us(2000); /////
		LCD_Command(0x06);
	}
	else //if it's 8 or anything else (so 8 is the default);
	{
		_delay_us(2000); /////
		LCD_Command(0x38);
		LCD_Command(0x0e);
		LCD_Command(0x01);
		_delay_us(2000); /////
		LCD_Command(0x06);
	}

}

void LCD_Command(char cmd)
{
	Pin_Reset(command, RS); //initialize RS pin with zero for sending a command
	
	if(mode == 4)
	{
		Port_Write(data, cmd & 0xf0); //0xf0 = 11110000, so we take high bits D4:D7
		Pin_Set(command, E);
		_delay_us(1);
		Pin_Reset(command, E);
		_delay_us(100);
		Port_Write(data, cmd<<4); //cmd<<4 = XXXX0000, so we take low bits D0:D3 by shifting to left
		Pin_Set(command, E);
		_delay_us(1);
		Pin_Reset(command, E);
		_delay_us(100);	
	}
	else //if it's 8 or anything else (so 8 is the default);
	{
		Port_Write(data, cmd); //send all 8bits through data port
		Pin_Set(command, E);
		_delay_us(1);
		Pin_Reset(command, E);
		_delay_us(100);
	}
}

void LCD_Out(unsigned char value)
{
	Pin_Set(command, RS); //initialize RS pin with 1 for sending the data
	
	if(mode == 4)
	{
		Port_Write(data, value & 0xf0); //0xf0 = 11110000, so we take high bits D4:D7
		Pin_Set(command, E);
		_delay_us(1);
		Pin_Reset(command, E);
		_delay_us(100);
		Port_Write(data, value<<4); //value<<4 = XXXX0000, so we take low bits D0:D3 by shifting to left
		Pin_Set(command, E);
		_delay_us(1);
		Pin_Reset(command, E);
		_delay_us(100);
	}
	else //if it's 8 or anything else (so 8 is the default);
	{
		Port_Write(data, value); //send all 8bits through data port
		Pin_Set(command, E);
		_delay_us(1);
		Pin_Reset(command, E);
		_delay_us(100);
	}
}

void LCD_Print(char * str) //char*str = "Hello", str (pointer) can access this array of characters (a string)
{
	unsigned char i = 0;
	
	while(str[i] != 0) //as the string is terminated with null value(zero), (0 as a number not '0' as a char)
	{
		LCD_Out(str[i]); //print the current char on LCD
		i++;
	}
}

void LCD_Print_xy(char row, char pos, char * str) //(print at xy position), x is the row, y is the pos(column)
{
	if((row == 0) && (pos < 16))
	{
		LCD_Command( (pos & 0x0F) | (0x80) ); //0x80 force cursor to start from the 1st line
	}
	else if((row == 1) && (pos < 16))
	{
		LCD_Command( (pos & 0x0F) | (0xC0) ); //0xC0 force cursor to start from the 2nd line	
	}
	
	LCD_Print(str); //Print the string by calling the LCD_Print function
}

void LCD_Clear()
{
	LCD_Command(0x01); //Clear display screen
	_delay_ms(2);
	LCD_Command( (0 & 0x0F) | (0x80) ); //Cursor at 00 position
}
