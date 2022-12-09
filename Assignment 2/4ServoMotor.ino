

#include <Servo.h>

Servo myservo;  

int potpin = A0;  
int val;    

int currentAngle = 0;
int currentDirection = 10;
int currentSpeed = 1;

bool enabled = true;

void setup() {
  myservo.attach(7);
  Serial.begin(9600);
  currentDirection = currentSpeed;
}

void loop() {
  val = analogRead(potpin);          
  val = map(val, 0, 1023, 0, 180);     
  myservo.write(currentAngle);
  currentAngle += currentDirection;

  delay(15);     
}                      
