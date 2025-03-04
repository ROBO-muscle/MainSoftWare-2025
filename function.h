/* 
 * File:   function.h
 * Author: takum
 *
 * Created on December 7, 2024, 2:16 PM
 */

#ifndef FUNCTION_H
#define	FUNCTION_H

#ifdef	__cplusplus
extern "C" {
#endif

void setup();

void U1Write(uint8_t);

void I2C_communication();

uint16_t IR_read();

void TMR2_setup();
void TMR3_setup();

void TMR3_start();
void TMR3_stop();

#ifdef	__cplusplus
}
#endif

#endif	/* FUNCTION_H */

