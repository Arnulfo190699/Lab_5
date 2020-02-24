/*
 * File:   Master.c
 * Author: Ronaldo Arnulfo Macz
 *
 * Created on 19 de febrero de 2020, 03:26 PM
 */

// PIC16F887 Configuration Bit Settings

// 'C' source line config statements

// CONFIG1
#pragma config FOSC = INTRC_NOCLKOUT// Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // RE3/MCLR pin function select bit (RE3/MCLR pin function is digital input, MCLR internally tied to VDD)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>

#include <stdint.h>
#include "I2C.h"
#include "LCD.h"
#include  <stdint.h>
#define _XTAL_FREQ 4000000


uint8_t VAL_1 = 0;
uint8_t VAL_2 = 0;
uint8_t ENT_1 = 0;
uint8_t DEC_1 = 0;
uint8_t DEC_2 = 0;


void main(void) {
///////////////////////CONFIGURACION DE PUERTOS ////////////////////////////
    
    TRISA = 0b11111111;                 //PUERTO A COMO SALIDA DIGITAL
    TRISB = 0;
    TRISC = 0;
    TRISD = 0;
    
    ANSEL = 0;
    
    PORTA = 0;//Valor inicial de los puertos
    PORTB = 0;
    PORTC = 0;
    PORTD = 0;
    
/////////////////////// LIBRERIA DE LCD //////////////////////////////////////////////////
    initLCD(); 
    Lcd_Clear();
    I2C_Master_Init(100000);            //DEFINIMOS LA FRECUENCIA DE LA LCD A 1KHZ
    Lcd_Clear();                        //SE LIMPIA LA LCD
    
    Lcd_Set_Cursor(1,1);                //SE DEFINEN LOS VALORES ESTATICOS DE LA LCD
    Lcd_Write_String ("S1");
    Lcd_Set_Cursor(7,1);
    Lcd_Write_String ("S2");
    Lcd_Set_Cursor(13,1);
    Lcd_Write_String ("S3");
    
    while(1){
   
     
        I2C_Master_Start();
        I2C_Master_Write(0x51);         //LEE LA DIRECCIÒN DEL SLAVE_1
        VAL_1 = I2C_Master_Read(0);     //GUARDA EL VALOR QUE LEE DEL SLAVE_1 
        I2C_Master_Stop();
        __delay_ms(10);
        
        I2C_Master_Start();            
        I2C_Master_Write(0x61);          //LEE LA DIRECCIÒN DEL SLAVE_2
        VAL_2 = I2C_Master_Read(0);      //GUARDA EL VALOR QUE LEE DEL SLAVE_2
        I2C_Master_Stop();
        __delay_ms(10);
        
        VAL_1 = VAL_1 * 5/255;          //CONVIERTE EL VALOR DEL POTENCIOMETRO A UN RANGO DE 0 Y 5 VOLTEOS
        ENT_1 = VAL_1;
        DEC_2 = (VAL_1 - ENT_1)*100;
        DEC_1= DEC_2;
         
         
        Lcd_Set_Cursor(1,2);            //MUESTRA EL VALOR DEL POTENCIOMETRO EN LA LCD
        Lcd_Write_Int(ENT_1);
        Lcd_Write_Char('.');
        if (DEC_1 >= 10){
            Lcd_Write_Int(DEC_1);
        }else{
            Lcd_Write_Char('0');
            Lcd_Write_Int(DEC_1);
        }
        
        
        if(VAL_2 < 10){                 //MUESTRA EL VALOR DEL CONTADOR EN LA LCD
            Lcd_Set_Cursor(7,2);
            Lcd_Write_String("0");
            Lcd_Write_Int(VAL_2);
        }else{
            Lcd_Set_Cursor(7,2);
            Lcd_Write_Int(VAL_2);
        }        
        
    }
    
}