//_____radio module___________
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define RADIO_CE 9 //CE SP
#define RADIO_SCN 10 //SCN SPI
#define CHANNEL 6
const uint64_t pipe = 0xF0F1F2F3F4L ;  //id
RF24 radio(RADIO_CE, RADIO_SCN); //initialization

//______recieve_____
const int s = 2;
byte data [s] = {};
int spR, spL;

//______motors______
int enr = 4;
int in1 = 3;
int in2 = 2;

int enl = 7;
int in3 = 5;
int in4 = 6;

#define LIMIT 20
#include <GyverMotor.h>
GMotor motL (DRIVER3WIRE, in3, in4, enl);
GMotor motR (DRIVER3WIRE, in1, in2, enr);


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

  //set motor's settings
  motL.setMode(AUTO);
  motL.setMinDuty(LIMIT);

  motR.setMode(AUTO);
  motR.setMinDuty(LIMIT);
}

void loop() {
  if (radio.available()) {
    radio.read(&data, sizeof(data));
  }
  spR = (int)data[0];
  spR = map(spR, 0, 255, -255, 255);
  if (abs(spR) < LIMIT) spR = 0;

  spL = (int)data[1];
  spL = map(spL, 0, 255, -255, 255);
  if (abs(spL) < LIMIT) spL = 0;

  motL.smoothTick(spL);
  motR.smoothTick(spR);
}
