/** Buzzer Siren with Ternary operator
 * 4. 부저와 LED를 이용하여 경보 알림 기능을 만들어주세요.
 *  *삼항 연산자 사용
 */
int buzzer = 3;
int redLed = 9;
int blueLed = 11;
boolean isState = false;

void setup() {
  pinMode(redLed, OUTPUT);
  pinMode(blueLed, OUTPUT);
}

void loop() {
  int note = isState ? 1524 : 1004; // 삼항연산자
  digitalWrite(redLed, !isState);
  digitalWrite(blueLed, isState);
  tone(buzzer, note, 300);
  delay(500);
  isState = !isState;
}
