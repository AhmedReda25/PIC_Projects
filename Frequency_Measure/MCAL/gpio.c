
#include "gpio.h"


void SetDir(uint8_t port, uint8_t pin, uint8_t dir)
{
	if(dir == OUTPUT)
	{
		switch(port)
		{
			case DIO_PORTA: CLR_BIT(TRISA,pin); break;
			case DIO_PORTB: CLR_BIT(TRISB,pin); break;
			case DIO_PORTC: CLR_BIT(TRISC,pin); break;
//			case DIO_PORTD: CLR_BIT(TRISD,pin); break;
		}
	}
	else
	{
		switch(port)
		{
			case DIO_PORTA: SET_BIT(TRISA,pin); break;
			case DIO_PORTB: SET_BIT(TRISB,pin); break;
			case DIO_PORTC: SET_BIT(TRISC,pin); break;
//			case DIO_PORTD: SET_BIT(TRISD,pin); break;
		}
	}
}
/*----------------------------------------------------------*/

void PinWrite(uint8_t port, uint8_t pin, uint8_t val)
{
	if(val == LOW)
	{
		switch(port)
		{
			case DIO_PORTA: CLR_BIT(PORTA,pin); break;
			case DIO_PORTB: CLR_BIT(PORTB,pin); break;
			case DIO_PORTC: CLR_BIT(PORTC,pin); break;
//			case DIO_PORTD: CLR_BIT(PORTD,pin); break;
		}
	}
	else
	{
		switch(port)
		{
			case DIO_PORTA: SET_BIT(PORTA,pin); break;
			case DIO_PORTB: SET_BIT(PORTB,pin); break;
			case DIO_PORTC: SET_BIT(PORTC,pin); break;
//			case DIO_PORTD: SET_BIT(PORTD,pin); break;
		}
	}
}
/*----------------------------------------------------------*/
uint8_t GetPin(uint8_t port, uint8_t pin)
{
	switch(port)
	{
		case DIO_PORTA: return GET_BIT(PORTA,pin);
		case DIO_PORTB: return GET_BIT(PORTB,pin);
		case DIO_PORTC: return GET_BIT(PORTC,pin);
//		case DIO_PORTD: return GET_BIT(PORTD,pin);
	}
}
/*----------------------------------------------------------*/
void PinToggle(uint8_t port, uint8_t pin)
{
    switch(port)
	{
		case DIO_PORTA: TOGGLE_BIT(PORTA,pin);
		case DIO_PORTB: TOGGLE_BIT(PORTB,pin);
		case DIO_PORTC: TOGGLE_BIT(PORTC,pin);
//		case DIO_PORTD: TOGGLE_BIT(PORTD,pin);
	}
}

