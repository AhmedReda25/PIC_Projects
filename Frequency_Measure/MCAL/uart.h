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
#define GLOBAL_INTERRUPT_ENABLE()      (GIE = 1)
#define GLOBAL_INTERRUPT_DISABLE()     (GIE = 0)

#define PERIPHERAL_INTERRUPT_ENABLE()  (PEIE = 1)
#define PERIPHERAL_INTERRUPT_DISABLE() (PEIE = 0)

#if HIGH_SPEED
#define MYSPBRG ((16000000UL/(16*MYBUAD))-1)
#else
#define MYSPBRG ((16000000/64/MYBUAD)-1)
#endif

#define STRING_COMPLETE   1
#define STRING_TERMINATE '0' //For Asynchronous string receive, assuming '0' character will be sent to mark the end of transfer

#define TxREADY 0
#define TxBUSY  1

#define RxREADY 0
#define RxBUSY  1

void UART_Init(void);
void UART_Receiv_IntEn(void);
void UART_Transmit_IntEN(void);
void UARTByte(unsigned char);
void UART_SendNonBlocking(char c);
char UARTRead(void);
char UARTReadNonBlocking(void);
void UARTString(char *st);
void UART_StringNonBlocking(char *st);
uint8_t UART_ReadStringNonBlocking(char *str, uint8_t len);

<<<<<<< HEAD
void UART_SetTxHandler(void(*pf)(void));
void UART_SetRxHandler(void(*pf)(void));
#endif
=======
#endif
>>>>>>> 5540774fe780e226359595f00df55d9822ffc4b7
