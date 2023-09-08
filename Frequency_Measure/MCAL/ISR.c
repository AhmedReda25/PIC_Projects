

#include <xc.h>
extern void (*CCP1_callback)(void);
extern void (*TMR1_OVF_Handler)(void);

extern void (*Tx_Handler)(void);
extern void (*Rx_Handler)(void);

void __interrupt() _ISR(void)
{
	if(TXIF && TXIE)
	{
        if(Tx_Handler)
            Tx_Handler();
       
	}
    if(RCIF && RCIE)
    {
        if(Rx_Handler)
            Rx_Handler();
        
    }
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