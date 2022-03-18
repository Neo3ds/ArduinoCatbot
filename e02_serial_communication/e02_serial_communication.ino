/** Serial Communication
 * 2. 시리얼 통신과 시리얼 모니터 사용해보기
 */

int led = 10;

void setup() {
  Serial.begin(9600);
  pinMode(led, OUTPUT);
}

void loop() {
  if (Serial.available()) {
    char cmd = Serial.read();
    if (cmd == '0') digitalWrite(led, LOW);
    else if (cmd == '1') digitalWrite(led, HIGH);
  }
}
