#include    "xc.h"              // Microchip XC8 compiler include file
#include    "stdint.h"          // Include integer definitions
#include    "stdbool.h"         // Include Boolean (true/false) definitions
#include    "UBMP410.h"         // Include UBMP4.1 constant and function definitions
#include    "motors.h"           // Include servo function definitions

unsigned char base_pos = 0;



unsigned char servo1_pos = 128; // Servo 1 position variable
unsigned char timerPeriods = 3; // Interrupt timer periods counter (x5ms)

// Servo interrupt function using TMR0 to count 5ms intervals and generate 
// a new servo pulse every 15ms.
void __interrupt() servo(void)
{
	if(TMR0IF == 1 && TMR0IE == 1)	// Validate Timer 0 interrupt
	{
        TMR0IF = 0;				// Clear Timer 0 interrupt flag
        TMR0 = 21;              // Pre-set TMR0 for next 5ms period interval
        timerPeriods --;        // Count down 5ms timer periods
        if(timerPeriods == 0)
        {
            timerPeriods = 3;   // Reset timer period to 15ms servo pulse period
            servo_pulse(SERVO1, servo1_pos);    // Update servo1 position
        }
	}
}

int main(void){
    OSC_config();               // Configure internal oscillator for 48 MHz
    UBMP4_config();
    TRISC = 0b00001110;

    while(1){
        
        if(SW2 == 1 && base__pos != 256){   //moves the base right 
            BASEr = 1;
            base_pos ++;
        }else{
            BASEr = 0;
        }

        if(SW3 == 1 && base_pos != 0){   // moves the base left
            BASEl = 1;
            base_pos --;
        }else{
            BASEl = 0;
        }
        

        }
         if(SW5 == 0 && servo1_pos > 0)
        {
            servo1_pos --;
        }
        
        if(SW4 == 0 && servo1_pos < 255)
        {
            servo1_pos ++;
        }
        

        if(SW1 == 0)
        {
            RESET();
        }
    }

    
}
