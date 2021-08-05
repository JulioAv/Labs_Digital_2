/*
 * File:   Slave.c
 * Author: swimm
 *
 * Created on 30 de julio de 2021, 11:01 AM
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

char pot1, pot2, potsel, data, temp;

void __interrupt()isr(void){
    if (ADIF){
        if (ADCON0bits.CHS == 0){
            pot1 = ADRESH;
        }
        else{
            pot2 = ADRESH;
        }
        
        ADIF = 0;
    }
    if(SSPIF == 1){
        potsel = spiRead();
        spiWrite(pot1);
        potsel = spiRead();
        spiWrite(pot2);
        SSPIF = 0;
    }
}

void setup(){
    ANSEL = 0x03;
    ANSELH = 0x00;
    
    TRISA = 0x23;       //0010 0011
    TRISB = 0x00;
    TRISC = 0x18;       //0001 1000
    TRISD = 0x00;       //0010 1000
   
    ADC_CONFIG(8);
    
    OSCCONbits.IRCF = 0B111;        //4MHz
    OSCCONbits.OSTS = 0;
    OSCCONbits.SCS = 1;
    
    PIE1bits.ADIE = 1; 
    INTCONbits.PEIE = 1;        // Habilitamos interrupciones PEIE
    PIR1bits.SSPIF = 0;         // Borramos bandera interrupción MSSP
    PIE1bits.SSPIE = 1;         // Habilitamos interrupción MSSP
    
    spiInit(SPI_SLAVE_SS_EN, SPI_DATA_SAMPLE_MIDDLE, SPI_CLOCK_IDLE_LOW, SPI_IDLE_2_ACTIVE);
    INTCONbits.GIE = 1; 
}

void main(void) {
    setup();
    
    while (1){
        ADC_IF();
        //spiWrite(pot1);
        
    }
}
