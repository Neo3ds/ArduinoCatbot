/** RGB LED Origin
 * 9. RGB LED를 통해 다양한 색상 나타내기
 *  빨 -> 초 -> 파 순서로 켜기(시간 간격: 2초)
 */
int redLed = 9;
int greenLed = 10;
int blueLed = 11;

void setup() {
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(blueLed, OUTPUT);

  digitalWrite(redLed, HIGH);
  delay(2000);
  digitalWrite(redLed, LOW);
  digitalWrite(greenLed, HIGH);
  delay(2000);
  digitalWrite(greenLed, LOW);
  digitalWrite(blueLed, HIGH);
  delay(2000);
}

void loop() {
}
