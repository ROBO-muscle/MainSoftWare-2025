/* 
 * File:   common.h
 * Author: taku_256
 *
 * Created on September 11, 2024, 9:30 AM
 */

#ifndef COMMON_H
#define	COMMON_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#define ull unsigned long long int
    
#define pi 3.14159265358979323846264338327950288
#define rd (180/pi) //radian to degree
#define deg(angle) (angle*pi/180)
#define rad(angle) (angle*180/pi)
    
#define MSB16(B) B >> 8
#define LSB16(B) B & 0x00ff    
    
#ifdef	__cplusplus
}
#endif

#endif	/* COMMON_H */

