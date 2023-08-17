#ifndef LED_H
#define LED_H


#include "../MCAL/gpio.h"
#include "../MCAL/bitmath.h"
#include "../MCAL/timer.h"
#include <stdint.h>


#define ACTIVE_LOW  0
#define ACTIVE_HIGH 1

typedef struct
{
	uint8_t port         :3;
	uint8_t pin          :3;
	uint8_t active_state :1;
}led_t;

void ledInit(led_t led);
void ledON(led_t led);
void ledOFF(led_t led);
void ledToggle(led_t led);

#endif