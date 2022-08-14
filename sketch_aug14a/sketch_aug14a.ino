//motor A - Right
#define EN_A 6
#define IN1_A 8
#define IN2_A 7
int spR = 0; //сurrent speed of motor (0-225) - PWM range values

//motor B - Left
#define IN1_B  4
#define IN2_B  3
#define EN_B  5
int spL = 0; //сurrent speed of motor (0-225) - PWM range value

//_____remote control_____
#define J_R A1 //right joystick`s pin
#define J_L A0 //left joystick`s pin

//____motors____
#define LIMIT_SPEED 10

#include <GyverMotor.h>
GMotor motR (DRIVER3WIRE, IN1_A, IN2_A, EN_A);
GMotor motL (DRIVER3WIRE, IN1_B, IN2_B, EN_B);

//_______communication protocol__________

void setup() {
  Serial.begin(9600);
  
  pinMode(J_R, INPUT);
  pinMode(J_L, INPUT);

  motR.setMode(AUTO);
  motR.setMinDuty(20);

  motL.setMode(AUTO);
  motL.setMinDuty(20);
}
void loop() {
  spR = analogRead(J_R);
  spR = map(spR, 0, 1023, -255, 255);

  spL = analogRead(J_L);
  spL = map(spL, 0, 1023, -255, 255);


  motR.smoothTick(spR);
  motL.smoothTick(spL);
}
