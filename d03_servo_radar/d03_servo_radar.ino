/**
 * Servo Radar
 * 3. 서보모터를 이용하여 레이더 탐지처럼 되게 해주세요.
 */

#include <Servo.h>

int PIN_SERVO = 9;
int MIN_ANGLE = 0;
int MAX_ANGLE = 180;
int angle = 0;
int sw = 1;

Servo servo;

void setup() {
  servo.attach(PIN_SERVO);
}

void loop() {
  servo.write(angle);
  delay(50);
  angle += sw;
  if (angle == MAX_ANGLE || angle == MIN_ANGLE)
    sw = sw * -1;
}
