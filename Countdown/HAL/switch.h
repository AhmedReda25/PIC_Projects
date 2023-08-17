#ifndef SWITCH_H
#define SWITCH_H

/*----------------------------------------------*/
#include "../MCAL/gpio.h"
#include "../MCAL/bitmath.h"
#include "../MCAL/timer.h"
#include <stdint.h>
/*----------------------------------------------*/
#define ACTIVE_LOW  0
#define ACTIVE_HIGH 1

#define RELEASED  0
#define PRESSED   1
/*----------------------------------------------*/
typedef struct
{
	uint8_t port         :3;
	uint8_t pin          :3;
	uint8_t active_state :1;
}switch_t;
/*----------------------------------------------*/

void sw_init(switch_t sw);
uint8_t is_pressed(switch_t sw);







#endif