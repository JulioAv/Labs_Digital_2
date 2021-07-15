/*
 * File:   Lab0.c
 * Author: Julio Avila
 *
 * Created on 11 de julio de 2021, 05:02 PM
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


#include <xc.h>

char display[10] = {0B00111111, 0B00000110, 0B01011011, 0B01001111, 
0B01100110, 0B01101101, 0B01111101, 0B01000111, 0B01111111, 0B01100111};
//Valores para el display

char modo = 1;
char val;
char cont1=0;
char cont2=0;

void __interrupt()isr(void){
    if (RBIF){
        PORTB = PORTB;
        modo = 2;
        RBIF = 0;
    }
    if (T0IF){
        if (modo==2){
            val--;
            PORTA = val;
            
        }
        TMR0 = 12;
        
        
        T0IF = 0;
    }
    
}

void main(void) {
    ANSEL = 0x00;
    ANSELH = 0x00;
    
    TRISA = 0x00;
    TRISB = 0x07;
    TRISC = 0x00;
    TRISD = 0x00;
    TRISE = 0x00;
    
    OSCCONbits.IRCF = 0B010;    //Oscilador a 250KHz
    OSCCONbits.OSTS = 0;
    OSCCONbits.SCS = 1;
    
    OPTION_REGbits.nRBPU = 0;
    OPTION_REGbits.T0CS = 0;
    OPTION_REGbits.T0SE = 0;
    OPTION_REGbits.PSA = 0;
    OPTION_REGbits.PS = 0B111;
    TMR0 = 12;
    IOCB = 0x06;
    
    WPUB = 0x07;
    
    PORTA = 0;
    
    PORTC = display[3];
    PORTD = 0;
    
    INTCONbits.GIE = 1;
    INTCONbits.T0IE = 1;
    INTCONbits.RBIE = 1;
    INTCONbits.INTE = 0;
    
    INTCONbits.RBIF = 0;
    INTCONbits.T0IF = 0;
    
    PORTB = 0B00001000;
    modo = 1;
    val = 3;
    
    while (1){
        //PORTA = val;
        PORTE = modo;
        if (val==3){
            PORTC = display[3];
            PORTB = 0x08;
        }
        else if (val==2){
            PORTC = display[2];
            PORTB = 0x08;
        }
        else if (val==1){
            PORTC = display[1];
            PORTB = 0x10;
        }
        else {
            PORTC = display[0];
            PORTB = 0x20;
            val = 3;
            modo = 1;
        }
        
    }
    
}
