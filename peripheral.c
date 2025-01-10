#include "xc.h"
#include "function.h"
#include "struct.h"
#include "user.h"
#define FCY 64000000
#include "libpic30.h"
#include <math.h>
#include <stdbool.h>

void U1Write(uint8_t Data){
    U1TXREG = Data;
}

void TMR2_start(){
    T2CONbits.TON = 1;
}

void TMR2_stop(){
    T2CONbits.TON = 0;
}

void TMR3_start(){
    T3CONbits.TON = 1;
}

void TMR3_stop(){
    T3CONbits.TON = 0;
}
