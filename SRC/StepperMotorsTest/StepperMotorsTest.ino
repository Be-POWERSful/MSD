#include <Wire.h>
#include <Adafruit_MotorShield.h>
//#include "utility/Adafruit_PWMServoDriver.h"

Adafruit_MotorShield AFMS = Adafruit_MotorShield();

Adafruit_StepperMotor *Motor1 = AFMS.getStepper(200, 1);
Adafruit_StepperMotor *Motor2 = AFMS.getStepper(200, 2);

void setup() {
  // put your setup code here, to run once:
  AFMS.begin();

  Motor1->setSpeed(10);  // 10 rpm
  Motor2->setSpeed(10);  // 10 rpm
}

void loop() {
  // put your main code here, to run repeatedly:

  // Small steps of alternating motors for appearance of same time
  for (int i = 0; i < 100; i++) {
    Motor1->step(2, FORWARD, SINGLE);
    Motor2->step(2, FORWARD, SINGLE);
  }
}
