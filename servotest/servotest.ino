#include <Servo.h>

Servo myservo;

int pos = 0; 

void setup() {
  myservo.attach(9);
}

void loop() { 
  myservo.write(0);
  delay(2000);
  myservo.write(45);
  delay(2000);
  myservo.write(90);
  delay(2000);
  
}

