#ifndef TIMER_H
#define TIMER_H

#include <stdint.h>
#include <xc.h>
#define _XTAL_FREQ 16000000

#define TIMER2_ON  (TMR2ON=1)
#define TIMER2_OFF (TMR2ON=0)

#define T0_EXT_PIN 1
#define T0_INT_CLK 0

#define RISING  0
#define FALLING 1


#define TIMER0_INT_ENABLE()       (TMR0IE = 1)
#define GLOBAL_INTERRUPT_ON()     (GIE = 1)
#define PERIPHERAL_INTERRUPT_ON() (PEIE = 1)

#define TIMER0_INT_DISABLE()       (TMR0IE = 0)
#define GLOBAL_INTERRUPT_OFF()     (GIE = 0)
#define PERIPHERAL_INTERRUPT_OFF() (PEIE = 0)


typedef enum{
    T2_DIV1,
    T2_DIV4,
    T2_DIV16        
}T2_prescaler_t;
/*----------------------------------------------*/

typedef enum{
    POST1,
    POST2,
    POST3,
    POST4,
    POST5,
    POST6,
    POST7,
    POST8,
    POST9,
    POST10,
    POST11,
    POST12,
    POST13,
    POST14,
    POST15,
    POST16
}T2_Postscaler_t;
/*----------------------------------------------*/

typedef enum {
	T0_DIV2,
	T0_DIV4,
	T0_DIV8,
	T0_DIV16,
	T0_DIV32,
	T0_DIV64,
	T0_DIV128,
	T0_DIV256,
	T0_DIV1
}T0_prescaler_t;
/*----------------------------------------------*/ 
    
typedef enum{
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
/*----------------------------------------------*/
void Timer2_init(T2_prescaler_t psc, T2_Postscaler_t post);
void CCP2_init(CCP_mode_t mode);
void Set_T2_Maxcount(uint8_t max);
void Set_CCP2DC(uint8_t dc); /* Duty Cycle */

void Timer0_init(T0_prescaler_t psc, uint8_t preload_value);
void Timer0_Counter_init(uint8_t edge);

void Set_T0_Callback(void(*p)(void));
void Timer0_SetPreload(uint8_t preload_value);

void T0_PeriodicInt_ms(uint16_t time, void(*fp)(void));







#endif