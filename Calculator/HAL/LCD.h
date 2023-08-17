

#include <xc.h> // include processor files - each processor file is guarded.
#include "gpio.h"
#define _XTAL_FREQ 16000000
#define RS 0
#define EN 1
#define LCD_PRT DIO_PORTC
#define EN_DELAY 100

#define LCD_Char lcd_data

void lcd_cmd(unsigned char cmd);
void lcd_data(unsigned char data);
void LCD_init(void);
void LCD_SetCursor(char x, char y);
void LCD_String(char *st);
void LCD_SHL(void);
void LCD_SHR(void);
void LCD_Clear(void);
void LCD_Print(uint8_t r, uint8_t c, char *str);