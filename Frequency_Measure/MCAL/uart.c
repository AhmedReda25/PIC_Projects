

#include "uart.h"
static char *st_rec;
static char *pt_send = 0;
static uint8_t strflag = 0;
static uint8_t Rx_mLength;


void (*Tx_Handler)(void) = NULL;
void (*Rx_Handler)(void) = NULL;

static uint8_t TxState = TxREADY;
static uint8_t RxState = RxREADY;
/*-----------------------Helper Functions----------------------*/
static void Rx_StrFun(void)
{
    static uint8_t idx = 0;
    st_rec[idx] = RCREG; /* Read received data */
    Rx_mLength--;
	
    if(!Rx_mLength)
    {
        st_rec[idx+1] = 0;
        strflag = 1;
        idx = 0;
		RxState = RxREADY;
    }
    else
    {
        idx++;
    }
}
static void Tx_StrFun(void)
{
    static uint8_t i = 0;
	if(pt_send[i] != '\0')
		UART_SendNonBlocking(pt_send[i++]);
    else{
        i = 0;
        TXIE = 0; //Disable data register empty interrupt
        TxState = TxREADY;
    }
}
/*-------------------------------------------------------------*/
void UART_Init(void)
{
    SPBRG = MYSPBRG;
    TXSTA = 0x00; /* TXEN, ASYNC, Low Speed */
    RCSTA = 0x80; /* SPEN, CREN */
    
#if TRANSMMITION_ENABLE
    TXEN = 1;
#endif
#if RECEPTION_ENABLE
    CREN = 1;
#endif
#if ASYNCHRONOUS
    SYNC = 0;
#else
    SYNC = 1;
#endif

#if HIGH_SPEED
    BRGH = 1;
#else
    BRGH = 0;
#endif
    
	SetDir(DIO_PORTC, PIN6, INPUT);
	SetDir(DIO_PORTC, PIN7, INPUT);
    
}

/*--------------------------------------------------------*/
void UARTByte(unsigned char data)
{
    while(!TXIF);/* Wait for empty buffer */
    TXREG = data;
}
/*--------------------------------------------------------*/
void UART_SendNonBlocking(char c)
{
	TXREG = c;
}
/*--------------------------------------------------------*/
char UARTRead(void)
{
    while(!RCIF);
    return RCREG;
}
/*--------------------------------------------------------*/
char UARTReadNonBlocking(void)
{
    return RCREG;
}
/*--------------------------------------------------------*/
void UARTString(char *st)
{
    unsigned char i=0;
    while(st[i])
    {
        UARTByte(st[i++]);
    }
}
/*--------------------------------------------------------*/

void UART_Receiv_IntEn(void)
{
    RCIE=1; 
}
/*--------------------------------------------------------*/
void UART_Transmit_IntEN(void)
{
	TXIE = 1; /* Data register empty interrupt */
}
/*--------------------------------------------------------*/
void UART_StringNonBlocking(char *str)
{
    if(TxREADY == TxState)
    {
        pt_send = str;
        TxState = TxBUSY;
        UART_SetTxHandler(Tx_StrFun);
        
        UART_Transmit_IntEN();
        GLOBAL_INTERRUPT_ENABLE();
        PERIPHERAL_INTERRUPT_ENABLE();
    }
    
}
/*--------------------------------------------------------*/
uint8_t UART_ReadStringNonBlocking(char *str, uint8_t len)
{
    if(RxREADY == RxState){
		st_rec = str;
        Rx_mLength = len;
		UART_SetRxHandler(Rx_StrFun);
		UART_Receiv_IntEn(); /* Enable Reception interrupt */
		GLOBAL_INTERRUPT_ENABLE();
		PERIPHERAL_INTERRUPT_ENABLE();
		
		RxState = RxBUSY;
	}
    if(strflag == 1){
        strflag = 0;
        return 1;
    }
    return 0;
}
/*--------------------------------------------------------*/
void UART_SetTxHandler(void(*pf)(void))
{
    Tx_Handler = pf;
}
void UART_SetRxHandler(void(*pf)(void))
{
    Rx_Handler = pf;
}