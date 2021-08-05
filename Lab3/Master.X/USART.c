/*
 * File:   USART.c
 * Author: swimm
 *
 * Created on 21 de julio de 2021, 09:36 AM
 */


#include <xc.h>

void USART_CONFIG(int frec, tr, rc){
    RCSTAbits.SPEN = 1;
    TXSTAbits.SYNC = 0;
    TXSTAbits.TX9 = 0;
    RCSTAbits.RX9 = 0;
    switch(frec){
        case 4:
            SPBRG = 25;
            TXSTAbits.BRGH = 1;
            BAUDCTLbits.BRG16 = 0;
            break;
        case 8:
            SPBRG = 12;
            TXSTAbits.BRGH = 0;
            BAUDCTLbits.BRG16 = 0;
            break;     
    }
    if(tr==1){
        TXEN = 1;
    }
    else{
        TXEN = 0;
    }
    if(rc == 1){
        RCSTAbits.CREN = 1;
    }
    else{
        RCSTAbits.CREN = 0;
    }
}

void UART_write(unsigned char* word){   //Función que transmite datos
    while (*word != 0){                 //Verifica que el puntero aumente
        TXREG = (*word);                //Envía el caracter que toca de la cadena
        while(!TXSTAbits.TRMT);         //Espera a que se haya enviado el dato
        word++;                         //Aumenta el apuntador para ir al
    }                                   //siguente caracter
    return;
}
