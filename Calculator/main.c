


#include <xc.h>
#include <stdio.h>
#include "calc.h"

#include "LCD.h"
#include "Stack.h"
#include "keypad.h"
#include "gpio.h"

char pressed_key;
char str[15] , rpn[15];
char idx = 0;
uint8_t result;
void main(void) {
    
    keypad kpd = {.port = DIO_PORTB};
    keypad_init(kpd);
    LCD_init();
    
    LCD_Print(1,1,"RPN Calculator");
    __delay_ms(1000);
    LCD_Clear();
    while(1){
        do{
            pressed_key = get_key(kpd);
            if(pressed_key == 'c'){
                LCD_Clear();
                idx = 0;
            }else if(pressed_key == '='){
                str[idx] = 0; /* Terminate the expression string */
                idx = 0;
                LCD_Char(pressed_key);
            }
            else if(pressed_key != NO_PRESS){
                str[idx++] = pressed_key;
                LCD_Char(pressed_key);
            }
                
        }while(pressed_key != '=');
        
        TORPN_MutiDigit(str, rpn);
        result = Calc_RPN_MutiDigit(rpn);
            
        sprintf(rpn, "%d", result);
        LCD_SetCursor(2,14);
        LCD_String(rpn);
   }
    return;
}
