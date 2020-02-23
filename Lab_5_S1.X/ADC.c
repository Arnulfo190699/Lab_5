/*
 * File:   ADC.c
 * Author: Ronaldo Arnulfo Macz
 *
 * Created on 6 de febrero de 2020, 12:06 PM
 */

#include <pic16f887.h>
#include <stdint.h>

#include "ADC.h"

void ADCCONFIG (uint8_t ADnum){
    INTCONbits.GIE = 1;      //INTERRUPCION GLOBAL ACTIVADA
    INTCONbits.PEIE = 1;    // INTERRUPCION
    
    
    PIE1bits.ADIE = 1;      //CONVERTIDOR DE ADC
    PIR1bits.ADIF = 1;      //BANDERA
    
    ADCON0bits.ADCS1 = 0;
    ADCON0bits.ADCS0 = 1;          //  FOSC/8
    ADCON0bits.ADON = 1;           //ADC ENABLED
    
    
    switch(ADnum){          //SE SELECIONA QUE PIN ANALOGICO SE VA A USAR
        case 0:
            ADCON0bits.CHS3 = 0;
            ADCON0bits.CHS2 = 0;
            ADCON0bits.CHS1 = 0;
            ADCON0bits.CHS0 = 0;
            break;
            
        case 1:
            ADCON0bits.CHS3 = 0;
            ADCON0bits.CHS2 = 0;
            ADCON0bits.CHS1 = 0;
            ADCON0bits.CHS0 = 1;                
            break;
            
        case 2:
            ADCON0bits.CHS3 = 0;
            ADCON0bits.CHS2 = 0;
            ADCON0bits.CHS1 = 1;
            ADCON0bits.CHS0 = 0;                    
            break;
            
        case 3:
            ADCON0bits.CHS3 = 0;
            ADCON0bits.CHS2 = 0;
            ADCON0bits.CHS1 = 1;
            ADCON0bits.CHS0 = 1;                  
            break;
            
        case 4:
            ADCON0bits.CHS3 = 0;
            ADCON0bits.CHS2 = 1;
            ADCON0bits.CHS1 = 0;
            ADCON0bits.CHS0 = 0;                   
            break;
            
        case 5:
            ADCON0bits.CHS3 = 0;
            ADCON0bits.CHS2 = 1;
            ADCON0bits.CHS1 = 0;
            ADCON0bits.CHS0 = 1;                   
            break;
            
        case 6:
            ADCON0bits.CHS3 = 0;
            ADCON0bits.CHS2 = 1;
            ADCON0bits.CHS1 = 1;
            ADCON0bits.CHS0 = 0;  
            break;
            
        case 7:
            ADCON0bits.CHS3 = 0;
            ADCON0bits.CHS2 = 1;
            ADCON0bits.CHS1 = 1;
            ADCON0bits.CHS0 = 1;  
            break;
            
        case 8:
            ADCON0bits.CHS3 = 1;
            ADCON0bits.CHS2 = 0;
            ADCON0bits.CHS1 = 0;
            ADCON0bits.CHS0 = 0;  
            break;
            
        case 9:
            ADCON0bits.CHS3 = 1;
            ADCON0bits.CHS2 = 0;
            ADCON0bits.CHS1 = 0;
            ADCON0bits.CHS0 = 0;  
            break;
            
        case 10:
            ADCON0bits.CHS3 = 1;
            ADCON0bits.CHS2 = 0;
            ADCON0bits.CHS1 = 0;
            ADCON0bits.CHS0 = 1;  
            break;
            
        case 11:
            ADCON0bits.CHS3 = 1;
            ADCON0bits.CHS2 = 0;
            ADCON0bits.CHS1 = 1;
            ADCON0bits.CHS0 = 1;  
            break;
            
        case 12:
            ADCON0bits.CHS3 = 1;
            ADCON0bits.CHS2 = 1;
            ADCON0bits.CHS1 = 0;
            ADCON0bits.CHS0 = 0;  
            break;
            
        case 13:
            ADCON0bits.CHS3 = 1;
            ADCON0bits.CHS2 = 1;
            ADCON0bits.CHS1 = 0;
            ADCON0bits.CHS0 = 1;  
            break;
            
        case 14:
            ADCON0bits.CHS3 = 1;
            ADCON0bits.CHS2 = 1;
            ADCON0bits.CHS1 = 1;
            ADCON0bits.CHS0 = 0;  
            break;
            
        case 15:
            ADCON0bits.CHS3 = 1;
            ADCON0bits.CHS2 = 1;
            ADCON0bits.CHS1 = 1;
            ADCON0bits.CHS0 = 1;  
            break;
                  
    }
    ADCON1 = 0;
    ADCON0bits.GO_DONE = 1;
}