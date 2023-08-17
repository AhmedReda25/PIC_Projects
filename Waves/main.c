

#include "config.h"
#include "MCAL/timer.h"
#include "MCAL/gpio.h"
#include "HAL/switch.h"


#define SAWTH_UP   1
#define SAWTH_DOWN 0

#define SIN_WAVE 0
#define SAWTH    1
#define TRINGL   2
/*---------------------Sin lookup--------------------------------------*/
uint8_t sin_lut[] = {0x80,0x8c,0x98,0xa5,0xb0,0xbc,0xc6,0xd0,
0xda,0xe2,0xea,0xf0,0xf5,0xfa,0xfd,0xfe,
0xff,0xfe,0xfd,0xfa,0xf5,0xf0,0xea,0xe2,
0xda,0xd0,0xc6,0xbc,0xb0,0xa5,0x98,0x8c,
0x80,0x73,0x67,0x5a,0x4f,0x43,0x39,0x2f,
0x25,0x1d,0x15,0xf,0xa,0x5,0x2,0x1,
0x0,0x1,0x2,0x5,0xa,0xf,0x15,0x1d,
0x25,0x2f,0x39,0x43,0x4f,0x5a,0x67,0x73};
/*---------------------------------------------------------------------*/
/*---------------------------------------------------------------------*/
uint8_t ovf = 0, pl = 0;

uint8_t sawtoth_value = 0, dir = SAWTH_UP;
uint8_t wave_type = SIN_WAVE;


volatile uint8_t sinwave_step = 0;
void Update_DAC(void){
    
        switch(wave_type)
        {
            case SIN_WAVE:
                Set_CCP2DC(sin_lut[sinwave_step++]);
                if(sinwave_step > 63)
                    sinwave_step = 0;
                break;

            case TRINGL:
                sawtoth_value += 2;
                Set_CCP2DC(sawtoth_value); /* Will automatically overflow to zero after 255 */
                break;

            case SAWTH:
                dir==SAWTH_UP? (sawtoth_value += 4) : (sawtoth_value -= 4);
                Set_CCP2DC(sawtoth_value);
                if(sawtoth_value >= 252)
                    dir = SAWTH_DOWN;
                else if(sawtoth_value < 4)
                    dir = SAWTH_UP;
                break;
       }
}
/*---------------------------------------------------------------------*/
void main(void) {
    
    switch_t WaveType_sw = {.port = DIO_PORTD, .pin = PIN1, .active_state = ACTIVE_HIGH};

    sw_init(WaveType_sw);
    
    
    /* Setting up timer2 & CCP2 for PWM generation */
	Timer2_init(T2_DIV1, POST1);
	CCP2_init(PWM_MODE);
	Set_T2_Maxcount(63);             /* Max PWM count is 4-times larger than this value + 1, in this case (63+1)*4 = 256 -> 8-bit */
	SetDir(DIO_PORTC, PIN1, OUTPUT); /* PWM pin output */
    
    
    /* Setting up timer0 for a periodic interrupt,
     * the value of the duty cycle(Digital value fed to DAC)
     * will be updated within the timer ISR 
	 */
    Timer0_init(T0_DIV32,150);
    Set_T0_Callback(Update_DAC);
    
    TIMER0_INT_ENABLE();
	GLOBAL_INTERRUPT_ON();
	PERIPHERAL_INTERRUPT_ON();
    while(1)
    {
        if(is_pressed(WaveType_sw))
        {
            wave_type++; /* Change the current wave */
            if(wave_type > 2)
                wave_type = 0;
            __delay_ms(50);
        }
    }
    
    return;
}
