#define J_R 12
#define k_r 0

#define J_L 14
#define k_l 0

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(J_R, INPUT);
  pinMode(J_L, INPUT);
}
byte right() {
  byte v = map(analogRead(J_R), 0, 4095, 0, 255);
  return v;
}
void loop() {
  // put your main code here, to run repeatedly:
//  Serial.print(analogRead(J_L) + k_l);
//  Serial.print("\t");
//  Serial.println(analogRead(J_R) - k_r);
  Serial.println(right());
}
