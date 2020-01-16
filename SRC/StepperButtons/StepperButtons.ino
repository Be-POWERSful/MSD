#include <Wire.h>
#include <Adafruit_MotorShield.h>
//#include "utility/Adafruit_PWMServoDriver.h"

// digital pin 2 has a pushbutton attached to it. Give it a name:
const int Button1 = 9;
const int Button2 = 10;
const int LEDL = 2;
const int LEDR = A1;

Adafruit_MotorShield AFMS = Adafruit_MotorShield();

Adafruit_StepperMotor *Motor1 = AFMS.getStepper(200, 1);
Adafruit_StepperMotor *Motor2 = AFMS.getStepper(200, 2);

void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  // make the pushbutton's pin an input:
  pinMode(Button1, INPUT);
  pinMode(LEDL, OUTPUT);
  pinMode(Button2, INPUT);
  pinMode(LEDR, OUTPUT);
  
  // Setup motorshield
  AFMS.begin();
  // Setup stepper motors speeds
  Motor1->setSpeed(10);  // 10 rpm
  Motor2->setSpeed(10);  // 10 rpm
}

void loop() {
  // read the input pin:
  int buttonState1 = digitalRead(Button1);
  int buttonState2 = digitalRead(Button2);
  int user = 0;

  // Always have one of the modes operating
  while(true){
    // Switch states of use outside loops might not be necessary
    if (buttonState1 == HIGH && user == 0){
      user = 1;
    }
    else if (buttonState1 == HIGH && user == 1){
      user = 0;
    }

    // Operate in the user input mode
    if (user == 1){
      while (true){
        digitalWrite(LEDL, HIGH);
        if (buttonState2 == HIGH){
          digitalWrite(LEDR, HIGH);
          // Small steps of alternating motors for appearance of same time
          for (int i = 0; i < 100; i++) {
            Motor1->step(2, FORWARD, SINGLE);
            Motor2->step(2, FORWARD, SINGLE);
          }
          digitalWrite(LEDR, LOW);
        }
        // Both cases may have troubles as not constantly polling
        // Switch modes of operation
        if (buttonState1 == HIGH){
          user == 0;
          break;
        }
      }
    }
    // Operate in the automatic mode
    else {
      while (true){
        // Small steps of alternating motors for appearance of same time
        for (int i = 0; i < 100; i++) {
          Motor1->step(2, FORWARD, SINGLE);
          Motor2->step(2, FORWARD, SINGLE);
        }
        delay(10);
        // Both cases may have troubles as not constantly polling
        // Switch modes of operation
        if (buttonState1 == HIGH){
          user == 1;
          break;
        }
      }
    }
  }
  delay(10);
}
