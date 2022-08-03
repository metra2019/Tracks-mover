//_____radio module___________
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define RADIO_CE 9 //CE SP
#define RADIO_SCN 10 //SCN SPI
#define CHANNEL 6
const uint64_t pipe = 0xF0F1F2F3F4L ;  //id
RF24 radio(RADIO_CE, RADIO_SCN); //initialization

//____motors____
#define LIMIT_SPEED 10
#include <L298NX2.h>

//motor A - Right
#define EN_A 7
#define IN1_A 6
#define IN2_A 5
int spR = 0; //сurrent speed of motor (0-225) - PWM range values

//motor B - Left
#define IN1_B  3
#define IN2_B  2
#define EN_B  4
int spL = 0; //сurrent speed of motor (0-225) - PWM range value

//initialization
L298NX2 motors(EN_A, IN1_A, IN2_A, EN_B, IN1_B, IN2_B);

//_______communication protocol__________
#define LEN 2
#define SIZE 2 * sizeof(int)
#define R 0
#define L 1
int data [LEN];

void setup() {
  Serial.begin(9600);

  //radio settings
  radio.begin();
  radio.setChannel(CHANNEL);
  radio.setDataRate(RF24_1MBPS);
  radio.setPALevel(RF24_PA_HIGH);
  //set reciever mode
  radio.openReadingPipe(1, pipe);
  radio.startListening();

  data[R] = 0;
  data[L] = 0;

  motors.setSpeedA(data[R]);
  motors.setSpeedB(data[L]);
}

void printInfo() {
  for (int i = 0; i < LEN; i++) {
    Serial.print(data[i]);
    Serial.print('\t');
  }
  Serial.print('\n');
  delay(10);
}
void loop() {
  radio.read(&data, SIZE);
}
