/*
 * File:   Lab_2.c
 * Author: Ronaldo Arnulfo Macz
 *
 * Created on 4 de febrero de 2020, 09:38 PM
 */

// PIC16F887 Configuration Bit Settings

// 'C' source line config statements

// CONFIG1
#pragma config FOSC = INTRC_NOCLKOUT// Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF     // Power-up Timer Enable bit (PWRT disabled)
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
#define _XTAL_FREQ 8000000
#include <stdint.h>
#include <pic16f887.h>
#include "I2C.h"

uint8_t z;
uint8_t dato;
uint8_t CONTADOR = 0;
uint8_t UNIDADES = 0;
uint8_t DECENAS = 0;
uint8_t BOTON = 0;

void main(void) {
    
    /////////// CONFIGURACION DE PUERTOS////////////////////  
    TRISA = 0;
    TRISB = 0b00000011;                 //B0 Y B1 COMO ENTRADAS DIGITALES
    TRISD = 0;
    
    PORTA = 0;
    PORTB = 0;
    PORTD = 0;

    ANSEL = 0;
    ANSELH = 0;

    /////////// CONFIGURACIONES INTERRUPCIONES PUERTO B///////////////////////
    INTCON = 0;
    INTCONbits.GIE = 1;
    INTCONbits.RBIE = 1;
    INTCONbits.RBIF = 0;
    IOCB = 0;
    IOCBbits.IOCB0 = 1;
    IOCBbits.IOCB1 = 1;
    INTCONbits.PEIE = 1;
    
    I2C_Slave_Init(0x60);         //SE DEFINE ESTE SLAVE CON LA DIRECCION 0X60
    
    
    
    while(1){
        
        BOTON = 0;
        PORTA = CONTADOR;
        ADCON0bits.GO = 1;
       
    }
}

////////////////////////////////// INTERRUPCIONES //////////////////////////


void __interrupt() isr(void){
    
    
    if(RBIF == 1){
        RBIF = 0;
        if(BOTON == 0){
            if (PORTBbits.RB0 == 1){
             BOTON = 1;
             CONTADOR++;  
             if (CONTADOR >15){             //SE RESTRINGUE EL CONTADOR A 4 BITS
                 CONTADOR = 0;
             }
            }
            if (PORTBbits.RB1 == 1){
                BOTON = 1;
             if (CONTADOR == 0){           //SE RESTRINGUE EL CONTADOR A 4 BITS
                 CONTADOR = 15;
             }
             else {
                 CONTADOR--;
             }               
            }
        }
    }
    
    if(PIR1bits.SSPIF == 1){ 

        SSPCONbits.CKP = 0;
       
        if ((SSPCONbits.SSPOV) || (SSPCONbits.WCOL)){
            z = SSPBUF;                 // Read the previous value to clear the buffer
            SSPCONbits.SSPOV = 0;       // Clear the overflow flag
            SSPCONbits.WCOL = 0;        // Clear the collision bit
            SSPCONbits.CKP = 1;         // Enables SCL (Clock)
        }

        if(!SSPSTATbits.D_nA && !SSPSTATbits.R_nW) {
            //__delay_us(7);
            z = SSPBUF;                 // Lectura del SSBUF para limpiar el buffer y la bandera BF
            //__delay_us(2);
            PIR1bits.SSPIF = 0;         // Limpia bandera de interrupción recepción/transmisión SSP
            SSPCONbits.CKP = 1;         // Habilita entrada de pulsos de reloj SCL
            while(!SSPSTATbits.BF);     // Esperar a que la recepción se complete
            PORTD = SSPBUF;             // Guardar en el PORTD el valor del buffer de recepción
            __delay_us(250);
            
        }
        else if(!SSPSTATbits.D_nA && SSPSTATbits.R_nW){
            z = SSPBUF;
            BF = 0;
            SSPBUF = PORTA;
            SSPCONbits.CKP = 1;
            __delay_us(250);
            while(SSPSTATbits.BF);
        }
       
        PIR1bits.SSPIF = 0;    
        

    }        
    
    
}