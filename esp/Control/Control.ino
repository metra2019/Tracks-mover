#include <WiFi.h>

#define J_R 34
#define J_L 35

const char * ssid = "metra"; // Пример установленного имени WiFi
const char * password = "14062005"; // Установленный пароль WiFi.

const uint16_t port = 80;
const char * host = "172.20.10.8";

void setup() {
  Serial.begin(115200);
  pinMode(J_R, INPUT);
  pinMode(J_L, INPUT);


  //подключение к сети
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("...");
  }

}

byte right() {
  byte v = map(analogRead(J_R), 0, 4095, 0, 255);
  return v;
}

byte left() {
  byte v = map(analogRead(J_L), 0, 4095, 0, 255);
  return v;
}

void loop() {
  WiFiClient client;
  client.connect(host, port);

  //  if (!client.connect(host, port)) {
  //    Serial.println("connection to host failed");
  //    delay(500);
  //    return;
  //  }

  //Serial.println(analogRead(J_L));
  client.print(right());
  client.print('\0');
  client.print(left());
  client.print('\0');
  client.stop();
}
