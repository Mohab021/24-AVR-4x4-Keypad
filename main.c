
#define F_CPU 8000000UL
#include <util/delay.h>
#include <avr/io.h>
#include "AVR_Ports.h"
#include "AVR_LCD_Declarations.h"

uint8_t keypad[4][4] = {{'7', '8', '9', '/'},
						{'4', '5', '6', '*'},
						{'1', '2', '3', '-'},
						{'C', '0', '=', '+'}};

uint8_t CL1()
{
	PORTB = 0x01; //set PB0 (column 1)

	if(PINA == 0x01) { return keypad[0][0]; }
	else if(PINA == 0x02) { return keypad[1][0]; }
	else if(PINA == 0x04) { return keypad[2][0]; }
	else if(PINA == 0x08) { return keypad[3][0]; }
	else { return 'E'; }
}

uint8_t CL2()
{
	PORTB = 0x02; //set PB1 (column 2)

	if(PINA == 0x01) { return keypad[0][1]; }
	else if(PINA == 0x02) { return keypad[1][1]; }
	else if(PINA == 0x04) { return keypad[2][1]; }
	else if(PINA == 0x08) { return keypad[3][1]; }
	else { return 'E'; }
}

uint8_t CL3()
{
	PORTB = 0x04; //set PB2 (column 3)

	if(PINA == 0x01) { return keypad[0][2]; }
	else if(PINA == 0x02) { return keypad[1][2]; }
	else if(PINA == 0x04) { return keypad[2][2]; }
	else if(PINA == 0x08) { return keypad[3][2]; }
	else { return 'E'; }
}

uint8_t CL4()
{
	PORTB = 0x08; //set PB3 (column 4)

	if(PINA == 0x01) { return keypad[0][3]; }
	else if(PINA == 0x02) { return keypad[1][3]; }
	else if(PINA == 0x04) { return keypad[2][3]; }
	else if(PINA == 0x08) { return keypad[3][3]; }
	else { return 'E'; }
}

int main(void)
{
	uint8_t result;
	LCD_Initialize();
	
	DDRA = 0x00; //input
	DDRB = 0xFF; //output
	
    while(1) 
    {
		result = CL1(); //set column1, set only one column at a time
		_delay_ms(50); //a delay for debounce
		if( result != 'E' ){ LCD_Out(result); } // E, is (empty), that's in case of no keypress
	
		result = CL2(); //set column2, set only one column at a time
		_delay_ms(50);
		if( result != 'E' ){ LCD_Out(result); }
			
		result = CL3(); //set column3, set only one column at a time
		_delay_ms(50);
		if( result != 'E' ){ LCD_Out(result); }
			
		result = CL4(); //set column4, set only one column at a time
		_delay_ms(50);
		if( result != 'E' ){ LCD_Out(result); }
	}
}
