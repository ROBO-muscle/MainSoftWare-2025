/* 
 * File:   user.h
 * Author: takum
 *
 * Created on December 2, 2024, 5:34 PM
 */

#ifndef USER_H
#define	USER_H

#ifdef	__cplusplus
extern "C" {
#endif
#include <math.h>
    
#define LED1 LATEbits.LATE3
//#define LED2 LATEbits.LATE2
#define LED3 LATGbits.LATG13
#define LED4 LATGbits.LATG12
#define LED5 LATGbits.LATG14
#define LED6 LATEbits.LATE1
//#define LED7 LATEbits.LATE0
#define LED8 LATDbits.LATD7
#define JYRO (((i2c_data[1]*256+i2c_data[0])/16)-(jyrof-180) - 180)
#define rudder_funk rudder(JYRO,15*LINE_flag,0,(!LINE_flag)*LINE+LINE_flag*IR_Data*1.6,(!LINE_flag)*0x1000+(LINE_flag)*0xa00)
#define hold_ball (ADC1BUF0<500)
#define LINE_num 15
#define LINE (atan2(LINEx_vec,LINEy_vec)/3.141592*180)
#define KICK LATAbits.LATA15
    
    
#ifdef	__cplusplus
}
#endif

#endif	/* USER_H */

