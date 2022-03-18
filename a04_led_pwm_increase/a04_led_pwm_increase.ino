/** LED PWM Increase
 * 4. LED 세기가 0에서 1씩 커져서 밝아지게 해주세요.
 * (시간 간격: 0.02초)
 */
int redLed = 9;

void setup() {
  for (int power = 0; power < 255; power++) {
    analogWrite(redLed, power);
    delay(20);
  }
}

void loop() {
}
