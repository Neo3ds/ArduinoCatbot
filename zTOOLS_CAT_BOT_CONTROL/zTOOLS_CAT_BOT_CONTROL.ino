/**
 * 캣봇 다기능 처리
 * @Auth TaeJuneJoung
 * @Date 2021.10.18
 */

#define PIN_RIGHT_DC_FW      2
#define PIN_RIGHT_DC_BW      4
#define PIN_LEFT_DC_FW       7
#define PIN_LEFT_DC_BW       8
#define PIN_RIGHT_DC_SP      5
#define PIN_LEFT_DC_SP       6
#define PIN_BUZZER           3
#define PIN_SERVO            9
#define PIN_RIGHT_LED       10
#define PIN_LEFT_LED        A0
#define PIN_TRIG            12
#define PIN_ECHO            13
#define PIN_BT_TX           A4
#define PIN_BT_RX           A5

#include <SoftwareSerial.h>
#include <Servo.h>

SoftwareSerial BT(PIN_BT_TX, PIN_BT_RX);
Servo servo;

const int START_VAL = 255;
const int DATA_LEN = 12;
const int END_VALUE = 10;

unsigned char buf[DATA_LEN];
unsigned char prevc;
unsigned long currentTime;
int index = 0;
int mode = -1;
boolean isStart = false;

int STOP_SIGN = 0;
int FRONT_SIGN = 1;
int LEFT_SIGN = 2;
int RIGHT_SIGN = 3;
int BACK_SIGN = 4;

int LEFT_ANGLE = 60;
int BASE_ANGLE = 90;
int RIGHT_ANGLE = 120;
int beforeAngle = 90;

int motorSpeed = 100;

boolean PIANO_LED[8][3] = {
  {true, false, false}, {false, true, false}, {false, false, true},
  {true, true, false}, {true, false, true}, {false, true, true},
  {true, true, true}, {true, false, false}
}; 

int NOTES[7][8] = {
  {33, 37, 41, 44, 49, 55, 62, 65},
  {65, 73, 82, 87, 98, 110, 123, 131},
  {131, 147, 165, 175, 196, 220, 247, 262},
  {262, 294, 330, 349, 392, 440, 494, 523},
  {523, 587, 659, 698, 784, 880, 988, 1046},
  {1046, 1175, 1319, 1397, 1568, 1760, 1976, 2093},
  {2093, 2349, 2637, 2794, 3136, 3520, 3951, 4186}
};

/**
 * Pin Init Function
 */
void pinInit() {
  for (int pin=2; pin < 13; pin++) {
    pinMode(pin, OUTPUT);
  }
  pinMode(PIN_ECHO, INPUT);
  pinMode(PIN_LEFT_LED, OUTPUT);
  servo.attach(PIN_SERVO);
}

/**
 * Get Bluetooth Data
 * @params c
 */
void getUpdateData(unsigned char c) {
  if (c == DATA_LEN && isStart == false) {
    if (prevc == START_VAL) {
      isStart = true;
      index = 1;
      writeBuffer(index-1, prevc);
      writeBuffer(index, c);
    }
  } else {
    prevc = c;
    if (isStart) {
      writeBuffer(index, c);
    }
  }

  index++;

  if (index > DATA_LEN) {
    isStart = false;
    index=0;
  }

  if (isStart && index == DATA_LEN && index > 3) {
    isStart = false;
    parseData();
    index = 0;
  }
}

/**
 * Check Buffer Sum Data
 * @return boolean
 */
bool isCheckOk() {
  if (buf[DATA_LEN-1] == END_VALUE) {
    int checkSum = buf[DATA_LEN-2];
    int sumValue = 0;
    for (int i=2; i<DATA_LEN-2; i++) {
      sumValue += buf[i];
    }
    sumValue = sumValue & 0xff;
    if (checkSum == sumValue) {
      return true;
    }
  }
  return false;
}

/**
 * Read Buffer Data
 * @params index
 */
unsigned char readBuffer(int index) {
  return buf[index];
}

/**
 * Write Buffer Data
 * @params c
 */
void writeBuffer(int index, unsigned char c) {
  buf[index] = c;
}

/**
 * Control DC Motor
 * @params direct, motorSpeed
 * 
 * direct
 * 0: Stop
 * 1: Forward
 * 2: Left
 * 3: Right
 * 4: Backward
 */
void motorCtrl(int direct) {
  analogWrite(PIN_RIGHT_DC_SP, motorSpeed);
  analogWrite(PIN_LEFT_DC_SP, motorSpeed);
  if (direct == STOP_SIGN) {
    digitalWrite(PIN_RIGHT_DC_FW, LOW);
    digitalWrite(PIN_RIGHT_DC_BW, LOW);
    digitalWrite(PIN_LEFT_DC_FW, LOW);
    digitalWrite(PIN_LEFT_DC_BW, LOW);
    analogWrite(PIN_RIGHT_DC_SP, 0);
    analogWrite(PIN_LEFT_DC_SP, 0);
  } else if (direct == FRONT_SIGN) { // 전진
    digitalWrite(PIN_RIGHT_DC_FW, HIGH);
    digitalWrite(PIN_RIGHT_DC_BW, LOW);
    digitalWrite(PIN_LEFT_DC_FW, HIGH);
    digitalWrite(PIN_LEFT_DC_BW, LOW);
  } else if (direct == LEFT_SIGN) { // 좌측
    digitalWrite(PIN_RIGHT_DC_FW, HIGH);
    digitalWrite(PIN_RIGHT_DC_BW, LOW);
    digitalWrite(PIN_LEFT_DC_FW, LOW);
    digitalWrite(PIN_LEFT_DC_BW, HIGH);
  } else if (direct == RIGHT_SIGN) { // 우측
    digitalWrite(PIN_RIGHT_DC_FW, LOW);
    digitalWrite(PIN_RIGHT_DC_BW, HIGH);
    digitalWrite(PIN_LEFT_DC_FW, HIGH);
    digitalWrite(PIN_LEFT_DC_BW, LOW);
  } else if (direct == BACK_SIGN) { // 후진
    digitalWrite(PIN_RIGHT_DC_FW, LOW);
    digitalWrite(PIN_RIGHT_DC_BW, HIGH);
    digitalWrite(PIN_LEFT_DC_FW, LOW);
    digitalWrite(PIN_LEFT_DC_BW, HIGH);
  }
}

/**
 * Get Ultrasonic Sensor Distance Value
 * @return distance
 */
 float getDistance() {
  digitalWrite(PIN_TRIG, LOW);
  digitalWrite(PIN_ECHO, LOW);
  delayMicroseconds(2);
  digitalWrite(PIN_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(PIN_TRIG, LOW);
  float duration = pulseIn(PIN_ECHO, HIGH);
  return duration / 29.0 / 2;
}

void delayTimes(int command, unsigned long sleepTime) {
  currentTime = millis();
  while (millis() - currentTime < sleepTime) {
    getData();
    if (mode != command) {
      motorCtrl(STOP_SIGN);
      return;
    }
  }
}

/**
 * Obstacle Avoidance Driving: Direction
 * @params command, direct, turnTime, leftSpeed, rightSpeed
 */
void obstacleDirectionMove(int command, int direct, unsigned long turnTime) {
  currentTime = millis();

  if (direct) {
    motorCtrl(LEFT_SIGN);
  } else {
    motorCtrl(RIGHT_SIGN);
  }
  
  while (millis() - currentTime < turnTime) {
    getData();
    if (mode != command) {
      motorCtrl(STOP_SIGN);
      return;
    }
  }
  motorCtrl(STOP_SIGN);
}

/**
 * Obstacle Avoidance Driving
 * @params distance, direct, turnTime
 * 
 * direct
 * 0: Right Hand on Wall
 * 1: Left Hand on Wall
 * 2: Random
 * 3: Smart
 */
void obstacleAvoidanceDriving(int distance, int direct, int turnTime) {
  int command = 1;
  analogWrite(PIN_RIGHT_DC_SP, motorSpeed);
  analogWrite(PIN_LEFT_DC_SP, motorSpeed);
  
  while (mode == command) {
    float distanceVal = getDistance();
    if (distanceVal > distance) {
      motorCtrl(FRONT_SIGN);
    } else {
      motorCtrl(STOP_SIGN);
      unsigned long turnTimeVal = turnTime * 100;
      if (direct == 0) { // Right Hand on Wall
        obstacleDirectionMove(command, 0, turnTimeVal);
      } else if (direct == 1) { // Left Hand on Wall
        obstacleDirectionMove(command, 1, turnTimeVal);
      } else if (direct == 2) { // Random
        int randomNumber = random(direct);
        obstacleDirectionMove(command, randomNumber, turnTimeVal);
      } else if (direct == 3) { // Smart
        int obstacleDistanceList[2] = {0, 0};
        servo.write(LEFT_ANGLE);
        delayTimes(command, 300);
        obstacleDistanceList[0] = getDistance();
        delayTimes(command, 500);
        servo.write(RIGHT_ANGLE);
        obstacleDistanceList[1] = getDistance();
        delayTimes(command, 500);
        servo.write(BASE_ANGLE);

        if (obstacleDistanceList[0] > obstacleDistanceList[1]) {
          obstacleDirectionMove(command, 1, turnTimeVal);
        } else {
          obstacleDirectionMove(command, 0, turnTimeVal);
        }
      }
    }
    getData();
  }
}

/**
 * Parse Data 
 */
void parseData() {
  if (isCheckOk()) {
    mode = readBuffer(2);
    int angleValue = readBuffer(3);
    int rightLedValue = readBuffer(4);
    int leftLedValue = readBuffer(5);
    int directValue = readBuffer(6);
    motorSpeed = readBuffer(7);

    if (mode == 0) { // General Control Mode
      if (beforeAngle != angleValue) {
        beforeAngle = angleValue;
        servo.attach(PIN_SERVO);
        servo.write(angleValue);
      }
      boolean rightLedState = rightLedValue > 0 ? true : false;
      boolean leftLedState = leftLedValue > 0 ? true : false;
      digitalWrite(PIN_RIGHT_LED, rightLedState);
      digitalWrite(PIN_LEFT_LED, leftLedState);
      motorCtrl(directValue);
      delay(100); // 지터링 현상 방지를 위해
      servo.detach();
    } else if (mode == 1) { // Obstracle Avoidance Driving
      obstacleAvoidanceDriving(angleValue, rightLedValue, leftLedValue);
    }
  }
}

/**
 * Get Bluetooth Data
 */
void getData() {
  if (BT.available()) {
    unsigned char c = BT.read();
    getUpdateData(c);
  }
}

void setup() {
  BT.begin(9600);
  pinInit();
  randomSeed(analogRead(0));

  servo.write(BASE_ANGLE);
  
  tone(PIN_BUZZER, 912, 100);
  delay(150);
  tone(PIN_BUZZER, 912, 100);
  delay(150);
  servo.detach();
}

void loop() {
  getData();
}
