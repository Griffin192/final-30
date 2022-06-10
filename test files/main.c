/*
servo one is the red one at the bottom 
servo two is the elbow 
servo three is the wrist
servo four is special and needs it's own timing it's continuous it's mounted to the base and used to point the arm
leds used to indacat what servo is selected 
switch between servos with SW2 
use  SW4 and SW5 to change the direction

*/
#include    "xc.h"              
#include    "stdint.h"          
#include    "stdbool.h"        
#include    "UBMP410.h"         
#include    "motors.h"           //y did i name it motors and not servos


unsigned char servo1_pos;        // Servo 1 position variable
unsigned char servo2_pos;        // Servo 2 position variable
unsigned char servo3_pos;        // Servo 3 position variable
unsigned char servo4c_pos = 130;       // Servo 4 position variable 130 = no move 
unsigned char timerPeriods = 3; // Interrupt timer periods counter (x5ms)
unsigned char servoswitch = 0; 
   

// Servo interrupt function using TMR0 to count 5ms intervals and generate 
// a new servo pulse every 15ms.
void __interrupt() servo(void)
{
	if(TMR0IF == 1 && TMR0IE == 1)	// Validate Timer 0 interrupt
	{
        TMR0IF = 0;				//0
        TMR0 = 21;              //it's 3am and it works no tuch 
        timerPeriods --;        // Count down 5ms timer periods
        if(timerPeriods == 0)
        {
            timerPeriods = 3;   // Reset timer period to 15ms servo pulse period
            servo_pulse(SERVO1, servo1_pos);   // Update servo1 position
            servo_pulse(SERVO2, servo2_pos);   // Update servo2 position
            servo_pulse(SERVO3, servo3_pos);   // Update servo3 position    
            servo_pulseC(SERVO4C, servo4c_pos);   // Update servo4C position
        }   
	}
}

int main(void){
    
    OSC_config();               // Configure internal oscillator for 48 MHz
    UBMP4_config();
    TRISC = 0b0000000;    //aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa y

    while(1){
      

       if(SW2 == 0 && servoswitch != 4){ // pick servo
           servoswitch ++;
           __delay_ms(500);
        }if(servoswitch > 3){
           servoswitch = 0;
            __delay_ms(500);
        }
        
        
        if(servoswitch == 0){       // servo 1
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

        if(servoswitch == 1){       //servo 2
            LED4 = 1;      
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

        if(servoswitch == 2){       //servo 3  
            LED5 = 1;        
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
        
        if(servoswitch == 3){       //servo 4 it stops at 130 cuz it can  
            LED6 = 1;
            if(SW5 == 0 && servo4c_pos 1= 100){
                servo4c_pos = 100;
                __delay_ms(2);
            }else{
                servo4c = 130;
            }if(SW4 == 0 && servo4c_pos != 150 ){
                servo4c_pos = 150;
                __delay_ms(2);
            }else{
                servo4c = 130;
            }

         
            
        }else{
            TRISC = 0b0001000;  // i think i don't need this now but to scared to tuch now i'll try tomorow 5/6/2020
        }
       
    
        if(SW1 == 0){
            RESET(); 
        }
    }
}
    

