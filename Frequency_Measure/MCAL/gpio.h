#ifndef GPIO_H
#define GPIO_H

#include <xc.h>
#include <stdint.h>
#include "bitmath.h"

#define INPUT  0
#define OUTPUT 1

#define HIGH 1
#define LOW  0

#define PIN0 0
#define PIN1 1
#define PIN2 2
#define PIN3 3
#define PIN4 4
#define PIN5 5
#define PIN6 6
#define PIN7 7

#define DIO_PORTA 1
#define DIO_PORTB 2
#define DIO_PORTC 3
#define DIO_PORTD 4

void SetDir(uint8_t port, uint8_t pin, uint8_t dir);
void PinWrite(uint8_t port, uint8_t pin, uint8_t val);
void PinToggle(uint8_t port, uint8_t pin);
uint8_t GetPin(uint8_t port, uint8_t pin);

#endif