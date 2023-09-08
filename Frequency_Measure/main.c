

#include <xc.h>
#include <stdio.h>
#include "freq.h"
#include "MCAL/timer.h"
#include "MCAL/uart.h"
#include <stdint.h>
#define _XTAL_FREQ 16000000


volatile uint16_t end, start=0, ov=0;
volatile unsigned long count=0;
double period, freq;
char buf[10];

void TimerOvfISR(void)
{
    ov++;
}
void CaptureISR(void)
{
    end = Get_Captured();                                               /* Store the value of timer1 that has been captured */
    count = ((unsigned long)end + (ov * 65536)) - (unsigned long)start; /* The tick count for the full signal period        */
    start = end;
    
    ov = 0;
}
void main(void) {
    UART_Init();
    
    CCP1_init(CAPTURE_RISING);                               /* Initialize capture mode with every rising edge          */
    Timer1_init(T1_DIV1, INTERNAL_CLOCK, EXTERNAL_NOT_SYNC); /* Timer1 fed with internal oscillator without pre-scaling */
    SetDir(DIO_PORTC, PIN2, INPUT);                          /* Capturing pin input mode                                */
    
    
    TIMER1_OVF_INTERRUPT_ON();
    TIMER1_CAPTURE_INTERRUPT_ON();
    GLOBAL_INTERRUPT_ON();
    PERIPHERAL_INTERRUPT_ON();
    
    
    Set_Capture_ISR(CaptureISR);
    Set_T1OVF_ISR(TimerOvfISR);
    
    TIMER1_ON;
    while(1)
    {
        period = (double)count/(4000000);
        freq = 1/period;
        sprintf(buf, "%.2f", freq);
        UARTString(buf);
        UARTString("\r\n");
        __delay_ms(50);
    }
    return;
}