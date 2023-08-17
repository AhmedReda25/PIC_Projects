
#include "switch.h"

void sw_init(switch_t sw){
	SetDir(sw.port, sw.pin, INPUT);
}

/*-------------------------------------------------------------------*/

uint8_t is_pressed(switch_t sw){
	uint8_t stat = RELEASED;
    
    
	if(sw.active_state == ACTIVE_HIGH){
		if(GetPin(sw.port,sw.pin) == HIGH){
			__delay_ms(2); /* De-bounsing */
			if(GetPin(sw.port,sw.pin) == HIGH){
                stat = PRESSED;
            }
		}
	}
	else{
		if(GetPin(sw.port,sw.pin) == LOW){
			__delay_ms(2); /* De-bounsing */
			if(GetPin(sw.port,sw.pin) == LOW){
                stat = PRESSED;
            }
		}
	}
    return stat;
	
}