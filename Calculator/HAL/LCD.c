
#include <xc.h>
#include "LCD.h"
void lcd_cmd(unsigned char cmd)
{
    PinWrite(LCD_PRT, RS, LOW); /*Command register*/
	
	/*High nibble*/
    uint8_t val = GetPortValue(LCD_PRT);
	val = (val & 0x0F) | (cmd & 0xF0);
	PortWrite(LCD_PRT, val);
    
    PinWrite(LCD_PRT, EN, HIGH);
    __delay_us(EN_DELAY);
    PinWrite(LCD_PRT, EN, LOW);
    
    __delay_ms(2); /*Wait a bit*/
    
	/*Low nibble*/
    val = GetPortValue(LCD_PRT);
	val = (val & 0x0F) | (cmd<<4);
	PortWrite(LCD_PRT, val);
	
    PinWrite(LCD_PRT, EN, HIGH);
    __delay_us(EN_DELAY);
    PinWrite(LCD_PRT, EN, LOW);
    
}

void lcd_data(unsigned char data)
{
    PinWrite(LCD_PRT, RS, HIGH); /*Data register*/
	
    /*High nibble*/
    uint8_t val = GetPortValue(LCD_PRT);
	val = (val & 0x0F) | (data & 0xF0);
	PortWrite(LCD_PRT, val);
    
    PinWrite(LCD_PRT, EN, HIGH);
    __delay_us(EN_DELAY);
    PinWrite(LCD_PRT, EN, LOW);
    
    __delay_us(20);
    
    /*Low nibble*/
    val = GetPortValue(LCD_PRT);
	val = (val & 0x0F) | (data<<4);
	PortWrite(LCD_PRT, val);
	
    PinWrite(LCD_PRT, EN, HIGH);
    __delay_us(EN_DELAY);
    PinWrite(LCD_PRT, EN, LOW);
}

void LCD_init(void)
{
    SetPortDir(DIO_PORTC, OUTPUT); /*All output*/
    __delay_ms(20); /*For stable power*/
    lcd_cmd(0x33);
    __delay_ms(1);
    lcd_cmd(0x32);
    __delay_ms(1);
    
    lcd_cmd(0x28); /*Function set*/
    __delay_us(50);
    lcd_cmd(0x0E); /*Display on/off*/
    __delay_us(50);
    lcd_cmd(0x01); /*Clear*/
    __delay_ms(2);
    lcd_cmd(0x06); /*Entry mode set*/
    __delay_us(50);
}

void LCD_SetCursor(char x, char y)
{
    char add[] = {0x80, 0xC0};
    lcd_cmd(add[x-1] + (y-1));
    __delay_us(50);
}

void LCD_String(char *st)
{
    char i=0;
    while(st[i])
        lcd_data(st[i++]);
}

void LCD_SHL(void)
{
    lcd_cmd(0x18);
    __delay_us(50);
}

void LCD_SHR(void)
{
    lcd_cmd(0x1C);
    __delay_us(50);
}
void LCD_Clear(void)
{
    lcd_cmd(0x01); /*Clear*/
    __delay_ms(2);
}
void LCD_Print(uint8_t r, uint8_t c, char *str)
{
    LCD_SetCursor(r,c);
    LCD_String(str);
}