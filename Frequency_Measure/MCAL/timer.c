#include "timer.h"

static void (*CCP1_callback)(void) = 0;
static void (*TMR1_OVF_Handler)(void) = 0;

uint8_t T1_preload = 0;

void Timer1_init(Timer1_Scaler_t div, uint8_t clk_src, uint8_t ext_sync_state)
{
	T1CON &= 0xCF;       /* Clear pre-scaler bits */
	T1CON |= (div<<4);   /* Set pre-scaler */
	
	TMR1CS = clk_src;    /* Select the clock */
	
	
	T1SYNC = ext_sync_state;  /* Select synchronization state (ignored if timer is clocked internally)*/
	
    TMR1 = 0;
	TIMER1_OFF; /* Start counting */

}

/*------------------------------------------------------------------------------------------------------------------*/
void Timer1_Reset(void)
{
	TMR1 = 0;
}

/*------------------------------------------------------------------------------------------------------------------*/
void Timer1_SetPreload(uint16_t prld)
{
	T1_preload = prld;
}
/*------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------------*/
void Set_Compar_ISR(void(*pf)(void))
{
	CCP1_callback = pf;
}
/*------------------------------------------------------------------------------------------------------------------*/
void Set_T1OVF_ISR(void(*pf)(void))
{
    TMR1_OVF_Handler = pf;
}
/*------------------------------------------------------------------------------------------------------------------*/
void Set_Capture_ISR(void(*pf)())
{
    CCP1_callback = pf;
}
/*------------------------------------------------------------------------------------------------------------------*/
void __interrupt() _ISR(void)
{
	if(CCP1IF)
	{
		if(CCP1_callback) /* Check NULL pointer */
			(*CCP1_callback)(); /* Execute timer1 callback routine */
		
		CCP1IF = 0;
	}
    if(TMR1IF)
    {
        if(TMR1_OVF_Handler)
            TMR1_OVF_Handler();
        
        TMR1IF = 0;
    }
}
/*------------------------------------------------------------------------------------------------------------------*/
void CCP1_init(CCP_mode_t mode)
{
    CCP1CON &= 0xF0; /* Clearing mode bits */
    CCP1CON |= mode; /* Setting the mode   */
}
/*------------------------------------------------------------------------------------------------------------------*/
void Set_ComparValue(uint16_t com_val)
{
    CCPR1 = com_val;
}
/*------------------------------------------------------------------------------------------------------------------*/
uint16_t Get_Captured(void)
{
    return CCPR1;
}

