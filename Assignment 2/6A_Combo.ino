

#include <Stepper.h>
#include <Servo.h>

bool enabled = true;

int STEPS = 2048;

Servo servo;
Stepper stepper(STEPS, 8, 10, 9, 11);

int minSpeed = 10;
int maxSpeed = 20;
float currentSpeed = 10;

int pinA = 2;
int pinB = 4;

bool stateA = "OFF";
bool stateACheck;
bool stateB = "OFF";
bool stateBCheck;

int stateATimer = 0;
int stateBTimer = 0;


int stepsPerNob = 50;
int currentNobValue = 0;
int nobTimer = 1000;
int deltaNobValue;
int previousNobValue;
int currentNobDirection;
bool printCurrentNobValue = false;
bool printDelta = false;

int currentTime;
int previousTime;
int deltaTime;

int currentStepperValue;

float servoTarget = 0;
float currentServoValue = 0;
int servoTimer;


void setup() {
  stepper.setSpeed(currentSpeed);
  Serial.begin(9600);
  servo.attach(7);

}

void loop() {
  if(!enabled) return;

  handleStepper();
  handleServo();
  handleRotary();

}

void handleStepper(){
  if(currentStepperValue == currentNobValue) return;
  if(currentNobDirection == 0) return;
  stepper.step(currentNobDirection);
}

void handleServo(){
  if(servoTimer > 0){
    servoTimer -= deltaTime;
    return;
  }

  servoTimer = 8;
  float previousTarget = servoTarget - currentNobDirection;

  if(previousTarget == servoTarget) return;
  
  
  servoTarget -= currentNobDirection;
  

  if(servoTarget < 0){
    servoTarget = 0;
  }

  if(servoTarget > 180){
    servoTarget = 180;
  }

  if(servoTarget == currentServoValue) return;
  float difference = servoTarget - currentServoValue;

  if(servoTarget > currentServoValue){
    currentServoValue += 1;
  }
  else{
    currentServoValue -= 1;
  }

  servo.write(currentServoValue);
  
}

void handleRotary() {
  stateA = digitalRead(pinA) == 0;
  stateB = digitalRead(pinB) == 0;

  handleTimers();

  if(stateACheck != stateA){
    stateACheck = stateA;

    if(stateATimer == 0){
      stateBTimer = 200;
      currentNobValue += stepsPerNob;
      printNobValue();
    }
  }

  if(stateBCheck != stateB){
    stateBCheck = stateB;

    if(stateBTimer == 0){
      stateATimer = 200;
      currentNobValue -= stepsPerNob;
      printNobValue();
    }
  }
  
}

void printNobValue(){
  if(!printCurrentNobValue) return;
  Serial.print("Current Nob Value: ");
  Serial.println(currentNobValue);
}

void handleTimers(){
  currentTime = millis();
  deltaTime = currentTime - previousTime;
  previousTime = currentTime;

  
  if(stateATimer > 0){
    stateATimer -= deltaTime;

    if(stateATimer < 0){
      stateATimer = 0;
    }
  }

  if(stateBTimer > 0){
    stateBTimer -= deltaTime;
    if(stateBTimer < 0){
      stateBTimer = 0;
    }
  }

  if(nobTimer >= 0){
    nobTimer -= deltaTime;
  }
  else if(nobTimer < 0){
    nobTimer = 500;
    deltaNobValue = currentNobValue - previousNobValue;
    previousNobValue = currentNobValue;
    printDeltaNobValue();
    handleNobSpeed(deltaNobValue);
  }
}

void handleNobSpeed(int nobSpeed){
  if(nobSpeed < 0){
    currentNobDirection = - 1;
  }
  else if(nobSpeed > 0){
    currentNobDirection = 1;
  }
  else{
    currentNobDirection = 0;
  }

  
  
  if(nobSpeed < 0){
    nobSpeed = -nobSpeed;
  }

  
  float maxNobSpeed = 1000;
  
  if(nobSpeed > maxNobSpeed){
    nobSpeed = maxNobSpeed;
  }
  
  float speedPercent = nobSpeed / maxNobSpeed;
  float stepperSpeedDifference = maxSpeed - minSpeed;
  currentSpeed = minSpeed + (speedPercent * stepperSpeedDifference);
  
  Serial.print("New Speed: ");
  Serial.println(currentSpeed);
  Serial.print("Current nob direction: ");
  Serial.println(currentNobDirection);
  stepper.setSpeed(currentSpeed);

  Serial.print("Servo Target: ");
  Serial.println(servoTarget);
}

void printDeltaNobValue(){
  if(!printDelta) return;
  Serial.print("Nob speed: ");
  Serial.print(deltaNobValue);
  Serial.println(" steps per second");
}
