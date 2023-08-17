
#ifndef XC_HEADER_TEMPLATE_
#define XC_HEADER_TEMPLATE_


#include <xc.h> // include processor files - each processor file is guarded. 
#include "gpio.h" 
#define _XTAL_FREQ 16000000
#define RS 0
#define EN 1
#define LCD_PRT DIO_PORTD

#define EN_DELAY 100

void lcd_cmd(unsigned char cmd);
void lcd_data(unsigned char data);
void LCD_init(void);
void LCD_SetCursor(char x, char y);
void LCD_String(char *st);
void LCD_SHL(void);
void LCD_SHR(void);
void LCD_Char_Blink(void);
void LCD_Clear(void);
void LCD_Char_Blink_OFF(void);
// TODO Insert appropriate #include <>

// TODO Insert C++ class definitions if appropriate

// TODO Insert declarations

// Comment a function and leverage automatic documentation with slash star star
/**
    <p><b>Function prototype:</b></p>
  
    <p><b>Summary:</b></p>

    <p><b>Description:</b></p>

    <p><b>Precondition:</b></p>

    <p><b>Parameters:</b></p>

    <p><b>Returns:</b></p>

    <p><b>Example:</b></p>
    <code>
 
    </code>

    <p><b>Remarks:</b></p>
 */
// TODO Insert declarations or function prototypes (right here) to leverage 
// live documentation

//#ifdef	__cplusplus
//extern "C" {
//#endif /* __cplusplus */

    // TODO If C++ is being used, regular C code needs function names to have C 
    // linkage so the functions can be used by the c code. 

//#ifdef	__cplusplus
//}
//#endif /* __cplusplus */

#endif	 /* XC_HEADER_TEMPLATE_H */

