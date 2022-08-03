//_____radio module___________
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define RADIO_CE 9 //CE SP
#define RADIO_SCN 10 //SCN SPI
#define CHANNEL 6
const uint64_t pipe = 0xF0F1F2F3F4L ;  //id
RF24 radio(RADIO_CE, RADIO_SCN); //initialization

//_____remote control_____
#define J_R A1 //right joystick`s pin
#define J_L A0 //left joystick`s pin


#define LEN 2
#define SIZE 2 * sizeof(int)
int data [LEN] = {};
#define R 0
#define L 1
int t = 0;

void setup() {
  Serial.begin(9600);

  //radio settings
  radio.begin();
  radio.setChannel(CHANNEL);
  radio.setDataRate(RF24_1MBPS);
  radio.setPALevel(RF24_PA_HIGH);
  radio.openWritingPipe(pipe); //set transmitter mode

  pinMode(J_R, INPUT);
  pinMode(J_L, INPUT);

  data [R] = 0;
  data[L] = 0;
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
  t = analogRead(J_R);
  t = map(t, 0, 1023, -255, 255);
  data[R] = t;

  t = analogRead(J_L);
  t = map(t, 0, 1023, -255, 255);
  data[L] = t; 

  radio.write(&data, sizeof(data));
}
