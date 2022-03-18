/** Buzzer with array
 * 3. 배열을 이용해서 원하는 노래 만들기
 */
int buzzer = 3;
int notes[12] = {392, 392, 440, 440, 392, 392, 330, 392, 392, 330, 330, 294};

void setup() {
  for (int note : notes) {
    tone(buzzer, note, 300);
    delay(500);
  }
}

void loop() {
}
