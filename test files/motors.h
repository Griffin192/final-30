// Servo header pin bit maps for servo_pulse() function

#define SERVO1 0b00000001      // Servo output pin on H1
#define SERVO2 0b00000010      // Servo output pin on H2
#define SERVO3 0b00000100
#define SERVO4C 0b00001000      // Servo output pin on H3 continuos

#define BASEr 0b01000000 //motor output right pin on H7
#define BASEl 0b10000000 //motor output left pin on H8


void servo_pulse(unsigned char, unsigned char);
void servo_pulseC(unsigned char, unsigned char);