/*
 * 캣봇 중급자 코드
 * Author: TaeJune Joung
 * Enterprise: NEO3DS
 * Date: 21.12.20
 * License:
 *  본 코드의 저작권은 위와 같으며,
 *  상업적인 무단 도용시 법적인 책임을 물을 수 있음을 공지합니다.
 */

#include <SoftwareSerial.h>
#include <Servo.h>

#define PIN_BT_TX       A4
#define PIN_BT_RX       A5
#define RIGHT_DC_FW      2
#define RIGHT_DC_BW      4
#define LEFT_DC_FW       7
#define LEFT_DC_BW       8
#define RIGHT_DC_PWM     5
#define LEFT_DC_PWM      6
#define PIN_LEFT_LED    A0
#define PIN_RIGHT_LED   10
#define PIN_TRIG        12
#define PIN_ECHO        13
#define PIN_BUZZER       3
#define PIN_SERVO        9

SoftwareSerial bt(PIN_BT_TX, PIN_BT_RX);
Servo servo;

int motorSpeed = 255;
unsigned long intervalTime = 200;
int servoAngleList[3] = {90, 160, 20};

char cmd;
char beforeCommand = 'x';

/**
 * ledCtrl
 * @params
 *  -leftState: true -> left led on / false -> left led off
 *  -rightState: true -> right led on / false -> right led off
 */
void ledCtrl(boolean leftState, boolean rightState) {
  digitalWrite(PIN_LEFT_LED, leftState);
  digitalWrite(PIN_RIGHT_LED, rightState);
}

/**
 * motorCtrl
 * @params
 *  -leftState
 *  -rightState
 *  -leftSpeed
 *  -rightSpeed
 */
void motorCtrl(boolean leftState, boolean rightState, int leftSpeed, int rightSpeed) {
  digitalWrite(LEFT_DC_FW, leftState);
  digitalWrite(LEFT_DC_BW, !leftState);
  digitalWrite(RIGHT_DC_FW, rightState);
  digitalWrite(RIGHT_DC_BW, !rightState);
  analogWrite(LEFT_DC_PWM, leftSpeed);
  analogWrite(RIGHT_DC_PWM, rightSpeed);
}

/**
 * motorStop
 */
void motorStop() {
  digitalWrite(LEFT_DC_FW, false);
  digitalWrite(LEFT_DC_BW, false);
  digitalWrite(RIGHT_DC_FW, false);
  digitalWrite(RIGHT_DC_BW, false);
  analogWrite(LEFT_DC_PWM, 0);
  analogWrite(RIGHT_DC_PWM, 0);
  ledCtrl(false, false);
}

/**
 * getDistance
 * @return distance(cm)
 */
float getDistance() {
  digitalWrite(PIN_TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(PIN_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(PIN_TRIG, LOW);
  return pulseIn(PIN_ECHO, HIGH) / 58.0;
}

/**
 * getBluetoothData
 */
void getBluetoothData() {
  if (bt.available()) {
    cmd = bt.read();
    
    if (cmd != beforeCommand) {
      motorStop();
      beforeCommand = cmd;
    }
    
    switch (cmd) {
      case 'F': {
        motorStop();
        servo.write(servoAngleList[0]);
        motorCtrl(true, true, motorSpeed, motorSpeed);
        ledCtrl(true, true);
        break;
      }
      case 'L': {
        motorStop();
        servo.write(servoAngleList[1]);
        motorCtrl(true, true, motorSpeed-100, motorSpeed);
        blinkLedCtrl(cmd, 0);
        break;
      }
      case 'R': {
        motorStop();
        servo.write(servoAngleList[2]);
        motorCtrl(true, true, motorSpeed, motorSpeed-100);
        blinkLedCtrl(cmd, 1);
        break;
      }
      case 'B': {
        motorStop();
        servo.write(servoAngleList[0]);
        motorCtrl(false, false, motorSpeed-50, motorSpeed-50);
        blinkLedCtrl(cmd, 2);
        break;
      }
      case 'S': {
        motorStop();
        break;
      }
      case 'A': {
        autoDriving(cmd);
        break;
      }
    }
  }
}

/**
 * blinkLedCtrl
 * @params
 *  -command: bluetooth command character
 *  -val: 0->left / 1->right / 2->both
 */
void blinkLedCtrl(char command, int val) {
  unsigned long blinkTime = millis();
  boolean ledState = false;
  while (cmd == command) {
    if (millis() - blinkTime > intervalTime) {
      ledState = !ledState;
      blinkTime = millis();
      if (val == 0) {
        ledCtrl(ledState, false);
      } else if (val == 1) {
        ledCtrl(false, ledState);
      } else if (val == 2) {
        ledCtrl(ledState, ledState);
      }
      tone(PIN_BUZZER, 392, 100);
    }
    getBluetoothData();
  }
}

/**
 * drivingCtrl
 * @params
 *  -command: bluetooth command character
 *  -commandTime: bluetooth command time
 *  -val: 0->left / 1->right / 2->both
 */
void drivingCtrl(char command, unsigned long commandTime, int val) {
  unsigned long currentTime = millis();
  unsigned long blinkTime = millis();
  boolean ledState = false;
  while (cmd == command && millis() - currentTime < commandTime) {
    if (millis() - blinkTime > intervalTime) {
      ledState = !ledState;
      blinkTime = millis();
      if (val == 0) {
        ledCtrl(ledState, false);
      } else if (val == 1) {
        ledCtrl(false, ledState);
      } else if (val == 2) {
        ledCtrl(ledState, ledState);
      }
      tone(PIN_BUZZER, 392, 100);
    }
    getBluetoothData();
  }
}

/**
 * autoDriving
 * @params
 *  -command: bluetooth command character
 */
void autoDriving(char command) {
  boolean isChange = true;
  while (cmd == command) {
    float distance = getDistance();
    if (distance > 20) {
      if (isChange)
        motorStop();
        delay(10);
        isChange = false;
      servo.write(servoAngleList[0]);
      motorCtrl(true, true, motorSpeed-50, motorSpeed-50);
      ledCtrl(true, true);
    } else {
      isChange = true;
      motorStop();
      delay(10);
      servo.write(servoAngleList[0]);
      motorCtrl(false, false, motorSpeed-50, motorSpeed-50);
      drivingCtrl(command, 1000, 2);
      motorStop();
      delay(10);
      int direct = analogRead(A1) % 2;
      if (direct == 0) {
        servo.write(servoAngleList[1]);
        motorCtrl(true, true, motorSpeed-100, motorSpeed-50);
        drivingCtrl(command, 1500, 0);
      } else {
        servo.write(servoAngleList[2]);
        motorCtrl(true, true, motorSpeed-50, motorSpeed-100);
        drivingCtrl(command, 1500, 1);
      }
      motorStop();
      delay(10);
    }
    getBluetoothData();
  }
}

void setup() {
  bt.begin(9600);
  pinMode(LEFT_DC_FW, OUTPUT);
  pinMode(LEFT_DC_BW, OUTPUT);
  pinMode(RIGHT_DC_FW, OUTPUT);
  pinMode(RIGHT_DC_BW, OUTPUT);
  pinMode(LEFT_DC_PWM, OUTPUT);
  pinMode(RIGHT_DC_PWM, OUTPUT);
  pinMode(PIN_LEFT_LED, OUTPUT);
  pinMode(PIN_RIGHT_LED, OUTPUT);
  pinMode(PIN_TRIG, OUTPUT);
  pinMode(PIN_ECHO, INPUT);
  pinMode(PIN_BUZZER, OUTPUT);

  servo.attach(PIN_SERVO);
  servo.write(servoAngleList[0]);

  tone(PIN_BUZZER, 912, 100);
  delay(150);
  tone(PIN_BUZZER, 912, 100);
  delay(150);

  boolean ledState = false;
  for (int i=0; i < 5; i++) {
    ledState = !ledState;
    ledCtrl(ledState, ledState);
    delay(200);
  }
}

void loop() {
  getBluetoothData();
}
