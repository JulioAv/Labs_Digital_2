/*
 * File:   Master_I2C.c
 * Author: swimm
 *
 * Created on 8 de agosto de 2021, 05:31 PM
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

#include "I2C_2.h"
#include <xc.h>
#include "LCD.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

char pot, con, cen, dec, uni, vol, buffer[], tem1, tem2;
int temp;

void Division(char y){
        cen = (y/100);
        dec = ((y%100)/10);
        uni = ((y%100)%10);
}

void setup(){
    ANSEL = 0x00;
    ANSELH = 0x00;
    
    TRISA = 0x00;
    TRISB = 0x00;
    TRISC = 0x00;
    TRISD = 0x00;
    PORTB = 0;
    
    OSCCONbits.IRCF = 0B111;
    OSCCONbits.OSTS = 0;
    OSCCONbits.SCS = 1;
    
    I2C_Master_Init(100000);
    Lcd_Init();
    Lcd_Clear();
    Lcd_Set_Cursor(1,1);
    Lcd_Write_String("Pot: Con: Temp:");
}

void main(void) {
    setup();
    while(1){
        
        I2C_Master_Start();
        I2C_Master_Write(0x51);
        pot = I2C_Master_Read(0);
        I2C_Master_Stop();
        __delay_ms(200);  
        
        vol = pot*0.01961;
        Lcd_Set_Cursor(2,1);
        sprintf(buffer, " %dV ", vol);
        Lcd_Write_String(buffer);
        
        I2C_Master_Start();
        I2C_Master_Write(0x31);
        con = I2C_Master_Read(0);
        I2C_Master_Stop();
        __delay_ms(200);
        
        Division(con);
        sprintf(buffer, "  %d", dec);
        Lcd_Write_String(buffer);
        sprintf(buffer, "%d", uni);
        Lcd_Write_String(buffer);
        
        I2C_Master_Start();
        I2C_Master_Write(0x90);
        I2C_Master_Write(0xEE);
        I2C_Master_Stop();
        __delay_ms(200);
        
        I2C_Master_Start();
        I2C_Master_Write(0x90);
        I2C_Master_Write(0xAA);
        I2C_Master_Stop();
        __delay_ms(200);
        
        I2C_Master_Start();
        I2C_Master_Write(0x91);
        tem1 = I2C_Master_Read(0);
        tem2 = I2C_Master_Read(0);
        I2C_Master_Stop();
        __delay_ms(200);
        
        temp = tem1+tem2;
        temp = (temp*125)/(31488);
        
        Division(tem1);
        sprintf(buffer, "   %d", cen);
        Lcd_Write_String(buffer);
        sprintf(buffer, "%d", dec);
        Lcd_Write_String(buffer);
        sprintf(buffer, "%d", uni);
        Lcd_Write_String(buffer);
        
    }
    return;
}
