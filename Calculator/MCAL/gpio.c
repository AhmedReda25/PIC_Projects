
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
		}
	}
	else
	{
		switch(port)
		{
			case DIO_PORTA: SET_BIT(TRISA,pin); break;
			case DIO_PORTB: SET_BIT(TRISB,pin); break;
			case DIO_PORTC: SET_BIT(TRISC,pin); break;
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
		}
	}
	else
	{
		switch(port)
		{
			case DIO_PORTA: SET_BIT(PORTA,pin); break;
			case DIO_PORTB: SET_BIT(PORTB,pin); break;
			case DIO_PORTC: SET_BIT(PORTC,pin); break;
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
	}
}
/*----------------------------------------------------------*/
void PinToggle(uint8_t port, uint8_t pin)
{
    switch(port)
	{
		case DIO_PORTA: TOGGLE_BIT(PORTA,pin); return;
		case DIO_PORTB: TOGGLE_BIT(PORTB,pin); return;
		case DIO_PORTC: TOGGLE_BIT(PORTC,pin); return;
		case DIO_PORTE: TOGGLE_BIT(PORTE,pin); return;
	}
}
/*----------------------------------------------------------*/
void PortWrite(uint8_t port, uint8_t val)
{
	switch(port)
	{
		case DIO_PORTA: PORTA = val; return;
		case DIO_PORTB: PORTB = val; return;
		case DIO_PORTC: PORTC = val; return;
	}
}
/*----------------------------------------------------------*/
uint8_t GetPortValue(uint8_t port)
{
	switch(port)
	{
		case DIO_PORTA: return PORTA ;
		case DIO_PORTB: return PORTB ;
		case DIO_PORTC: return PORTC ;
	}
}
/*----------------------------------------------------------*/
void SetPortDir(uint8_t port, uint8_t dir)
{
    if(dir == OUTPUT)
	{
		switch(port)
		{
			case DIO_PORTA: TRISA = 0x00; break;
			case DIO_PORTB: TRISB = 0x00; break;
			case DIO_PORTC: TRISC = 0x00; break;
		}
	}
	else
	{
		switch(port)
		{
			case DIO_PORTA: TRISA = 0xFF; break;
			case DIO_PORTB: TRISB = 0xFF; break;
			case DIO_PORTC: TRISC = 0xFF; break;
		}
	}
}