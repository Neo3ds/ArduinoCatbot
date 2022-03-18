/** Buzzer
 * 1. 수동 부저를 이용하여 만들고 싶은 멜로디를 완성해주세요.
 */
int buzzer = 3;

void setup() {
  tone(buzzer, 392, 300);
  delay(500);
  tone(buzzer, 392, 300);
  delay(500);
  tone(buzzer, 440, 300);
  delay(500);
  tone(buzzer, 440, 300);
  delay(500);
  tone(buzzer, 392, 300);
  delay(500);
  tone(buzzer, 392, 300);
  delay(500);
  tone(buzzer, 330, 300);
  delay(500);
  
  tone(buzzer, 392, 300);
  delay(500);
  tone(buzzer, 392, 300);
  delay(500);
  tone(buzzer, 330, 300);
  delay(500);
  tone(buzzer, 330, 300);
  delay(500);
  tone(buzzer, 294, 300);
  delay(500);
}

void loop() {
}
