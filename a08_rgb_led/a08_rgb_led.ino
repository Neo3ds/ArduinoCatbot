/** RGB LED
 * 8. RGB LED를 통해 다양한 색상 나타내기
 */
int redLed = 9;
int greenLed = 10;
int blueLed = 11;

void setup() {
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(blueLed, OUTPUT);

  digitalWrite(greenLed, HIGH); // 결과: 초록
  delay(2000);
  digitalWrite(redLed, HIGH); // 결과: 노랑
  delay(2000);
  digitalWrite(blueLed, HIGH); // 결과: 흰색
  delay(2000);
}

void loop() {
}
