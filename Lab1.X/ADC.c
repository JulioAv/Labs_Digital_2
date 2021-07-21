/*
 * File:   ADC.c
 * Author: swimm
 *
 * Created on 15 de julio de 2021, 03:34 PM
 */
#define _XTAL_FREQ 1000000
#define __delay_us(x) _delay((unsigned long)((x)*(_XTAL_FREQ/4000000.0)))


#include <xc.h>
#include "adc.h"

void ADC_CONFIG(void){
    ADCON0bits.ADCS = 0B00;
    ADCON0bits.ADON = 1;
    ADCON0bits.CHS = 0;
    ADCON1bits.ADFM = 0;
    ADCON1bits.VCFG0 = 0;
    ADCON1bits.VCFG1 = 0;
    ADCON0bits.GO = 0;
    
}

void ADC_IF(void){
    if(ADCON0bits.GO == 0){
            __delay_us(50);
            ADCON0bits.GO = 1;
        }
        
}
