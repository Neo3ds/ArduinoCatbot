/** LED PWM Decrease
 * 5. LED 세기가 최대치에서 1씩 줄어들어 꺼지게 해주세요.
 * (시간 간격 0.02초)
 */
int redLed = 9;

void setup() {
  for (int power = 255; power >= 0; power--) {
    analogWrite(redLed, power);
    delay(20);
  }
}

void loop() {
}
