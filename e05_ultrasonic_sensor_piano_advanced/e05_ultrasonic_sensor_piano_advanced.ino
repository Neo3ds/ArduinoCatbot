/**
 * Ultrasonic Sensor Piano: Advanced
 * 5. 초음파 센서 피아노 Advanced
 *   7cm 간격으로 LED 색상이 변경되고, 소리도 도~높은도
 */

int buzzer = 3;
int redLed = 9;
int greenLed = 10;
int blueLed = 11;
int trig = 12;
int echo = 13;

int notes[8] = {
  262, 294, 330, 349, 392, 440, 494, 523
};

int stateList[8][3] = {
  {1, 0, 0}, {0, 1, 0}, {0, 0, 1}, {1, 1, 0}, {1, 0, 1},
  {0, 1, 1}, {1, 1, 1}, {1, 0, 0}
};

float getUltrasonic() {
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  float duration = pulseIn(echo, HIGH);
  return duration / 29 / 2;
}

void rgbCtrl(boolean ir, boolean ig, boolean ib) {
  digitalWrite(redLed, ir);
  digitalWrite(greenLed, ig);
  digitalWrite(blueLed, ib);
}

void setup() {
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(blueLed, OUTPUT);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
}

void loop() {
  float distance = getUltrasonic();
  int index = distance / 7;
  if (index < 8) {
    tone(buzzer, notes[index], 300);
    rgbCtrl(stateList[0], stateList[1], stateList[2]);
    delay(500);
  } else {
    rgbCtrl(false, false, false);
  }
}
