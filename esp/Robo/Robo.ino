#include <ESP8266WiFi.h>

const char* ssid = "metra";
const char* password = "14062005";
const uint16_t port = 80;

WiFiServer wifiServer(port);
String req;

//motor A - Right
#define EN_A 4
#define IN1_A 3
#define IN2_A 2
int rval;

//motor B - Left
#define EN_B  7
#define IN1_B  6
#define IN2_B  5
int lval;

//____motors____
#define LIMIT_SPEED 10

#include <GyverMotor.h>
GMotor motR (DRIVER3WIRE, IN1_A, IN2_A, EN_A);
GMotor motL (DRIVER3WIRE, IN1_B, IN2_B, EN_B);

void setup() {

  Serial.begin(115200);

  WiFi.begin(ssid, password);

  //  while (WiFi.status() != WL_CONNECTED) {
  //    delay(1000);
  //    Serial.println("Connecting..");
  //  }
  //
  //  Serial.print("Connected to WiFi. IP:");
  //  Serial.println(WiFi.localIP());

  pinMode(EN_A, OUTPUT);
  pinMode(IN1_A, OUTPUT);
  pinMode(IN1_A, OUTPUT);
  
  motR.setMode(AUTO);
  motR.setMinDuty(20);

  motL.setMode(AUTO);
  motL.setMinDuty(20);

  wifiServer.begin();
}

void loop() {
  //  WiFiClient client = wifiServer.available();

  //  if (client) {
  //    while (client.connected()) {
  //      while (client.available() > 0) {
  //        char c = client.read();
  //        Serial.write(c);
  //      }
  //    }
  //    client.stop();
  //  }

  lval = 120;
  rval = 200;

  //  if (client.available() > 0) {
  //    req = client.readStringUntil('\0');
  //    lval = req.toInt();
  //    req = client.readStringUntil('\0');
  //    rval = req.toInt();
  //  }
  //  Serial.print(lval);
  //  Serial.print("\t");
  //  Serial.println(rval);
  motR.smoothTick(rval);
  //motL.smoothTick(lval);
}
