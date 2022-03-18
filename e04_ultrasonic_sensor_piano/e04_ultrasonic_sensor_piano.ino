/**
 * Ultrasonic Sensor Piano
 * 4. 초음파 센서 피아노
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
  if (distance < 7) {
    rgbCtrl(true, false, false);
    tone(buzzer, notes[0], 300);
    delay(500);
  } else if (distance < 14) {
    rgbCtrl(false, true, false);
    tone(buzzer, notes[1], 300);
    delay(500);
  } else if (distance < 21) {
    rgbCtrl(false, false, true);
    tone(buzzer, notes[2], 300);
    delay(500);
  } else if (distance < 28) {
    rgbCtrl(true, true, false);
    tone(buzzer, notes[3], 300);
    delay(500);
  } else if (distance < 35) {
    rgbCtrl(true, false, true);
    tone(buzzer, notes[4], 300);
    delay(500);
  } else if (distance < 42) {
    rgbCtrl(false, true, true);
    tone(buzzer, notes[5], 300);
    delay(500);
  } else if (distance < 49) {
    rgbCtrl(true, true, true);
    tone(buzzer, notes[6], 300);
    delay(500);
  } else if (distance < 56) {
    rgbCtrl(true, false, false);
    tone(buzzer, notes[7], 300);
    delay(500);
  } else rgbCtrl(false, false, false);
}
