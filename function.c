/* 
 * File:   function.c
 * Author: takum
 *
 * Created on December 7, 2024, 2:30 PM
 */

#include "xc.h"
#include "function.h"
#include "struct.h"
#include "user.h"
#define FCY 64000000
#include "libpic30.h"
#include <math.h>
#include <stdbool.h>
I2C_MSG_OBJ msg;
uint8_t i2c_flag = 0;
uint8_t count;
extern uint8_t i2c_data[8];
extern int16_t jyrof;

void __attribute__((interrupt,no_auto_psv)) _MI2C2Interrupt	(void){
    
    if(msg.mode == 0){
        if(i2c_flag == 0&&I2C2STATbits.S == 1){
            I2C2TRN = msg.ADDbyte;
            i2c_flag++;
        }
        else if(i2c_flag == 1){
            I2C2TRN = msg.reg;
            i2c_flag++;
        }
        else if(i2c_flag == 2){
            I2C2TRN = msg.Data[0];
            i2c_flag++;
        }
        else if(i2c_flag == 3){
            I2C2CONbits.PEN = 1;
            i2c_flag++;
        }
    }
    else{
        if(i2c_flag == 0&&I2C2STATbits.S == 1){
            I2C2TRN = msg.ADDbyte - 1;
            i2c_flag++;
        }
        else if(i2c_flag == 1){
            I2C2TRN = msg.reg;
            i2c_flag = 3;
        }
        else if(i2c_flag == 3){
            I2C2CONbits.RSEN = 1;
            i2c_flag++;
        }
        else if(i2c_flag == 4&&I2C2STATbits.S == 1){
            I2C2TRN = msg.ADDbyte;
            i2c_flag++;
        }
        else if(i2c_flag == 5){
            I2C2CONbits.RCEN = 1;
            i2c_flag++;
        }
        else if(i2c_flag == 6 && I2C2STATbits.RBF == 1){
            i2c_data[count] = I2C2RCV;
            if(count == msg.count){
                I2C2CONbits.ACKDT = 1;
                i2c_flag++;
                LATBbits.LATB0 =~ LATBbits.LATB0;
            }
            else{
                I2C2CONbits.ACKDT = 0;
                count++;
            }
            I2C2CONbits.ACKEN = 1;
        }
        else if(i2c_flag == 6){
            I2C2CONbits.RCEN = 1; 
        }
        else if(i2c_flag == 7){
            I2C2CONbits.PEN = 1;
            i2c_flag++;
            LED8=1;
        }
    }
    IFS3bits.MI2C2IF = 0;
}

void I2C_communication(I2C_MSG_OBJ obj){
    msg = obj;
    i2c_flag = 0;
    count = 0;
    I2C2CONbits.SEN = 1;
}