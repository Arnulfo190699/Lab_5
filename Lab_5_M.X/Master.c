/*
 * File:   Master.c
 * Author: Ronaldo Arnulfo Macz
 *
 * Created on 19 de febrero de 2020, 03:26 PM
 */


#include <xc.h>
#include "I2C.h"
#include "LCD.h"
#include  <stdint.h>
#define _XTAL_FREQ 8000000



void main(void) {
|   ///////////////////////CONFIGURACION DE PUERTO ////////////////////////////
    
    TRISA = 0b00000011;
    TRISB = 0;
    TRISC = 0;
    TRISD = 0;
    
    ANSEL = 0b00000011;
    
    PORTA = 0;//Valor inicial de los puertos
    PORTB = 0;
    PORTC = 0;
    PORTD = 0;
    
    /////////////////////// LIBRERIA DE LCD //////////////////////////////////////////////////
    initLCD(); 
    Lcd_Clear();
    Lcd_Set_Cursor(1,1);
    Lcd_Write_String ("Val_1");
    Lcd_Set_Cursor(7,1);
    Lcd_Write_String ("Val_2");
    Lcd_Set_Cursor(13,1);
    Lcd_Write_String ("TTL");
    return;
}
