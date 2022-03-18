/** DC Motor
 * 1. DC 모터를 회전/역회전으로 돌려보기 
 */

int lfw = 2; // 왼쪽 앞 바퀴
int lbw = 4; // 왼쪽 뒷 바퀴
int lsp = 5; // 왼쪽 바퀴 속도

void setup() {
  pinMode(lfw, OUTPUT);
  pinMode(lbw, OUTPUT);
  pinMode(lsp, OUTPUT);

  analogWrite(lsp, 255);
  // 정회전
  digitalWrite(lfw, HIGH);
  digitalWrite(lbw, LOW);
  delay(2000);

  // 역회전
  digitalWrite(lfw, LOW);
  digitalWrite(lbw, HIGH);
  delay(2000);

  analogWrite(lsp, 180); // 속도 저하
  delay(2000);

  // 정지
  analogWrite(lsp, 0);
  digitalWrite(lfw, LOW);
  digitalWrite(lbw, LOW);
}

void loop() {

}
