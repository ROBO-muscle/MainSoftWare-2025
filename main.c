/* 
 * File:   main.c
 * Author: takum
 *
 * Created on December 2, 2024, 5:32 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "config.h"
#include "function.h"
#include "struct.h"
#define FCY 64000000
#include "libpic30.h"
#include "user.h"
#include "wheel.h"


I2C_MSG_OBJ bno;
uint8_t data[8];
uint8_t i2c_data[];
int16_t jyrof; 
int16_t IR_Data;
uint8_t send_data;
uint8_t A[100];
bool t2_flag;
bool t3_flag;
bool I2C2_flag;
bool LINE_flag = true;
int LINEx_vec=0;
int LINEy_vec=0;
uint16_t IR_total;

/*
 * 
 */

int main(int argc, char** argv) {
    setup();
    LED1 = 1;
    bno.add = 0x28;
    bno.mode = 0;
    bno.ADDbyte = bno.add*2+bno.mode;
    bno.reg = 0x3d;
    bno.count = 0;
    bno.Data = data;
    data[0] = 0b00001100; 
    __delay_ms(1000);
    I2C_communication(bno);
    __delay_ms(500);
    bno.mode = 1;
    bno.ADDbyte = bno.add*2+bno.mode;
    bno.reg = 0x1A;
    bno.count = 1;                          
    bno.Data = data;
    I2C_communication(bno);
    __delay_ms(40);
    jyrof = ((i2c_data[1]*256+i2c_data[0])/16);
    LATAbits.LATA15 = 0;
    
    while(1){
        t3_flag = true;
        TMR3_start();
        while(t3_flag){}
        TMR3_stop();
        LED8=0;
        I2C_communication(bno);
        __delay_ms(20);
        LED1=~LED1;
        TRISEbits.TRISE7  = 1;
        LINE_flag = PORTBbits.RB2&& // fo
                PORTBbits.RB3&& // fi
                PORTBbits.RB4&& // lo
                PORTBbits.RB5&& // li
                PORTCbits.RC3&& // bo
                PORTCbits.RC2&& // bi
                PORTCbits.RC1&& // ro
                PORTEbits.RE7&& // ri
                (!LINEx_vec)&&(!LINEy_vec);
    
        if((!(PORTBbits.RB2&&PORTBbits.RB3&&PORTCbits.RC3&&PORTCbits.RC2)) && (LINEy_vec==0)){
            LINEy_vec=LINE_num*(PORTBbits.RB2&&PORTBbits.RB3)-LINE_num*(PORTCbits.RC3&&PORTCbits.RC2);
        }
        if((!(PORTBbits.RB4&&PORTBbits.RB5&&PORTCbits.RC1&&PORTEbits.RE7)) && (LINEx_vec==0)){
            LINEx_vec=LINE_num*(PORTBbits.RB4&&PORTBbits.RB5)-LINE_num*(PORTCbits.RC1&&PORTEbits.RE7);
        }
        rudder_funk;
        LINEx_vec+=(LINEx_vec<0)-(0<LINEx_vec);
        LINEy_vec+=(LINEy_vec<0)-(0<LINEy_vec);
        LED4 = !PORTBbits.RB2;
        LED5 = !PORTBbits.RB3;
        LED6 = (JYRO<10)*(-10<JYRO);
        KICK = hold_ball;
        LED4 = hold_ball; 
//        LED8 = !PORTEbits.RE7;// flont2x B0 x  RI x
    }
    
    return (EXIT_SUCCESS);
}
