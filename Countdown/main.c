

#include <xc.h>
#include <stdio.h>
#include <stdint.h>
#include "down_timer.h"
#include "timer_defines.h"
#include "LCD.h"
#include "timer.h"
#include "switch.h"
#include "led.h"

#define _XTAL_FREQ 16000000
uint8_t min = 0, sec = 0, digit = 0;
uint8_t Time_Counter = 0, Timer_On_Flag = 0;

void LCD_PrintTime(void);
void Compare_match_routine(void);
/*------------------------------------------------------------------------------*/
CursorLocation current_loc = STRT_LOC;

led_t indicator_led = {.port = DIO_PORTB, .pin = PIN2, .active_state = ACTIVE_HIGH};
void main(void) {
    
    switch_t inc = {.port = DIO_PORTC, .pin = PIN0, .active_state = ACTIVE_HIGH};
    switch_t advanc = {.port = DIO_PORTC, .pin = PIN1, .active_state = ACTIVE_HIGH};
    switch_t start = {.port = DIO_PORTC, .pin = PIN2, .active_state = ACTIVE_HIGH};
    
    sw_init(inc);
    sw_init(advanc);
    sw_init(start);
    ledInit(indicator_led);
    
    CCP1_init(COMPARE_SPECIAL_EVENT); /* Reset the timer on compare match and set compare flag */
    Set_Compar_ISR(Compare_match_routine);
    Set_ComparValue(50000);           /* 10 periodic interrupts = 1s */
    
    Timer1_Compar_IntEn();            /* Enable compare match interrupt   */
    Timer1_init(T1_DIV8, INTERNAL_CLOCK, EXTERNAL_NOT_SYNC); /* Timer1 count with system oscillator, pre-scaler 8 */
    
    
    LCD_init();
    LCD_String("Timer");
    LCD_PrintTime();

    while(1)
    {
        if(Timer_On_Flag)
        {
            LCD_Char_Blink_OFF();
            LCD_PrintTime(); /* Time will be updated every 1s within the timer ISR */
        }
        else
        {
            if(is_pressed(advanc))
            {
                __delay_ms(600);
                digit = 0;
                switch(current_loc)
                {
                    case STRT_LOC:
                        current_loc = MIN_TENS;
                        break;
                    case MIN_TENS:
                        current_loc = MIN_ONES;
                        break;
                    case MIN_ONES:
                        current_loc = SEC_TENS;
                        break;
                    case SEC_TENS:
                        current_loc = SEC_ONES;
                        break;
                    case SEC_ONES:
                        current_loc = STRT_LOC;
                        break;
                }
            }
            if(is_pressed(inc))
            {
                __delay_ms(600);
                if(digit < 9)
                {
                    digit++;
                    lcd_data(digit+'0');
                    switch(current_loc)
                    {
                        case MIN_TENS:
                            min += 10;
                            break;
                        case MIN_ONES:
                            min += 1;
                            break;
                        case SEC_TENS:
                            sec += 10;
                            break;
                        case SEC_ONES:
                            sec += 1;
                            break;
                    }
                }
            }
            LCD_SetCursor(2,current_loc);
            if(current_loc == 5)
                LCD_Char_Blink_OFF();
            else
                LCD_Char_Blink();
            
            if(is_pressed(start))
            {
                TIMER_ON;
                Timer_On_Flag = 1;
            }
        }
    }
    return;
}    
void LCD_PrintTime(void)
{
    LCD_SetCursor(2,MIN_TENS);
    lcd_data(min/10+'0'); /*Minutes tens*/
    lcd_data(min%10+'0'); /*Minutes ones*/
    lcd_data(':');
    lcd_data(sec/10+'0'); /*Seconds tens*/
    lcd_data(sec%10+'0'); /*Seconds ones*/
}

void Compare_match_routine(void)
{
    Time_Counter++;
        
        if(Time_Counter == 10)/* 1 second has been elapsed */
        {
            Time_Counter = 0; /* Reset the counter */
            ledToggle(indicator_led); /* Toggle indicator led */
            
            if(sec == 0)
            {
                sec = 59;
                min--;
            }
            else
            {
                sec--;
            }
            if(min==0 && sec==0) /* The specified time expired */
            {
                TIMER_OFF;
                Timer_On_Flag = 0;
                current_loc = STRT_LOC;
            }
        }
    
}