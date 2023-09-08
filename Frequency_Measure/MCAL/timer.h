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


#define CAPTURE_INTERRUPT_ON()  (CCP1IE = 1)
#define CAPTURE_INTERRUPT_OFF() (CCP1IE = 0)

#define PERIPHERAL_INTERRUPT_ON()  (PEIE = 1)
#define PERIPHERAL_INTERRUPT_OFF() (PEIE = 0)


#define GLOBAL_INTERRUPT_ON()  (GIE = 1)
#define GLOBAL_INTERRUPT_OFF() (GIE = 0)

#define TIMER1_OVF_INTERRUPT_ON()  (TMR1IE = 1)
#define TIMER1_OVF_INTERRUPT_OFF() (TMR1IE = 0)

#define TIMER1_COMPARE_INTERRUPT_ON()  (CCP1IE = 1)
#define TIMER1_COMPARE_INTERRUPT_OFF() (CCP1IE = 0)

#define TIMER1_CAPTURE_INTERRUPT_ON()  (CCP1IE = 1)
#define TIMER1_CAPTURE_INTERRUPT_OFF() (CCP1IE = 0)

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

void Set_Compar_ISR(void(*pf)(void));
void Set_Capture_ISR(void(*pf)(void));
void Set_T1OVF_ISR(void(*pf)(void));

void CCP1_init(CCP_mode_t mode);
void Set_ComparValue(uint16_t com_val);
uint16_t Get_Captured(void);


void __interrupt() _ISR(void);






#endif