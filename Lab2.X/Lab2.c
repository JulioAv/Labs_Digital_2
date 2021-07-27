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
#define _XTAL_FREQ 4000000
#define __delay_us(x) _delay((unsigned long)((x)*(_XTAL_FREQ/4000000.0)))

#define RS RC4
#define EN RC5
#define D0 RD0
#define D1 RD1
#define D2 RD2
#define D3 RB3
////////////////////////////
#define D4 RD4
#define D5 RB5
#define D6 RD6
#define D7 RD7

#include <xc.h>
#include <stdint.h>
#include "LCDh.h"
#include "adc.h"
#include "usart.h"


int pot1, pot2, frec, tr, rc, con, vol1, vol2;
char num[10] = {"0","1","2","3","4","5","6","7","8","9"};
char cen1, dec1, uni1, cen2, dec2, uni2;

void UART_write(unsigned char* word){   //Función que transmite datos
    while (*word != 0){                 //Verifica que el puntero aumente
        TXREG = (*word);                //Envía el caracter que toca de la cadena
        while(!TXSTAbits.TRMT);         //Espera a que se haya enviado el dato
        word++;                         //Aumenta el apuntador para ir al
    }                                   //siguente caracter
    return;
}

void __interrupt()isr(void){
    if(ADIF){
        if (ADCON0bits.CHS == 0){
            pot1 = ADRESH;
            vol1 = ((pot1/256)*5);
        }
        else{
            pot2 = ADRESH;
            vol2 = ((pot2/256)*500);
        }
        ADC_IF();
        ADIF = 0;
    }
    if (RCIF){
        if (RCREG == '+'){
            con++;
        }
        else if (RCREG == '-'){
            con--;
        }
        
        RCIF = 0;
    }
    return;
}

void main(void) {
    ANSEL = 0x03;
    ANSELH = 0x00;
    
    TRISA = 0x03;
    TRISB = 0x00;
    TRISC = 0x80;
    TRISD = 0x00;
    
    OSCCONbits.IRCF = 0B110;            //Oscilador a 4MHz
    OSCCONbits.OSTS = 0;
    OSCCONbits.SCS = 1;
    
    ADC_CONFIG(4);
    USART_CONFIG(4, 1, 1);
    
    INTCONbits.PEIE = 1;
    PIE1bits.ADIE = 1;
    //PIE1bits.TXIE = 1;
    PIE1bits.RCIE = 1;
    ADCON0bits.GO = 1;
    Lcd_Init();
    RCIF = 0;
    ADIF = 0;
    INTCONbits.GIE = 1;
    Lcd_Clear();
    
    while(1){
        cen1 = vol1/100;
        dec1 = ((vol1%100)/10);
        uni1 = ((vol1%100)%10);
        
        Lcd_Set_Cursor(1,1);
        Lcd_Write_String("S1:  S2:  S3:");
        Lcd_Set_Cursor(2,1);
        Lcd_Write_String(num[cen1]);
        
        __delay_ms(5000);
       
        
        //UART_write("Pot 1: \r \0");
       // UART_write(pot1);
        //__delay_ms(5000);
    }
}
