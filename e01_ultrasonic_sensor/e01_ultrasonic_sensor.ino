/**
 * Ultrasonic Sensor
 * 1. 초음파 센서를 통하여서 거리값을 가져오고
 *   해당값을 시리얼 모니터에서 확인
 */

int trig = 12;
int echo = 13;

void setup() {
  Serial.begin(9600);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
}

void loop() {
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  float duration = pulseIn(echo, HIGH);
  float distance = duration / 29 / 2;

  Serial.print("거리: ");
  Serial.print(distance);
  Serial.println(" cm");
}
