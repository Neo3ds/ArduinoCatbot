/**
 * Bluetooth Control
 * 2. 블루투스 통신
 *   통신을 통해 LED 제어해보기
 */

#include <SoftwareSerial.h>

int led = 10;

SoftwareSerial BT(A4, A5);

void setup() {
  BT.begin(9600);
  pinMode(led, OUTPUT);
}

void loop() {
  if (BT.available()) {
    char cmd = BT.read();
    if (cmd == '0') digitalWrite(led, LOW);
    else if (cmd == '1') digitalWrite(led, HIGH);
  }
}
