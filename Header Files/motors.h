// Servo header pin bit maps for servo_pulse() function

#define SERVO1 0b00000001      // Servo output pin on H1
#define SERVO2 0b00000010      // Servo output pin on H2
#define SERVO3 0b00000100
#define SERVO4C 0b00001000      // Servo output pin on H3 continuos

#define BASEr 0b01000000 //motor output right pin on H7
#define BASEl 0b10000000 //motor output left pin on H8

/**
 * Function: servo_pulse(unsigned char servo, unsigned char position)
 * 
 * Creates a single servo pulse 0f 1-2ms length optimized for 90 degree servos.
 * Uses SERVO1 - SERVO8 header pin names (corresponding to H1 - H8 header pins)
 * defined in the header file as the servo parameter. 8-bit position values
 * ranging from 0-255 correspond to output pulse widths from 1-2ms. Ensure that
 * your main function repeatedly generates servo pulses every 15-20ms.
 * 
 * Example usage: servo_pulse(SERVO1, 127);
 */
void servo_pulse(unsigned char, unsigned char);