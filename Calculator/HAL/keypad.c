#include "keypad.h"


static char Kval[4][4] = {{'7','8','9','/'},
                   {'4','5','6','*'},
                   {'1','2','3','-'},
                   {'c','0','=','+'}};
/*----------------------------------------------------------*/
void keypad_init(keypad kpd)
{
	/* Rows output */
	for(uint8_t pin = R0; pin <= R3; pin++)
	{
		SetDir(kpd.port, pin, OUTPUT);
		PinWrite(kpd.port, pin, HIGH);
	}
	
	/* Columns input */
	for(uint8_t pin = C3; pin <= C0; pin++)
	{
		SetDir(kpd.port, pin, INPUT);
	}
    __delay_ms(1);
}
/*----------------------------------------------*/

uint8_t get_key(keypad kpd)
{
	/* Check weather or not a key is pressed, All rows high, then check columns */
	
	PortWrite(kpd.port, 0x0F);
    __delay_ms(1);
    
	if( (GetPortValue(kpd.port) &0xF0) == 0 )
		return NO_PRESS;
	
    
	uint8_t row, col;
	for(row = R0; row <= R3; row++)
	{
		PortWrite(kpd.port, (1<<row));
		__delay_ms(1);
        
		if( (GetPortValue(kpd.port)&0xF0) != 0 ){ /* The pressed key is in this row */
			break;
		}
//		else{
//			PinWrite(kpd.port, row, LOW); /* Not this row */
//            __delay_ms(2);
//		}
	}
    
	
	/* At this point, a key is pressed and the row is determined */
    
	/* Getting the column */
    uint8_t mask = (GetPortValue(kpd.port)) & 0xF0;
    
	switch(mask)
	{
		case 0x10: col = 3; break;
		case 0x20: col = 2; break;
		case 0x40: col = 1; break;
		case 0x80: col = 0; break;
	}
//	while((GetPortValue(kpd.port)) & 0xF0); /* Loop till the user release the key */
    __delay_ms(250);
	return Kval[row][col];
	
}






