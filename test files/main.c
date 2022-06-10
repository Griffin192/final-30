#include    "xc.h"              // Microchip XC8 compiler include file
#include    "stdint.h"          // Include integer definitions
#include    "stdbool.h"         // Include Boolean (true/false) definitions
#include    "UBMP410.h"         // Include UBMP4.1 constant and function definitions
#include    "motors.h"           // Include servo function definitions

unsigned char base_pos = 0;
unsigned char servo1_pos;        // Servo 1 position variable
unsigned char servo2_pos;        // Servo 2 position variable
unsigned char servo3_pos;        // Servo 3 position variable
unsigned char servo4c_pos = 100;       // Servo 4 position var
unsigned char timerPeriods = 3; // Interrupt timer periods counter (x5ms)
unsigned char servoswitch = 3; 
bool servoL = 1;
bool servoR = 1;   

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
            servo_pulse(SERVO1, servo1_pos);   // Update servo1 position
            servo_pulse(SERVO2, servo2_pos);   // Update servo2 position
            servo_pulse(SERVO3, servo3_pos);   // Update servo3 position    
        }   servo_pulseC(SERVO4C, servo4c_pos);   // Update servo3 position
	}
}

int main(void){
    
    OSC_config();               // Configure internal oscillator for 48 MHz
    UBMP4_config();
    TRISC = 0b0000000;

    while(1){
        //test
      /*  
        if(SW2 == 1 && base__pos != 255){   //moves the base right 
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
        
        

        
        */

       if(SW2 == 0 && servoswitch != 4){
           servoswitch ++;
           __delay_ms(500);
        }if(servoswitch > 3){
           servoswitch = 0;
            __delay_ms(500);
        }
        
        
        if(servoswitch == 0){           // servo 1
            LED3 = 1;
            if(SW5 == 0 && servo1_pos > 0 ){
                servo1_pos --;
                __delay_ms(2);
            }if(SW4 == 0 && servo1_pos < 255 ){
                servo1_pos ++;
                __delay_ms(2);
            }
        }else{
            LED3 = 0;
        }

        if(servoswitch == 1){     
            LED4 = 1;      //servo 2
            if(SW5 == 0 && servo2_pos > 0 ){
                servo2_pos --;
                __delay_ms(2);
            }if(SW4 == 0 && servo2_pos < 255 ){
                servo2_pos ++;
                __delay_ms(2);
            }
        }else{
            LED4 = 0;
        }

        if(servoswitch == 2){   
            LED5 = 1;        //servo 3
            if(SW5 == 0 && servo3_pos > 0 ){
                servo3_pos --;
                __delay_ms(2);
            }if(SW4 == 0 && servo3_pos < 255 ){
                servo3_pos ++;
                __delay_ms(2);
            }
        }else{
            LED5 = 0;
        }
        // stops at 130
        if(servoswitch == 3){
            LED6 = 1;

            
             if(SW5 == 0 && servo4c_pos > 100){
                servo4c_pos --;
                __delay_ms(50);
            }//else{
                servo4c = 130;
            }
            if(SW4 == 0 && servo4c_pos < 130 ){
                servo4c_pos = 25-
                __delay_ms(50);
            }else{
                servo4c = 130;
            }

         
            
        }else{
            TRISC = 0b0001000;
        }
       
        

        if(SW1 == 0){
            RESET();
        }
    }
}
    

