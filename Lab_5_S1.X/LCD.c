#include <stdint.h>
#include <pic16f887.h>
 #include <stdio.h>
 #include <stdlib.h>
#include "LCD.h"



void initLCD (void){
__delay_ms(15);

Lcd_Cmd(0x030);
__delay_ms(5);

Lcd_Cmd(0x030);
__delay_ms(11);

Lcd_Cmd(0x030);
__delay_us(160);


Lcd_Cmd(0x38);
Lcd_Cmd(0x10);
Lcd_Cmd(0x01);
Lcd_Cmd(0x06);
Lcd_Cmd(0x0C);
}



void Lcd_Cmd(uint8_t command){
    PORTBbits.RB6 = 0; 
    PORTD = command;
    PORTBbits.RB7 = 1;
    __delay_ms(4);
    PORTBbits.RB7 = 0;
}

void Lcd_Clear (void){
    Lcd_Cmd(0x01);
}

void Lcd_Set_Cursor(uint8_t posx, uint8_t posy){
    if(posy == 1){
        Lcd_Cmd (0x80 + posx - 1);
    }
    if(posy == 2){
        Lcd_Cmd (0xC0 + posx - 1);
    }
}

void Lcd_Write_Char(char var){
    PORTBbits.RB6 = 1;
    PORTD = var;
    PORTBbits.RB7 = 1;
    __delay_ms(4);
    PORTBbits.RB7 = 0;
}

void Lcd_Write_String(char *var){
    int i;
	for(i=0;var[i]!='\0';i++)
	   Lcd_Write_Char(var[i]);
}

void Lcd_Write_Int(uint8_t numero){
    char buffer [4];
    sprintf (buffer, "%d", numero); 
    Lcd_Write_String(buffer);
}