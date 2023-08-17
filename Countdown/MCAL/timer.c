#include "timer.h"

void (*CCP1_callback) (void) = 0;
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
void Timer1_IntEn(void)
{
	GIE    = 1;    /* Global interrupt          */
	PEIE   = 1;    /* peripheral interrupts     */
	TMR1IE = 1;    /* Timer1 overflow interrupt */
	TMR1IF = 0;
}
/*------------------------------------------------------------------------------------------------------------------*/

void Timer1_Compar_IntEn(void)
{
	CCP1IF = 0;
    CCP1IE = 1;
    PEIE   = 1;
    GIE    = 1;
}

/*------------------------------------------------------------------------------------------------------------------*/
void Set_Compar_ISR(void(*pf)(void))
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
}
/*------------------------------------------------------------------------------------------------------------------*/

void CCP1_init(CCP_mode_t mode)
{
    CCP1CON &= 0xF0; /* Clearing mode bits */
    CCP1CON |= mode; /* Setting the mode   */
}

void Set_ComparValue(uint16_t com_val)
{
    CCPR1 = com_val;
}


