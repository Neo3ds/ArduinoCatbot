/** Servo
 * 1. 서보 모터 제어해보기
 *  서보 모터 제어해보기
 */

 #include <Servo.h>

int PIN_SERVO = 9;

Servo servo;

void setup() {
  servo.attach(PIN_SERVO);

  servo.write(90); // 90도
  delay(500); // 0.5초 대기
  servo.write(180); // 180도
  delay(500); // 0.5초 대기
  servo.write(0); // 0도
  delay(500); // 0.5초 대기

  servo.detach();
}

void loop() {
}
