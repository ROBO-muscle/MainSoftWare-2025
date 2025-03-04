/* 
 * File:   setup.c
 * Author: takum
 *
 * Created on December 7, 2024, 2:30 PM
 */

#include <p33EP512MU810.h>
#include "xc.h"
#include "function.h"
#define FCY 64000000

void setup(){
    OSC_set();
    pin_set();
    UART1_setup(115200);
    UART2_setup(115200);
//    UART3_setup(115200);
    OC1_setup();
    OC2_setup();
    OC3_setup();
    OC4_setup();
    OC5_setup();
    OC6_setup();
    OC7_setup();
    OC8_setup();
    OC9_setup();
    OC10_setup();
    i2c_setup();
    ADC1_setup();
    TMR1_setup();
//    TMR2_setup();
    TMR3_setup();
}

void OSC_set(){
    OSCCON   = 0x0100;
    OSCTUN   = 0x0017;
    PLLFBD   = 0x003E;
    CLKDIV   = 0x0000;
    ACLKCON3 = 0xA2E1;
    ACLKDIV3 = 0x0007;
}

void pin_set(){
    ANSELA = 0x0000;
    ANSELB = 0x0000;
    ANSELC = 0x0000;
    ANSELD = 0x0000;
    ANSELE = 0x0000;
    ANSELG = 0x0000;
    
    AD1CSSH = 0x0000;
    AD1CSSL = 0x0000;
    
    TRISA = 0xffff;
    TRISB = 0xffff;
    TRISC = 0xffff;
    TRISD = 0xffff;
    TRISE = 0xffff;
    TRISF = 0xffff;
    TRISG = 0xffff;
    
//  ESP32S3 | UART1
    TRISFbits.TRISF2  = 0;
    RPOR8bits.RP98R = 0b000001;
    TRISFbits.TRISF8  = 1;
    RPINR18bits.U1RXR = 104;
    
//  OPENMV | UART2
    TRISFbits.TRISF13  = 0;
    RPOR12bits.RP109R  = 0b000011;
    TRISFbits.TRISF12  = 1;
    RPINR19bits.U2RXR = 108;
    
//  LED
    TRISEbits.TRISE3  = 0;
//    TRISEbits.TRISE2  = 0;
    TRISGbits.TRISG13 = 0;
    TRISGbits.TRISG12 = 0;
    TRISGbits.TRISG14 = 0;
    TRISEbits.TRISE1  = 0;
//    TRISEbits.TRISE0  = 0;
    TRISDbits.TRISD7  = 0;

// MOTER
    TRISEbits.TRISE2  = 0;
    TRISGbits.TRISG0  = 0;
    TRISGbits.TRISG1  = 0;
    TRISFbits.TRISF1  = 0;
    TRISFbits.TRISF0  = 0;
    TRISDbits.TRISD3  = 0;
    TRISDbits.TRISD2  = 0;
    TRISDbits.TRISD1  = 0;
    
    RPOR5bits.RP82R   = 0b010000;
    RPOR12bits.RP112R = 0b010001;
    RPOR13bits.RP113R = 0b010010;
    RPOR7bits.RP97R   = 0b010011;
    RPOR7bits.RP96R   = 0b010100;
    RPOR1bits.RP67R   = 0b010101;
    RPOR1bits.RP66R   = 0b010110;
    RPOR0bits.RP65R   = 0b010111;
    
// DRIBBLER
    TRISDbits.TRISD0  = 0;
    TRISDbits.TRISD15 = 0;
    
    RPOR0bits.RP64R   = 0b100101;
    RPOR4bits.RP79R   = 0b100110;

// KICKER
    TRISAbits.TRISA15 = 0;

// KICK SENSOR
    TRISAbits.TRISA14 = 1;
    TRISEbits.TRISE0  = 1;
    ANSELEbits.ANSE0  = 1;
    AD1CSSHbits.CSS24 = 1;

// IR
    TRISAbits.TRISA7  = 1;
    TRISDbits.TRISD13 = 1;
    TRISDbits.TRISD12 = 1;
    TRISDbits.TRISD11 = 1;
    TRISDbits.TRISD10 = 1;
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

// LINE
    TRISBbits.TRISB2  = 1; 
    TRISBbits.TRISB3  = 1;
    TRISBbits.TRISB4  = 1;
    TRISBbits.TRISB5  = 1;
    TRISCbits.TRISC3  = 1;
    TRISCbits.TRISC2  = 1;
    TRISCbits.TRISC1  = 1;
    TRISEbits.TRISE7  = 1;
    
    CNENBbits.CNIEB2  = 1;
    CNENBbits.CNIEB3  = 1;
    CNENBbits.CNIEB4  = 1;
    CNENBbits.CNIEB5  = 1;
    CNENCbits.CNIEC3  = 1;
    CNENCbits.CNIEC2  = 1;
    CNENCbits.CNIEC1  = 1;
    CNENEbits.CNIEE7  = 1;
    
    
    IEC1bits.CNIE = 1;
    IPC4bits.CNIP = 2;
    IFS1bits.CNIF = 0;
}

void TMR1_setup (void){
    PR1   =   0x00;
    TMR1  =   0x00;
    T1CON = 0x8000;
}

void TMR2_setup (void){
    PR2   = 0x1000; // Period : 4096
    TMR2  =   0x00; // Reset
    T2CON = 0x0030; // Prescale 1:256
    
    IEC0bits.T2IE = 1;
    IPC1bits.T2IP = 3;
    IFS0bits.T2IF = 0;
}

void TMR3_setup (void){
    PR3   = 0x0219; // Period : 537
    TMR3  =   0x00; // Reset
    T3CON = 0x0000; // Prescale 1:1
    
    IEC0bits.T3IE = 1;
    IPC2bits.T3IP = 3;
    IFS0bits.T3IF = 0;
}

void UART1_setup(long baudrate){    
    U1MODE = 0x0000;
    U1STA  = 0x0000;
    
    U1MODEbits.BRGH = 1;
    U1BRG = FCY / (4 * baudrate) - 1;
    U1STAbits.URXISEL = 0b00;
    U1STAbits.UTXINV = 0;
    
    IEC0bits.U1RXIE = 1;
    IPC2bits.U1RXIP = 0b001;
    IFS0bits.U1RXIF = 0;
    U1STAbits.URXISEL = 00;
    
    U1MODEbits.UARTEN = 1;
    
    U1STAbits.UTXEN = 1;
}

void UART2_setup(long baudrate){    
    U2MODE = 0x0000;
    U2STA  = 0x0000;
    
    U2MODEbits.BRGH = 1;
    U2BRG = FCY / (4 * baudrate) - 1;
    U2STAbits.URXISEL = 0b00;
    U2STAbits.UTXINV = 0;
    
    IEC1bits.U2RXIE = 1;
    IPC7bits.U2RXIP = 0b001;
    IFS1bits.U2RXIF = 0;
    U2STAbits.URXISEL = 00;
    
    U2MODEbits.UARTEN = 1;
    
    U2STAbits.UTXEN = 1;
}

void UART3_setup(long baudrate){    
    U3MODE = 0x0000;
    U3STA  = 0x0000;
    
    U3MODEbits.BRGH = 1;
    U3BRG = FCY / (4 * baudrate) - 1;
    U3STAbits.URXISEL = 0b00;
    U3STAbits.UTXINV = 0;
    
//    IEC5bits.U3RXIE = 1;
//    IPC20bits.U3RXIP = 0b001;
//    IFS5bits.U3RXIF = 0;
//    U3STAbits.URXISEL = 00;
    
    U3MODEbits.UARTEN = 1;
    
    U3STAbits.UTXEN = 1;
}

void OC1_setup(){
    OC1R  = 0x0000;
    OC1RS = 0x1000;
    OC1CON1 = 0x0000;
    OC1CON2 = 0x0000;
    OC1CON1bits.OCM     =   0b110; // Edge-Aligned PWM mode
    OC1CON1bits.OCTSEL  =   0b111; // Peripheral clock(FOSC/2)
    OC1CON2bits.SYNCSEL = 0b01011; // Timer1 synchronizes or triggers OC1
    OC1CON2bits.OCTRIG  =     0b1; // OC1 Start
}

void OC2_setup(){
    OC2R  = 0x0000;
    OC2RS = 0x1000;
    OC2CON1 = 0x0000;
    OC2CON2 = 0x0000;
    OC2CON1bits.OCM     =   0b110; // Edge-Aligned PWM mode
    OC2CON1bits.OCTSEL  =   0b111; // Peripheral clock(FOSC/2) 
    OC2CON2bits.SYNCSEL = 0b01011; // Timer1 synchronizes or triggers OC2
    OC2CON2bits.OCTRIG  =     0b1; // OC2 Start
}

void OC3_setup(){
    OC3R  = 0x0000;
    OC3RS = 0x1000;
    OC3CON1 = 0x0000;
    OC3CON2 = 0x0000;
    OC3CON1bits.OCM     =   0b110; // Edge-Aligned PWM mode
    OC3CON1bits.OCTSEL  =   0b111; // Peripheral clock(FOSC/2)
    OC3CON2bits.SYNCSEL = 0b01011; // Timer1 synchronizes or triggers OC3
    OC3CON2bits.OCTRIG  =     0b1; // OC3 Start
}

void OC4_setup(){
    OC4R  = 0x0000;
    OC4RS = 0x1000;
    OC4CON1 = 0x0000;
    OC4CON2 = 0x0000;
    OC4CON1bits.OCM     =   0b110; // Edge-Aligned PWM mode
    OC4CON1bits.OCTSEL  =   0b111; // Peripheral clock(FOSC/2)
    OC4CON2bits.SYNCSEL = 0b01011; // Timer1 synchronizes or triggers OC4
    OC4CON2bits.OCTRIG  =     0b1; // OC4 Start
}

void OC5_setup(){
    OC5R  = 0x0000;
    OC5RS = 0x1000;
    OC5CON1 = 0x0000;
    OC5CON2 = 0x0000;
    OC5CON1bits.OCM     =   0b110; // Edge-Aligned PWM mode
    OC5CON1bits.OCTSEL  =   0b111; // Peripheral clock(FOSC/2)
    OC5CON2bits.SYNCSEL = 0b01011; // Timer1 synchronizes or triggers OC5
    OC5CON2bits.OCTRIG  =     0b1; // OC5 Start
}

void OC6_setup(){
    OC6R  = 0x0000;
    OC6RS = 0x1000;
    OC6CON1 = 0x0000;
    OC6CON2 = 0x0000;
    OC6CON1bits.OCM     =   0b110; // Edge-Aligned PWM mode
    OC6CON1bits.OCTSEL  =   0b111; // Peripheral clock(FOSC/2)
    OC6CON2bits.SYNCSEL = 0b01011; // Timer1 synchronizes or triggers OC6
    OC6CON2bits.OCTRIG  =     0b1; // OC6 Start
}

void OC7_setup(){
    OC7R  = 0x0000;
    OC7RS = 0x1000;
    OC7CON1 = 0x0000;
    OC7CON2 = 0x0000;
    OC7CON1bits.OCM     =   0b110; // Edge-Aligned PWM mode
    OC7CON1bits.OCTSEL  =   0b111; // Peripheral clock(FOSC/2)
    OC7CON2bits.SYNCSEL = 0b01011; // Timer1 synchronizes or triggers OC7
    OC7CON2bits.OCTRIG  =     0b1; // OC7 Start
}

void OC8_setup(){
    OC8R  = 0x0000;
    OC8RS = 0x1000;
    OC8CON1 = 0x0000;
    OC8CON2 = 0x0000;
    OC8CON1bits.OCM     =   0b110; // Edge-Aligned PWM mode
    OC8CON1bits.OCTSEL  =   0b111; // Peripheral clock(FOSC/2)
    OC8CON2bits.SYNCSEL = 0b01011; // Timer1 synchronizes or triggers OC8
    OC8CON2bits.OCTRIG  =     0b1; // OC8 Start
}

void OC9_setup(){
    OC9R  = 0x0000;
    OC9RS = 0x1000;
    OC9CON1 = 0x0000;
    OC9CON2 = 0x0000;
    OC9CON1bits.OCM     =   0b110; // Edge-Aligned PWM mode
    OC9CON1bits.OCTSEL  =   0b111; // Peripheral clock(FOSC/2)
    OC9CON2bits.SYNCSEL = 0b01011; // Timer1 synchronizes or triggers OC9
    OC9CON2bits.OCTRIG  =     0b1; // OC9 Start
}

void OC10_setup(){
    OC10R  = 0x0000;
    OC10RS = 0x1000;
    OC10CON1 = 0x0000;
    OC10CON2 = 0x0000;
    OC10CON1bits.OCM     =   0b110; // Edge-Aligned PWM mode
    OC10CON1bits.OCTSEL  =   0b111; // Peripheral clock(FOSC/2)
    OC10CON2bits.SYNCSEL = 0b01011; // Timer1 synchronizes or triggers OC10
    OC10CON2bits.OCTRIG  =     0b1; // OC10 Start
}

void i2c_setup(){
    I2C2CON = 0x0000;
    
//    long FSCL = 400000; // CLK : 400kHz
//    I2C2BRG = FCY*(1/(FSCL) - 120/1000000000); // set CLK
    I2C2BRG = 151;
    
    IPC12bits.MI2C2IP = 0b111;
    IFS3bits.MI2C2IF  = 0; // clear interrupt i2c2 flag
    IEC3bits.MI2C2IE  = 1; // enable i2c2 interrupt  

    I2C2CONbits.I2CEN = 1; // i2c2 enable
}

void ADC1_setup(){
    AD1CON1   = 0x0000;
    AD1CON2   = 0x0000;
    AD1CON3   = 0x0000;
    AD1CON4   = 0x0000;
    AD1CHS123 = 0x0000;
    AD1CHS0   = 0x0000;
    
    AD1CON1bits.FORM   =       0b00; // Unsigned Integer Format
    AD1CON1bits.SSRC   =      0b111; // Internal counter ends sampling and starts conversion
//    SD1CON1bits.SIMSAM =        0b1; // samples simultaneously
    AD1CON1bits.ASAM   =        0b1; // Automatic Sample
    AD1CON2bits.VCFG   =      0b000; // AVDD/AVSS
    AD1CON2bits.CSCNA  =        0b1; // Scans inputs for CH0+ during Sample A bit
    AD1CON2bits.CHPS   =       0b00; // CH0 only
    AD1CON3bits.SAMC   =    0b11111; // TAD=31 (Auto-Sample Time bits)
    AD1CON3bits.ADCS   = 0b00000100; // ADC Conversion Clock Select bits
    AD1CON1bits.ADON   =        0b1;
    AD1CON1bits.SAMP   =        0b1;
    IEC0bits.AD1IE     =        0b1;
}