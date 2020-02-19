
#ifndef LCD
#define	LCD

#include <xc.h>
#include <stdint.h>
#define _XTAL_FREQ 8000000

void initLCD (void); 
void Lcd_Cmd (uint8_t command);
void Lcd_Clear (void);
void Lcd_Set_Cursor(uint8_t posy, uint8_t posx);
void Lcd_Write_Char(char var);
void Lcd_Write_String(char *var);
void Lcd_Write_Int(uint8_t numero);

#endif