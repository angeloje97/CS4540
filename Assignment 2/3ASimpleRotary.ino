

#include <Stepper.h>

bool enabled = true;

int STEPS = 2048;

Stepper stepper(STEPS, 8, 10, 9, 11);

int pinA = 2;
int pinB = 4;

bool stateA = "OFF";
bool stateACheck;
bool stateB = "OFF";
bool stateBCheck;

int stateATimer = 0;
int stateBTimer = 0;

int currentSpeed = 10;

int stepsPerNob = 20;
int currentNobValue = 0;
bool printCurrentNobValue = true;

int currentStepperValue;


void setup() {
  stepper.setSpeed(currentSpeed);
  Serial.begin(9600);
}

void loop() {
  if(!enabled) return;

  handleStepper();
  handleRotary();

}

void handleStepper(){
  if(currentStepperValue == currentNobValue) return;

  if(currentStepperValue < currentNobValue){
    currentStepperValue += 1;
    stepper.step(1);
    
  }
  else{
    currentStepperValue -= 1;
    stepper.step(-1);
    
  }
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
  if(stateATimer > 0){
    stateATimer -= 1;

    if(stateATimer <0){
      stateATimer = 0;
    }
  }

  if(stateBTimer > 0){
    stateBTimer -= 1;
    if(stateBTimer < 0){
      stateBTimer = 0;
    }
  }
}
