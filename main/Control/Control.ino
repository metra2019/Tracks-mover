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
#define J_R A2 //right joystick`s pin
#define J_L A7 //left joystick`s pin

//_____charge indicator___
#define DATA 6 //14 - SD
#define CLOCK 8 //11 - SH_CP
#define LATCH 7 //12 - ST_CP

byte nums[8] = {
  0b10000000,
  0b11000000,
  0b11100000,
  0b11110000,
  0b11111000,
  0b11111100,
  0b11111110,
  0b11111111
};

void setByte(byte value) {
  digitalWrite(LATCH, LOW); // начинаем передачу данных
  // устанавливаем нужный байт
  shiftOut(DATA, CLOCK, LSBFIRST, value);
  digitalWrite(LATCH, HIGH); // прекращаем передачу данных
}

//______leds on face____
#define ON_LED 3
#define OFF_LED 4

//______recieve_____
const int s = 2;
byte data [s] = {};
int spL, spR;

bool get_data = true;

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


  pinMode(LATCH, OUTPUT);
  pinMode(CLOCK, OUTPUT);
  pinMode(DATA, OUTPUT);
  digitalWrite(LATCH, LOW);

  pinMode(ON_LED, OUTPUT);
  pinMode(OFF_LED, OUTPUT);

  digitalWrite(ON_LED, get_data);
}

void loop() {
  spR = analogRead(J_R);
  spR = map(spR, 0, 1023, 0, 255);
  data[0] = byte(spR);

  spL = analogRead(J_L);
  spL = map(spL, 0, 1023, 0, 255);
  data[1] = byte(spL);

  radio.write(&data, sizeof(data));
}
