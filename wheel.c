#include "wheel.h"
#include "xc.h"
#include "user.h"
#include "common.h"
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

/*
     flont
       0
   -30   30
 -60       60
-90         90
-120      120
 -150    150
    +-180
*/

    void rudder(int roll,int roll_gain,int max_rolling_power,int16_t heading,int strong){
    int A =  sin( ( heading -  50) / rd)  * strong + roll*roll_gain;
    int B =  sin( ( heading - 130) / rd)  * strong + roll*roll_gain;
    int C = -sin( ( heading -  50) / rd)  * strong + roll*roll_gain;
    int D = -sin( ( heading - 130) / rd)  * strong + roll*roll_gain;
    
    
    OC1R = ( A*(A >= 0));
    OC2R = (-A*(A <= 0));
    OC3R = ( B*(B >= 0));
    OC4R = (-B*(B <= 0));
    OC5R = ( C*(C >= 0));
    OC6R = (-C*(C <= 0));
    OC7R = ( D*(D >= 0));
    OC8R = (-D*(D <= 0));
}