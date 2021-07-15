/*
 * File:   Lab1.c
 * Author: swimm
 *
 * Created on 15 de julio de 2021, 10:57 AM
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
#pragma config WRT = OFF 

#include <xc.h>

void __interrupt()isr(void){
    if (RBIF){
        
        if(RB0 == 0){
            PORTD++;
        }
        else if(RB1 == 0){
            PORTD--;
        }
        
    }  
    RBIF = 0;
}

void main(void) {
    ANSEL = 0x00;
    ANSELH = 0x00;
    
    TRISA = 0x00;
    TRISB = 0x03;
    TRISC = 0x00;
    TRISD = 0x00;
    
    PORTA = 0;
    PORTB = 0;
    PORTC = 0;
    PORTD = 0;
    
    OSCCONbits.IRCF = 0B100;
    OSCCONbits.OSTS = 0;
    OSCCONbits.SCS = 1;
    
    OPTION_REGbits.nRBPU = 0;
    WPUB = 0x03;
    IOCB = 0x03;
    
    INTCONbits.GIE = 1;
    INTCONbits.RBIE = 1;
    
    while(1){
        
    }
}
