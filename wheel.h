/* 
 * File:   wheel.h
 * Author: takum
 *
 * Created on December 18, 2024, 4:19 PM
 */

#ifndef WHEEL_H
#define	WHEEL_H

#ifdef	__cplusplus
extern "C" {
#endif

void rudder(int roll,int roll_gain,int max_rolling_power,int heading,int strong);

#ifdef	__cplusplus
}
#endif

#endif	/* WHEEL_H */

