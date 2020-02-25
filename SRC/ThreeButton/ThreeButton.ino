#include <Wire.h>
#include <Adafruit_MotorShield.h>
//#include "utility/Adafruit_PWMServoDriver.h"

// Flashlight goes in 3.3 V and one of the GND pins
// Buttons and LEDs
// digital pin 2 is an interrupt pin
const int Button1 = 10;
const int Button2 = 2;
const int Button3 = 8;
const int LED1 = 13;
const int LED2 = 9;
const int LED3 = 6;

// Global variables
const int motorSpeed = 1000;
const int spareTime = 10;
const int holdTime = 1000;
const int fullSteps = 200;
const int miniSteps = 2;
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
  pinMode(LED1, OUTPUT);
  pinMode(Button2, INPUT);
  pinMode(LED2, OUTPUT);
  pinMode(Button3, INPUT);
  pinMode(LED3, OUTPUT);

  // Setup Ground and Power
  pinMode(A0, OUTPUT);
  digitalWrite(A0, LOW);
  pinMode(A1, OUTPUT);
  digitalWrite(A1, HIGH);
  pinMode(A2, OUTPUT);
  digitalWrite(A2, LOW);
  pinMode(A3, OUTPUT);
  digitalWrite(A3, LOW);
  pinMode(7, OUTPUT);
  digitalWrite(7, HIGH);
  
  // Setup motorshield
  AFMS.begin();
  // Setup stepper motors speeds
  Motor1->setSpeed(motorSpeed);  // 10 rpm
  Motor2->setSpeed(motorSpeed);  // 10 rpm
}

int buttonState1 = digitalRead(Button1);
int buttonState2 = digitalRead(Button2);
int buttonState3 = digitalRead(Button3);

void loop() {
  // read the input pin:
  buttonState1 = digitalRead(Button1);
  digitalWrite(LED1, HIGH);

  if (buttonState1 == HIGH){
    manual();
  }
  else {
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, LOW);
    automatic();
  }
  delay(spareTime);
}

void automatic(){
  // Small steps of alternating motors for appearance of same time
  for (int i = 0; i < fullSteps/miniSteps; i++) {
    Motor1->step(miniSteps, FORWARD, DOUBLE);
    Motor2->step(miniSteps, BACKWARD, DOUBLE);
  } 
  delay(holdTime);
}

void manual(){
  buttonState2 = digitalRead(Button2);
  buttonState3 = digitalRead(Button3);
  
  // Turn on LED to signal user mode
  digitalWrite(LED2, HIGH);
  digitalWrite(LED3, HIGH);
  if (buttonState2 == HIGH){
    // Turn on second LED to illustrate currently turning
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, LOW);
    // Full quarter rotation of motor one for seperate wheel use
    for (int i = 0; i < fullSteps/miniSteps; i++) {
      Motor1->step(miniSteps, FORWARD, DOUBLE);
      delay(spareTime);
    } 
    // Turn off second LED as it can be rotated again
  }
  else if (buttonState3 == HIGH){
    // Turn on second LED to illustrate currently turning
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, LOW);
    // Full quarter rotation of motor two for seperate wheel use
    for (int i = 0; i < fullSteps/miniSteps; i++) {
      Motor2->step(miniSteps, BACKWARD, DOUBLE);
      delay(spareTime);
    } 
    // Turn off second LED as it can be rotated again
  }
}
