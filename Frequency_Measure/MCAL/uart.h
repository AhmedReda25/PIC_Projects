#ifndef UART_H
#define UART_H

#include <xc.h>
#include <stdint.h>
#include "string.h"
#include "bitmath.h"
#include "gpio.h"
/*----------------------------------------User_Config---------------------------------------------*/
#define HIGH_SPEED 0

#define MYBUAD 9600


#define TRANSMMITION_ENABLE 1
#define RECEPTION_ENABLE    1
#define ASYNCHRONOUS        1
/*--------------------------------------------------------------------------------------------------*/
#define GLOBAL_INTERRUPTENABLE()     (GIE = 1)
#define GLOBAL_INTERRUPTDISABLE()    (GIE = 0)

#define PERIPHERAL_INTERRUPTENABLE() (PEIE = 1)
#define PERIPHERAL_INTERRUPTDISABLE() (PEIE = 0)

#if HIGH_SPEED
#define MYSPBRG ((16000000UL/16/MYBUAD)-1)
#else
#define MYSPBRG ((16000000/64/MYBUAD)-1)
#endif

#define STRING_COMPLETE   1
#define STRING_TERMINATE '0'

void UART_Init(void);
void UART_Receiv_IntEn(void);
void UART_Transmit_IntEN(void);
void UARTByte(unsigned char);
void UART_SendNonBlocking(char c);
char UARTRead(void);
char UARTReadNonBlocking(void);
void UARTString(char *st);
void UART_StringNonBlocking(char *st);
uint8_t UART_ReadStringNonBlocking(char *st);


#endif