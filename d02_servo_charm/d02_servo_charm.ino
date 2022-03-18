/**
 * 2. 참참참 게임
 *   서보 모터와 부저를 이용하여 참참참 게임을 만들어 주세요.
 *   참참참은 왼쪽 / 오른쪽으로 이동할 수 있습니다.
 */

#include <Servo.h>

int buzzer = 3;
int PIN_SERVO = 9;

Servo servo;

void setup() {
  servo.attach(PIN_SERVO);
}

void loop() {
  tone(buzzer, 392, 300);
  delay(500);
  tone(buzzer, 392, 300);
  delay(500);
  tone(buzzer, 612, 300);
  delay(500);

  int value = analogRead(A0) % 2;
  if (value == 1) servo.write(30);
  else servo.write(150);
  delay(2000);
  servo.write(90);
}
