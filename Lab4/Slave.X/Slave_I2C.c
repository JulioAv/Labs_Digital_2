/*
 * File:   Slave_I2C.c
 * Author: swimm
 *
 * Created on 8 de agosto de 2021, 06:50 PM
 */
#pragma config FOSC = INTRC_NOCLKOUT// Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = ON       // Power-up Timer Enable bit (PWRT enabled)
#pragma config MCLRE = OFF      // RE3/MCLR pin function select bit (RE3/MCLR pin function is digital input, MCLR internally tied to VDD)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF         // Low Voltage Programming Enable bit (RB3/PGM pin has PGM function, low voltage programming enabled)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)
#define _XTAL_FREQ 8000000
#define __delay_us(x) _delay((unsigned long)((x)*(_XTAL_FREQ/4000000.0)))


#include <xc.h>
#include "adc.h"
#include "I2C_2.h"

char z, pot, con, val;

void __interrupt()isr(void){
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
            z = SSPBUF;             // Guardar en el PORTD el valor del buffer de recepción
            __delay_us(250);
            
        }else if(!SSPSTATbits.D_nA && SSPSTATbits.R_nW){
            z = SSPBUF;
            BF = 0;
            SSPBUF = val;
            SSPCONbits.CKP = 1;
            __delay_us(250);
            while(SSPSTATbits.BF);
        }
       
        PIR1bits.SSPIF = 0;    
    }
    if (ADIF){
        pot = ADRESH;
        ADIF = 0;
    }
    if(RBIF){
        if(RB0==0){
            con++;
        }
        if(RB1==0){
            con--;
        }
        RBIF = 0;
    }
}

void setup(){
    ANSEL = 0x01;
    ANSELH = 0x00;
    
    TRISA = 0x03;
    TRISB = 0x03;
    TRISC = 0x00;
    TRISD = 0x00;
    
    OSCCONbits.IRCF = 0B111;
    OSCCONbits.SCS = 1;
    OSCCONbits.OSTS = 0;
    
    if(RA1==0){
        ADC_CONFIG(8);
        PIE1bits.ADIE = 1;
        INTCONbits.PEIE = 1;
        INTCONbits.GIE = 1;

        I2C_Slave_Init(0x50);
    }
    else if(RA1==1){
        
        INTCONbits.RBIE = 1;
        IOCB = 0x03;
        OPTION_REGbits.nRBPU = 0;
        OPTION_REGbits.INTEDG = 1;
        WPUB = 0x03;
        con = 0;
        I2C_Slave_Init(0x30);
    }
}

void main(void) {
    setup();
    while(1){
    
        if(RA1==0){
            while(1){
                ADC_IF();
                val = pot;
            }
        }
        else if(RA1==1){
            while(1){
                PORTD = con;
                val = con;
                if(con==16){
                    con = 0;
                }
                else if(con==255){
                    con = 15;
                }
            }
        }
    }
}
