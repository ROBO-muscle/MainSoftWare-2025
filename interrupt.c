#include "xc.h"
#include "function.h"
#include "struct.h"
#include "user.h"
#include "wheel.h"
#define FCY 64000000
#include "libpic30.h"
#include "cam.h"
#include <stdbool.h>
extern uint8_t i2c_data[8];
extern uint8_t jyrof;
extern bool t2_flag;
extern bool t3_flag;
extern int16_t IR_Data;
int IR_flag = 0;
extern bool LINE_flag;
extern int LINEx_vec;
extern int LINEy_vec;
extern bool ball_flag;
uint8_t IR_sum[16] , now = 0;
extern uint16_t IR_total;

void __attribute__((interrupt,no_auto_psv)) _AD1Interrupt (void){
    IFS0bits.AD1IF = 0;
}

void __attribute__((interrupt,no_auto_psv)) _U1RXInterrupt (void){
    IFS0bits.U1RXIF = 0;
}

void __attribute__((interrupt,no_auto_psv)) _U2RXInterrupt (void){
    LED3 = ~LED3;
    uint8_t data = U2RXREG;
    Receive_from_cam(data);
    IFS1bits.U2RXIF = 0;
}

void __attribute__((interrupt,no_auto_psv)) _T2Interrupt (void){
    IFS0bits.T2IF = 0;
}

void __attribute__((interrupt,no_auto_psv)) _CNInterrupt (void){
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
//    rudder_funk;
    LINEx_vec+=(LINEx_vec<0)-(0<LINEx_vec);
    LINEy_vec+=(LINEy_vec<0)-(0<LINEy_vec);
    IFS1bits.CNIF = 0;
}

void __attribute__((interrupt,no_auto_psv)) _T3Interrupt (void){
    IFS0bits.T3IF = 0;
    IR_sum[0]  += !PORTAbits.RA7;
    IR_sum[1]  += !PORTDbits.RD13;
    IR_sum[2]  += !PORTDbits.RD12;
    IR_sum[3]  += !PORTDbits.RD11;
    IR_sum[4]  += !PORTDbits.RD10;
    IR_sum[5]  += !PORTDbits.RD9;
    IR_sum[6]  += !PORTFbits.RF3;
    IR_sum[7]  += !PORTFbits.RF5;
    IR_sum[8]  += !PORTFbits.RF4;
    IR_sum[9]  += !PORTBbits.RB15;
    IR_sum[10] += !PORTBbits.RB14;
    IR_sum[11] += !PORTGbits.RG8;
    IR_sum[12] += !PORTGbits.RG6;
    IR_sum[13] += !PORTEbits.RE6;
    IR_sum[14] += !PORTEbits.RE5;
    IR_sum[15] += !PORTEbits.RE4;
    
    TRISDbits.TRISD9  = 1;
    TRISFbits.TRISF3  = 1;
    TRISFbits.TRISF5  = 1;
    TRISFbits.TRISF4  = 1;
    TRISBbits.TRISB15 = 1;
    TRISBbits.TRISB14 = 1;
    TRISGbits.TRISG8  = 1;
    TRISGbits.TRISG6  = 1;
    TRISEbits.TRISE6  = 1;
    TRISEbits.TRISE5  = 1;
    TRISEbits.TRISE4  = 1;
    IR_flag++;
    if(IR_flag >= 100){
        t3_flag = false;
        IR_flag = 0;
        IR_Data = atan2(IR_sum[12] - IR_sum[4],IR_sum[0] - IR_sum[8])/3.141592*180;
        IR_total = 0;
        for(int i = 0;i < 16;i++){
            IR_total += IR_sum[i];
            IR_sum[i] = 0;
        }
    }
}
