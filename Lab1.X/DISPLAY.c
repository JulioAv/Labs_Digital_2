/*
 * File:   DISPLAY.c
 * Author: swimm
 *
 * Created on 21 de julio de 2021, 01:26 PM
 */


#include <xc.h>
#include "display.h"

char display[16] = {0B00111111, 0B00000110, 0B01011011, 0B01001111, 
0B01100110, 0B01101101, 0B01111101, 0B00000111, 0B01111111, 0B01100111, 
0B01110111, 0B01111100, 0B00111001, 0B01011110, 0B01111001, 0B01110001};

int DISP(int valor) {
    return display[valor];
}
