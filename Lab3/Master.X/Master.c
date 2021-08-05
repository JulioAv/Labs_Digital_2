/*
 * File:   Master.c
 * Author: swimm
 *
 * Created on 30 de julio de 2021, 10:39 AM
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
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3/PGM pin has PGM function, low voltage programming enabled)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)
#define _XTAL_FREQ 8000000
#define __delay_us(x) _delay((unsigned long)((x)*(_XTAL_FREQ/4000000.0)))


#include <xc.h>
#include "SPI.h"
#include "adc.h"
#include "usart.h"
#include <stdio.h>

char pot1, pot2, potsel, x, buffer[5], vol1, vol2;
int frec, tr, rc;

void __interrupt()isr(void){
    if (RCIF){
        if (RCREG == '0'){
            x = 1;
        }
        PORTA = RCREG;
        RCIF = 0;
    }
    return;
}


void setup(){
    ANSEL = 0x00;
    ANSELH = 0x00;
    
    TRISA = 0x00;
    TRISB = 0x00;
    TRISC = 0x90;       //1001 0000
    TRISD = 0x00;
    potsel = 0;
    PORTA = 0xFF;
    
    USART_CONFIG(8, 1, 1);
    
    OSCCONbits.IRCF = 0B111;        //4MHz
    OSCCONbits.OSTS = 0;
    OSCCONbits.SCS = 1;
    
    spiInit(SPI_MASTER_OSC_DIV4, SPI_DATA_SAMPLE_MIDDLE, SPI_CLOCK_IDLE_LOW, SPI_IDLE_2_ACTIVE);
    
    INTCONbits.PEIE = 1;
    PIE1bits.RCIE = 1;
    PIR1bits.RCIF = 0;
    INTCONbits.GIE = 1;
    x = 1;

}


void main(void) {
    setup();
    
    while(1){
        RC2 = 0;        //slave select
        __delay_ms(1);
        
        spiWrite(potsel);
        pot1 = spiRead();
        __delay_ms(1);
        spiWrite(potsel);
        pot2 = spiRead();
        __delay_ms(1);
        
        __delay_ms(1);
        
        RC2 = 1;        //slave deselect

        PORTB = pot1;
        PORTD = pot2;
        
        vol1 = (pot1*0.01961);
        vol2 = (pot2*0.01961);
        
        if(x == 1){
            UART_write("Pot 1: ");
            sprintf(buffer, "%dV " , vol1);
            UART_write(buffer);
            UART_write(" Pot 2: ");
            sprintf(buffer, "%dV", vol2);
            UART_write(buffer);
            UART_write("\r \0");
            x = 0;
        }
    }
}
