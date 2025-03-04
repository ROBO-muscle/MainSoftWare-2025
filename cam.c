/*
 * File:   cam.c
 * Author: taku_256
 *
 * Created on February 19, 2025, 4:30 PM
 */

#include <stdbool.h>
#include <stdint.h>
#include "cam.h"

struct_cam cam;

void Receive_from_cam(uint8_t data){
    cam.uart.CAMRXDATA = data;
    
    if  (cam.uart.flag) cam.goal.direction = cam.uart.data - 64;
    else                cam.goal.size      = cam.uart.data;
    
}
