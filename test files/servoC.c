#include    "xc.h"              // Microchip XC8 compiler include file
#include    "stdint.h"          // Include integer definitions
#include    "stdbool.h"         // Include Boolean (true/false) definitions

#include    "UBMP410.h"         // Include UBMP4 constants and functions
#include    "motors.h"           // Include UBMP4 servo definitions

// Create a servo pulse on the specified output (SERVO1 - 8), for a duration
// corresponding to the position value. Ensure PORTC servo pins are previously
// set as digital outputs.
void servo_pulseC(unsigned char servo, unsigned char position)
{
    PORTC = PORTC | servo;      // Set servo pin high and make fixed delay
    __delay_us(518);            // (change this value for 180 degree servos)
    for(position; position != 0; position--)   // Extend delay by position value
    {
        _delay(83);             // Clock cycle delay to make 1ms pulse (pos = 255)
    }                           // (change clock delay to modify pulse)
    PORTC = PORTC & (!servo);   // End pulse by resetting servo pin
}