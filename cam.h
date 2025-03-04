/*
 * File:   cam.h
 * Author: taku_256
 *
 * Created on February 19, 2025, 4:30 PM
 */

#ifndef CAM_H
#define	CAM_H

#ifdef	__cplusplus
extern "C" {
#endif
    
typedef struct{

    struct{
        int8_t direction;
        uint8_t size;
    }goal;

    struct{
        union{
            uint8_t CAMRXDATA;
            struct{
                unsigned char data : 7;
                unsigned char flag : 1;
            };
        };

    }uart;

}struct_cam;

extern struct_cam cam;

void Receive_from_cam(uint8_t);

#ifdef	__cplusplus
}
#endif

#endif	/* CAM_H */

