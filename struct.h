/* 
 * File:   struct.h
 * Author: takum
 *
 * Created on October 16, 2024, 3:20 PM
 */

#ifndef STRUCT_H
#define	STRUCT_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <xc.h>
#include <stdbool.h>

    
typedef enum{
    read  = 1,
    write = 0
} I2C_MODE;

typedef enum{
    LOW  = 0,
    HIGH = 1
} HIGH_and_LOW;
    
typedef struct{
//    union{
//        struct{
            unsigned char mode : 1;
            unsigned char   add : 7;
//        };
        uint8_t ADDbyte;
//    };
    uint8_t   reg;
    uint8_t count; // index of data
    uint8_t *Data;
}I2C_MSG_OBJ;

#ifdef	__cplusplus
}
#endif

#endif	/* STRUCT_H */

