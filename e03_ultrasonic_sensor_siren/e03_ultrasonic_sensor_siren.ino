/** Ultrasonic Siren
 * 3. 초음파 센서 침입 경보 시스템
 *   초음파 센서와 LED, 부저를 이용하여 침입 경보 시스템을 만들어주세요.
 */

int buzzer = 3;
int led = 10;
int trig = 12;
int echo = 13;

float getUltrasonic() {
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  float duration = pulseIn(echo, HIGH);
  return duration / 29 / 2;
}

void setup() {
  pinMode(led, OUTPUT);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
}

void loop() {
  float distance = getUltrasonic();
  if (distance < 20) {
    digitalWrite(led, HIGH);
    for (int cnt=0; cnt<10; cnt++) {
      tone(buzzer, 912, 300);
      delay(500);
    }
    digitalWrite(led, LOW);
  }
}
