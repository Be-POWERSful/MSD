#include <Wire.h>
#include <Adafruit_MotorShield.h>
//#include "utility/Adafruit_PWMServoDriver.h"

// Buttons and LEDs
// digital pin 2 is an interrupt pin
const int Button1 = 2;
const int Button2 = 10;
const int LEDL = 13;
const int LEDR = 9;

// Global variables
const int motorSpeed = 10;
const int numSteps = 200;
const int spareTime = 10;
const int holdTime = 1000;
volatile byte state = LOW;

// used to test the modes
int count = 0;


Adafruit_MotorShield AFMS = Adafruit_MotorShield();

Adafruit_StepperMotor *Motor1 = AFMS.getStepper(200, 1);
Adafruit_StepperMotor *Motor2 = AFMS.getStepper(200, 2);

void setup() {
  // initialize serial communication at 9600 bits per second:
  // Serial.begin(9600);
  // make the pushbutton's pin an input:
  pinMode(Button1, INPUT);
  pinMode(LEDL, OUTPUT);
  pinMode(Button2, INPUT);
  pinMode(LEDR, OUTPUT);

  attachInterrupt(digitalPinToInterrupt(Button1), changestate, CHANGE);
  
  // Setup motorshield
  AFMS.begin();
  // Setup stepper motors speeds
  Motor1->setSpeed(motorSpeed);  // 10 rpm
  Motor2->setSpeed(motorSpeed);  // 10 rpm
}

void loop() {
  // read the input pin:
//  int buttonState1 = digitalRead(Button1);
  int buttonState2 = digitalRead(Button2);

  // Operate in the user input mode
  while (state == HIGH){
    buttonState2 = digitalRead(Button2);
    // Turn on LED to signal user mode
    digitalWrite(LEDL, HIGH);
    if (buttonState2 == HIGH){
      // Turn on second LED to illustrate currently turning
      digitalWrite(LEDR, HIGH);
      // Small steps of alternating motors for appearance of same time
      for (int i = 0; i < numSteps/2; i++) {
        Motor1->step(2, FORWARD, SINGLE);
        Motor2->step(2, FORWARD, SINGLE);
      }
      delay(spareTime);
      // Turn off second LED as it can be rotated again
      digitalWrite(LEDR, LOW);
    }
  }
  // Ensure LED is off for user input mode
  digitalWrite(LEDL, LOW);
  // Operate in the automatic mode
  while (state == LOW){
    // Small steps of alternating motors for appearance of same time
    for (int i = 0; i < numSteps/2; i++) {
      Motor1->step(2, FORWARD, SINGLE);
      Motor2->step(2, FORWARD, SINGLE);
    }
    delay(holdTime);
    count++;
  }
  delay(spareTime);
}

void changestate(){
  // Switch modes of operation when the button is pressed
  state != state;
}
