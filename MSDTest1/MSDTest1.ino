/*
  DigitalReadSerial

  Reads a digital input on pin 2, prints the result to the Serial Monitor

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/DigitalReadSerial
*/

// digital pin 2 has a pushbutton attached to it. Give it a name:
int ButtonL = 2;
int ButtonR = 10;
int LEDL = 13;
int LEDR = 9;

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  // make the pushbutton's pin an input:
  pinMode(ButtonL, INPUT);
  pinMode(LEDL, OUTPUT);
  pinMode(ButtonR, INPUT);
  pinMode(LEDR, OUTPUT);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input pin:
  int bL = digitalRead(ButtonL);
  int bR = digitalRead(ButtonR);

  Serial.print(bL);
  if (bL == HIGH){
    
    digitalWrite(LEDL, HIGH);
   
  }

if(bL==LOW){
    digitalWrite(LEDL, LOW);
}

    if (bR == HIGH){
    digitalWrite(LEDR, HIGH);
   
  }

    if (bR == LOW){
    digitalWrite(LEDR, LOW);
   
  }
  
  delay(100);        // delay in between reads for stability
}
