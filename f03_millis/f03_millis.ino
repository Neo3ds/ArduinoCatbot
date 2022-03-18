/**
 * millis
 * 3. 시간함수 millis() 사용해보기
 */

int led = 10;
unsigned long currentTime;
boolean isLedOn = false;

void setup() {
  pinMode(led, OUTPUT);
}

void loop() {
  if (millis() - currentTime > 500) {
    currentTime = millis();
    isLedOn = !isLedOn;
    digitalWrite(led, isLedOn);
  }
}
