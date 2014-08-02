#include <16F628A.h>

#FUSES NOWDT                    //No Watch Dog Timer
#FUSES PUT                      //Power Up Timer
#FUSES INTRC                 //Internal RC Osc, no CLKOUT
#FUSES NOMCLR                   //Master Clear pin used for I/O
#FUSES NOLVP                    //No low voltage prgming, B3(PIC16) or B5(PIC18) used for I/O

#use delay(int=4000000)
#use STANDARD_IO( A )

#use FIXED_IO( A_outputs=PIN_A3,PIN_A2,PIN_A1)
#use FIXED_IO( B_outputs=PIN_B3,PIN_B2,PIN_B1,PIN_B0 )

#define Select   PIN_B4

#define LED0   PIN_A2
#define LED1   PIN_A3
#define LED2   PIN_B0
#define LED3   PIN_B1
#define LED4   PIN_B2

#define Relay   PIN_A1
#define Buzzer  PIN_B3

//#use rs232(baud=9600, xmit=PIN_B2,rcv=PIN_B1, STREAM=Debug,errors)


