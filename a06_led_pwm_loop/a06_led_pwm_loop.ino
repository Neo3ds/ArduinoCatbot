/** LED PWM Loop
 * 6. LED 세기가 1씩 밝아졌다가 최대치 세기가 되면 점점 1씩 어두워지게
 *  0이 되어 꺼지면 다시 점점 밝아지게 이 로직을 반복하여 계속 점점 밝아졌다가
 *  어두워졌다가를 반복하는 프로그램을 작성해주세요.
 *  (시간 간격: 0.01초)
 */
int redLed = 9;

void setup() {
}

void loop() {
  for (int power = 0; power < 255; power++) {
    analogWrite(redLed, power);
    delay(10);
  }
  for (int power = 255; power >= 0; power--) {
    analogWrite(redLed, power);
    delay(10);
  }
}
