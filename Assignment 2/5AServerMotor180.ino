

#include <Servo.h>

Servo myservo;  

int potpin = A0;  
int val;    

int currentAngle = 0;
int currentDirection = 10;
int currentSpeed = 10;

bool enabled = true;

void setup() {
  myservo.attach(7);
  Serial.begin(9600);
  currentDirection = currentSpeed;
}

void loop() {
  if(!enabled) return;
  val = analogRead(potpin);          
  val = map(val, 0, 1023, 0, 180);     
  myservo.write(currentAngle);
  currentAngle += currentDirection;

  if(currentAngle < 0){
    currentDirection = currentSpeed;
    delay(1000);
  }
  if(currentAngle >= 180){
    currentDirection = -currentSpeed;
    delay(1000);
  }
  delay(15);        
}                   
