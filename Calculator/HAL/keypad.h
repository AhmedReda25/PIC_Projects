#ifndef KEYPAD_H
#define KEYPAD_H


#include <xc.h>
#include <stdint.h>
#include "bitmath.h"
#include "gpio.h"

#define _XTAL_FREQ 16000000

#define R0 PIN0
#define R1 PIN1
#define R2 PIN2
#define R3 PIN3

#define C3 PIN4
#define C2 PIN5
#define C1 PIN6
#define C0 PIN7

#define NO_PRESS 0xFF

typedef struct{
	uint8_t port;
}keypad;

void keypad_init(keypad kpd);
uint8_t get_key(keypad kpd);




#endif