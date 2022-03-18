/** RGB LED Function
 * 10. RGB LED를 제어하는 함수를 만들어 원하는 색상을 켜보세요.
 */
int redLed = 9;
int greenLed = 10;
int blueLed = 11;

void rgbCtrl(boolean redState, boolean greenState, boolean blueState) {
  digitalWrite(redLed, redState);
  digitalWrite(greenLed, greenState);
  digitalWrite(blueLed, blueState);
}

void setup() {
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(blueLed, OUTPUT);

  rgbCtrl(true, false, false); // 빨강
  delay(2000);
  rgbCtrl(true, true, false); // 노랑
  delay(2000);
  rgbCtrl(false, true, true); // 청록
  delay(2000);
  rgbCtrl(true, true, true); // 흰색
  delay(2000);
}

void loop() {
}
