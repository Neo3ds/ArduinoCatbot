/** Buzzer Siren
 * 2. 부저와 LED를 이용하여 경보 알림 기능을 만들어주세요.
 *  예시) 경찰차 사이렌
 */
int buzzer = 3;
int redLed = 9;
int blueLed = 11;

void setup() {
  pinMode(redLed, OUTPUT);
  pinMode(blueLed, OUTPUT);
}

void loop() {
  digitalWrite(blueLed, LOW);
  digitalWrite(redLed, HIGH);
  tone(buzzer, 1004, 300);
  delay(500);

  digitalWrite(redLed, LOW);
  digitalWrite(blueLed, HIGH);
  tone(buzzer, 1524, 300);
  delay(500);
}
