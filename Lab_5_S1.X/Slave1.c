/*
 * File:   Slave1.c
 * Author: Ronaldo Arnulfo Macz
 *
 * Created on 20 de febrero de 2020, 10:21 PM
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
#include "ADC.h"
#include <pic16f887.h>
#include "I2C.h"

//*****************************************************************************
// Definición de variables
//*****************************************************************************
#define _XTAL_FREQ 4000000
uint8_t z;
uint8_t dato;
uint8_t bandera = 0;
uint8_t ENT_1 = 0;
uint8_t ENT_2 = 0;
uint8_t DEC_1 = 0;
uint8_t DEC_2 = 0;
uint8_t TTL = 0;

float ADC_1 = 0; 
float ADC_2 = 0;
float DECIMAL1_1 = 0;
float DECIMAL2_2 = 0;

void main(void) {
    
    //////////////////CONFIGURACION DE PUERTOS////////////////////////////////
    
    ANSEL = 0b00000001;             //ANS0 COMO ENTRADA ANALOGICA
    ANSELH = 0;
    
    TRISA = 0b00000001;             //A0 COMO ENTRADA
    TRISB = 0;
    TRISD = 0;
    
    PORTA = 0;
    PORTB = 0;
    PORTD = 0;
    
    I2C_Slave_Init(0x50);           //SE DEFINE ESTE SLAVE CON LA DIRECCION 0X50
    
    //*************************************************************************
    // Loop infinito
    //*************************************************************************
    
    while(1){
        ADCCONFIG(0);               // SE LLAMA A LA CONFIGURACION DEL ADC Y DEFINIENDO EL 
        if(bandera){                // ANS0 COMO ENTRADA
            ADC_1 = ADRESH;
            PORTB = ADC_1;
            bandera = 0;
            ADCON0bits.GO_DONE = 1;
        }
    
    }
    return;
}


//*****************************************************************************
// Código de Interrupción 
//*****************************************************************************
void __interrupt() isr(void){
    
    if(ADCON0bits.GO_DONE == 0){        //INTERRUPCION DEL ADC
        bandera = 1;
        PIR1bits.ADIF = 0;
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
            SSPBUF = PORTB;
            SSPCONbits.CKP = 1;
            __delay_us(250);
            while(SSPSTATbits.BF);
        }
       
        PIR1bits.SSPIF = 0;    

    }        
}


