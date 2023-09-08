

#include "uart.h"
static char st[15];
static uint8_t strflag = 0;
static char *pt_send = 0;

void UART_Init(void)
{
    SPBRG = MYSPBRG;
    TXSTA = 0x00;
    RCSTA = 0x80; /* UART enable */
    
#if TRANSMMITION_ENABLE
    TXEN = 1;
#endif
#if RECEPTION_ENABLE
    RCEN = 1;
#endif
#if ASYNCHRONOUS
    SYNC = 0;
#else
    SYNC = 1;
#endif
    
	SetDir(DIO_PORTC, PIN6,INPUT);
	SetDir(DIO_PORTC, PIN7,INPUT);
    
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
	UART_SendNonBlocking(str[0]);
    pt_send = str;
    UART_Transmit_IntEN();
}
/*--------------------------------------------------------*/
uint8_t UART_ReadStringNonBlocking(char *str)
{
    UART_Receiv_IntEn(); /* Enable Reception interrupt */
    GLOBAL_INTERRUPTENABLE();
    PERIPHERAL_INTERRUPTENABLE();
    
    if(strflag == 1)
    {
        strcpy(str,st);
        strflag = 0;
        return 1;
    }
    return 0;
}
/*--------------------------------------------------------*/
//void __interrupt() _ISR(void)
//{
//    static uint8_t i = 1;
//    static uint8_t idx = 0;
//	if(TXIF && TXIE)
//	{
//		
//		if(pt_send[i] != '\0')
//			UART_SendNonBlocking(pt_send[i++]);
//       else{
//           i = 1;
//           TXIE = 0;
//       }
//           
//       //TXIF = 0;
//
//	}
//    if(RCIF && RCIE)
//    {
//        st[idx] = RCREG; /* Read received data */
//        
//        //UART_SendNonBlocking(st[idx]);
//        if('0' == st[idx])
//        {
//            st[idx] = 0;
//            strflag = 1;
//            idx = 0;
//        }
//        else
//        {
//            UARTByte(st[idx++]);
//        }
//        
//        RCIF = 0;
//    }
//}