#include "led.h"



void ledInit(led_t led)
{
	SetDir(led.port, led.pin, OUTPUT);
}
void ledON(led_t led)
{
	(led.active_state == ACTIVE_HIGH) ? PinWrite(led.port, led.pin, HIGH) : PinWrite(led.port, led.pin, LOW);
}
void ledOFF(led_t led)
{
	(led.active_state == ACTIVE_HIGH) ? PinWrite(led.port, led.pin, LOW) : PinWrite(led.port, led.pin, LOW);
}
void ledToggle(led_t led)
{
    PinToggle(led.port, led.pin);
}