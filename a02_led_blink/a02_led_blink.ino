/** LED Blink
 * 2. LED를 1초 간격으로 켜졌다가 꺼졌다가를 반복하게 해주세요.
 */

void setup() {
  pinMode(9, OUTPUT);
}

void loop() {
  digitalWrite(9, HIGH);
  delay(1000);
  digitalWrite(9, LOW);
  delay(1000);
}
