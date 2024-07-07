#include <PS2X_lib.h>
#include <Servo.h>

PS2X ps2x;

#define PS2_DAT  13
#define PS2_CMD  11
#define PS2_SEL  10
#define PS2_CLK  12

Servo servo1;
Servo servo2;

const int motorLeftForward = 5;
const int motorLeftBackward = 6;
const int motorRightForward = 7;
const int motorRightBackward = 8;

void setup() {
  Serial.begin(9600);

  servo1.attach(9);
  servo2.attach(10);

  pinMode(motorLeftForward, OUTPUT);
  pinMode(motorLeftBackward, OUTPUT);
  pinMode(motorRightForward, OUTPUT);
  pinMode(motorRightBackward, OUTPUT);

  int error = ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT, true, true);

  if (error == 0) {
    Serial.println("Found Controller, configured successful");
  } else {
    Serial.println("Controller not found or error in configuration");
  }
}

void loop() {
  ps2x.read_gamepad(false, 0);

  // ควบคุมมอเตอร์ล้อ
  if (ps2x.Button(PSB_PAD_UP)) {
    analogWrite(motorLeftForward, 255);
    analogWrite(motorLeftBackward, 0);
    analogWrite(motorRightForward, 255);
    analogWrite(motorRightBackward, 0);
  } else if (ps2x.Button(PSB_PAD_DOWN)) {
    analogWrite(motorLeftForward, 0);
    analogWrite(motorLeftBackward, 255);
    analogWrite(motorRightForward, 0);
    analogWrite(motorRightBackward, 255);
  } else if (ps2x.Button(PSB_PAD_LEFT)) {
    analogWrite(motorLeftForward, 0);
    analogWrite(motorLeftBackward, 255);
    analogWrite(motorRightForward, 255);
    analogWrite(motorRightBackward, 0);
  } else if (ps2x.Button(PSB_PAD_RIGHT)) {
    analogWrite(motorLeftForward, 255);
    analogWrite(motorLeftBackward, 0);
    analogWrite(motorRightForward, 0);
    analogWrite(motorRightBackward, 255);
  } else {
    analogWrite(motorLeftForward, 0);
    analogWrite(motorLeftBackward, 0);
    analogWrite(motorRightForward, 0);
    analogWrite(motorRightBackward, 0);
  }

  // ควบคุมเซอร์โว
  static int servo1Position = 90;
  static int servo2Position = 90;

  if (ps2x.Button(PSB_SQUARE)) {
    servo1Position = constrain(servo1Position + 1, 0, 180);
  } else if (ps2x.Button(PSB_CIRCLE)) {
    servo1Position = constrain(servo1Position - 1, 0, 180);
  }

  if (ps2x.Button(PSB_CROSS)) {
    servo2Position = constrain(servo2Position + 1, 0, 180);
  } else if (ps2x.Button(PSB_TRIANGLE)) {
    servo2Position = constrain(servo2Position - 1, 0, 180);
  }

  servo1.write(servo1Position);
  servo2.write(servo2Position);

  delay(100);
}
