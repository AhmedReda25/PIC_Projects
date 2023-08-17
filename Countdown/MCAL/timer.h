#ifndef TIMER_H
#define TIMER_H


#define _XTAL_FREQ 16000000

#include <xc.h>
#include <stdint.h>
#include "bitmath.h"

#define INTERNAL_CLOCK 0
#define EXTERNAL_PIN   1

#define EXTERNAL_SYNC     0
#define EXTERNAL_NOT_SYNC 1

#define TIMER1_ON  do{TMR1ON = 1;}while(0)
#define TIMER1_OFF do{TMR1ON = 0;}while(0)


typedef enum
{
	T1_DIV1,
	T1_DIV2,
	T1_DIV4,
	T1_DIV8
	
}Timer1_Scaler_t;

/*------------------------------------------------------------------------------------------------*/
typedef enum{
    CCP_DISABLED,
    COMPARE_TOGGLE = 2,
    CAPTURE_FALLING = 4,
    CAPTURE_RISING,
    CAPTURE_4RISING,
    CAPTURE_16RISING,
    COMPARE_HIGH,
    COMPARE_LOW,
    COMPARE_FLAG_SET,
    COMPARE_SPECIAL_EVENT,
    PWM_MODE
}CCP_mode_t;
/*------------------------------------------------------------------------------------------------*/

void Timer1_init(Timer1_Scaler_t div, uint8_t clk_src, uint8_t ext_sync_state);
void Timer1_Reset(void);
void Timer1_SetPreload(uint16_t prld);
void Timer1_IntEn(void);
void Timer1_Compar_IntEn(void);
void Set_Compar_ISR(void(*pf)(void));
void CCP1_init(CCP_mode_t mode);
void Set_ComparValue(uint16_t com_val);


void __interrupt() _ISR(void);






#endif