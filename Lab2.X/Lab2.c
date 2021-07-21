/*
 * File:   Lab2.c
 * Author: swimm
 *
 * Created on 21 de julio de 2021, 09:22 AM
 */
// CONFIG1
#pragma config FOSC = INTRC_NOCLKOUT// Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = ON       // Power-up Timer Enable bit (PWRT enabled)
#pragma config MCLRE = OFF      // RE3/MCLR pin function select bit (RE3/MCLR pin function is digital input, MCLR internally tied to VDD)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = ON         // Low Voltage Programming Enable bit (RB3/PGM pin has PGM function, low voltage programming enabled)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)
#define _XTAL_FREQ 1000000
#define __delay_us(x) _delay((unsigned long)((x)*(_XTAL_FREQ/4000000.0)))

#include <xc.h>

int pot1, pot2, frec, tr, rc;

void __interrupt()isr(void){
    if(ADIF){
        if (ADCON0bits.CHS == 0){
            pot1 = ADRESH;
        }
        else{
            pot2 = ADRESH;
        }
        ADIF = 0;
    }
}

void main(void) {
    ANSEL = 0x03;
    ANSELH = 0x00;
    
    TRISA = 0x03;
    TRISB = 0x00;
    TRISC = 0x00;
    TRISD = 0x00;
    
    OSCCONbits.IRCF = 0B110;            //Oscilador a 1MHz
    OSCCONbits.OSTS = 0;
    OSCCONbits.SCS = 1;
    
    ADC_CONFIG(1);
    USART_CONFIG(1, 1, 1);
    
    INTCONbits.GIE = 1;
    INTCONbits.PEIE = 1;
    PIE1bits.ADIE = 1;
    PIE1bits.TXIE = 1;
    PIE1bits.RCIE = 1;
    
    while(1){
        if (ADCON0bits.GO == 0){
            if(ADCON0bits.CHS == 0){
                ADCON0bits.CHS = 1;
            }
            else{
                ADCON0bits.CHS = 0;
            }
            __delay_us(50);
            ADCON0bits.GO = 1;
        }
    }
}
