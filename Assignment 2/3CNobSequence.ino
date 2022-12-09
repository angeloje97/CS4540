

#include <Stepper.h>

bool enabled = true;

int STEPS = 2048;

Stepper stepper(STEPS, 8, 10, 9, 11);

int minSpeed = 5;
int maxSpeed = 20;
int currentSpeed = 10;
int stepperTimer = 0;
bool printStepperTimer = false;
bool printSequenceValues = true;
int sequencePositions[20];
int currentPos = 0;



int pinA = 2;
int pinB = 4;

bool stateA = "OFF";
bool stateACheck;
bool stateB = "OFF";
bool stateBCheck;

int stateATimer = 0;
int stateBTimer = 0;


int stepsPerNob = 20;
int currentNobValue = 0;
int nobTimer = 1000;
int deltaNobValue;
int previousNobValue;

int nobDirection;
int previousNobDirection;

bool printCurrentNobValue = false;
bool printDelta = false;
bool printNobDirection = true;


int currentTime;
int previousTime;
int deltaTime;

int currentStepperValue;




void setup() {
  stepper.setSpeed(currentSpeed);
  Serial.begin(9600);
}

void loop() {
  if(!enabled) return;

//  handleStepper();
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
      stateBTimer = 100;
      currentNobValue -= stepsPerNob;
      printNobValue();
    }
  }

  if(stateBCheck != stateB){
    stateBCheck = stateB;

    if(stateBTimer == 0){
      stateATimer = 100;
      currentNobValue += stepsPerNob;
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

  if(stepperTimer > 0){
    stepperTimer -= deltaTime;

    if(stepperTimer <= 0){
      stepperTimer = 0;
      onStepperTimerComplete();
    }
  }
  
  if(stateATimer > 0){
    stateATimer -= deltaTime;
    stepperTimer = 2000;

    if(stateATimer < 0){
      stateATimer = 0;
    }
  }

  if(stateBTimer > 0){
    stateBTimer -= deltaTime;
    stepperTimer = 2000;
    if(stateBTimer < 0){
      stateBTimer = 0;
    }
  }

  if(nobTimer >= 0){
    nobTimer -= deltaTime;
  }
  else if(nobTimer < 0){
    nobTimer = 250;
    deltaNobValue = currentNobValue - previousNobValue;
    previousNobValue = currentNobValue;

    printDeltaNob();
    handleNobDirection();
  }
}

void handleNobDirection(){
  nobDirection = 0;

  if(deltaNobValue > 0) {
    nobDirection = 1;
  }

  if(deltaNobValue < 0){
    nobDirection = -1;
  }
  
  if(previousNobDirection != nobDirection){
    
    previousNobDirection = nobDirection;

    if(currentPos >= 20){
      return;
    }
    if(nobDirection == 0){
      sequencePositions[currentPos] = currentNobValue;
      currentPos += 1;
    }
    

    if(printNobDirection){
      Serial.print("Nob Direction: ");
      Serial.println(nobDirection);
    }

    
  }
}

void printDeltaNob(){
  if(!printDelta) return;
  
  Serial.print("Delta Nob Value: ");
  Serial.println(deltaNobValue);
}

void onStepperTimerComplete(){
  if(printStepperTimer){
    Serial.println("Stepper timer complete");
  }

  if(printSequenceValues){
    Serial.print("Sequence Array: ");

    for(int i = 0; i < 20; i++){
      if(sequencePositions[i] == 0) break;
      if(i > 0){
        Serial.print(", ");
      }
      Serial.print(sequencePositions[i]);
      
    }
    Serial.println();
  }

  for(int i = 0; i < 20; i++){
    if(sequencePositions[i] == 0) break;
    int target = sequencePositions[i];
    while(currentStepperValue != target){
      if(currentStepperValue < target){
        currentStepperValue += 1;
        stepper.step(1);
      }
      else{
        currentStepperValue -= 1;
        stepper.step(-1);
      }
    }
  }

  clearSequence();
}

void clearSequence(){
  for(int i = 0; i < 20; i++)
  {
    sequencePositions[i] = 0;
  }

  currentPos = 0;
}
