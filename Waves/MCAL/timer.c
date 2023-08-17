#include "timer.h"

static void (*T0_callback) (void) = 0;
static void (*Periodic_Fun) (void);
static uint8_t T0_preload = 0;

static uint16_t ovf = 0;
/*----------------------------------------------------------------*/
static void T0_msRoutine(void)
{
	static uint8_t c = 0;
	c++;
	
	if(c == ovf)
	{
		Periodic_Fun();
		c = 0;
	}
}
/*----------------------------------------------------------------*/
void Timer2_init(T2_prescaler_t psc, T2_Postscaler_t post)
{
    /* pre-scaler set */
    T2CON &= 0xFC;
    T2CON |= psc;
    
    /* post-scaler set */
    T2CON &= 0x87;
    T2CON |= (post<<3);
    
    TMR2ON=1;
    TMR2 = 0;
}
/*----------------------------------------------------------------*/
void CCP2_init(CCP_mode_t mode)
{
    CCP2CON &= 0xF0; /* Clearing mode bits */
    CCP2CON |= mode; /* Selecting the mode */
}
/*----------------------------------------------------------------*/
void Set_T2_Maxcount(uint8_t max)
{
    PR2 = max;
}
void Set_CCP2DC(uint8_t dc)
{
    CCP2Y = dc&1;
    CCP2X = (dc>>1)&1;
    CCPR2L = dc>>2;
}
/*----------------------------------------------------------------*/
void Timer0_init(T0_prescaler_t psc, uint8_t preload_value)
{
	T0CS = T0_INT_CLK;      /* Internal clock (Fosc/4) */
	if(psc == T0_DIV1)
		PSA = 1;            /* pre-scaler assigned to WDT */
	else{
		PSA = 0;            /* pre-scaler assigned to timer0 */
		OPTION_REG &= 0xF8; /* Mask pre-scaler bits */
		OPTION_REG |= psc;
	}
	T0_preload = preload_value;
}
/*----------------------------------------------------------------*/
void Timer0_Counter_init(uint8_t edge)
{
	PSA = 1;           /* prescaler assigned to WDT */
	T0CS = T0_EXT_PIN; /* Count with external pin */
	T0SE = edge;
}

/*----------------------------------------------------------------*/
static void __interrupt() _ISR(void)
{
	if(TMR0IF)
	{
		if(T0_callback)       /* Check NULL pointer              */
			(*T0_callback)(); /* Execute timer0 callback routine */
		
		TMR0IF = 0;
		TMR0 += T0_preload;   /* Restart counting from pre-loaded value */
	}
}
/*----------------------------------------------------------------*/
void Set_T0_Callback(void(*p)(void))
{
	T0_callback = p;
}
/*----------------------------------------------------------------*/
void Timer0_SetPreload(uint8_t preload_value)
{
    T0_preload = preload_value;
}
/*----------------------------------------------------------------*/
void T0_PeriodicInt_ms(uint16_t time, void(*fp)(void))
{
	Timer0_init(T0_DIV32, 0);  /* 16 MHZ -> 32*4 pre-scaler -> 1 tick = 8 us */
	uint32_t ticks = time*125; /* (time * 10^-3) / 8us */
	
	if(ticks < 256){
		Timer0_SetPreload(256 - ticks);
		ovf = 1;
	}
	else{
		ovf = time;
		Timer0_SetPreload(131); /* 125 ticks and repeat (time) times */
	}
    
	Periodic_Fun = fp;
	Set_T0_Callback(T0_msRoutine);
	
	TIMER0_INT_ENABLE();
	GLOBAL_INTERRUPT_ON();
	PERIPHERAL_INTERRUPT_ON();
	
}




