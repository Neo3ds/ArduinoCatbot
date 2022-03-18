#include <SoftwareSerial.h>

SoftwareSerial BT(A4, A5);

void setup() {
  Serial.begin(9600);
  BT.begin(9600);
}

void loop() {
  if (Serial.available()) {
    BT.write(Serial.read());
  }

  if (BT.available()) {
    Serial.write(BT.read());
  }
}
