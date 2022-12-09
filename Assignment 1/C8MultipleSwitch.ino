int leftSwitch = 10;
int middleSwitch = 11;
int rightSwitch = 12;

bool leftSwitchOn;
bool leftSwitchOnCheck;
bool middleSwitchOn;
bool middleSwitchOnCheck;
bool rightSwitchOn;
bool rightSwitchOnCheck;

int currentMode;

int LEFT_SEQUENCE_MODE = 1;
float leftSequenceInterval = 500;
float leftCurrentSequenceInterval = 500;

int middleSwitchLongTime = 1000;
int middleSwitchLongTimer = 1000;
bool middlePressed;

int RIGHT_SEQUENCE_MODE = 2;
float rightSequenceInterval = 500;
float rightCurrentSequenceInterval = 500;

float currentTime = 0;
int greenPin = 0;
int redPin = 1;
int bluePin = 2;
int whitePin = 3;

int currentPinIndex;


void setup() {
  for(int i = 0; i <= 13; i++){
    pinMode(i, INPUT);
  }

}

void loop() {
  delay(1);
  digitalWrite(leftSwitch, HIGH);
  digitalWrite(middleSwitch, HIGH);
  digitalWrite(rightSwitch, HIGH);

  leftSwitchOn = digitalRead(leftSwitch) == 1;
  middleSwitchOn = digitalRead(middleSwitch) == 1;
  rightSwitchOn = digitalRead(rightSwitch) == 1;

  handleLeftSequenceMode();
  handleRightSequenceMode();
  
  for(int i = 10; i <= 12; i++){
    if(digitalRead(i) == 1){
      digitalWrite(i, LOW);
    }
  }

  if(leftSwitchOnCheck != leftSwitchOn){
    leftSwitchOnCheck = leftSwitchOn;

    if(leftSwitchOn){
      onLeftSwitch();
    }
  }

  if(middleSwitchOnCheck != middleSwitchOn){
    middleSwitchOnCheck = middleSwitchOn;

    if(middleSwitchOn){
      onMiddleSwitch();
    }
    else{
      onMiddleSwitchOff();
    }
  }

  if(rightSwitchOnCheck != rightSwitchOn){
    rightSwitchOnCheck = rightSwitchOn;


    if(rightSwitchOn){
      onRightSwitch();
    }
  }

  void HandleTimer();
}


void onLeftSwitch(){
  if(currentMode == LEFT_SEQUENCE_MODE){
    leftCurrentSequenceInterval -= 100;
    if(leftCurrentSequenceInterval < 50){
      leftCurrentSequenceInterval = 50;
    }
    return;
  }

  currentMode = LEFT_SEQUENCE_MODE;
  leftCurrentSequenceInterval = leftSequenceInterval;
}

void handleLeftSequenceMode(){
  if(currentMode != LEFT_SEQUENCE_MODE){
    return;
  }

  if(currentTime < leftCurrentSequenceInterval){
    currentTime ++;
  }
  else{
    currentTime = 0;

    digitalWrite(currentPinIndex, LOW);
    currentPinIndex --;

    if(currentPinIndex < 0){
      currentPinIndex = 3;
    }
  }

  digitalWrite(currentPinIndex, HIGH);
}

void onMiddleSwitch(){
  middlePressed = true;
  middleSwitchLongTimer = middleSwitchLongTime;
}

void onMiddleSwitchOff(){
  middlePressed = false;
}

void onMiddleLongSwitch() {
  if(currentMode == 0){
    return;
  }

  currentMode = 0;

  for(int i = 0; i < 4; i++){
    digitalWrite(i, LOW);
  }
}

void HandleTimer(){
  if(middlePressed){
    middleSwitchLongTimer -= 1;

    if(middleSwitchLongTimer <= 0){
      middlePressed = false;
      onMiddleLongSwitch();
    }
  }
}

void onRightSwitch(){
  if(currentMode == RIGHT_SEQUENCE_MODE){
    rightCurrentSequenceInterval -= 100;

    if(rightCurrentSequenceInterval <= 50){
      rightCurrentSequenceInterval = 50;
    }
    return; 
  }

  currentMode = RIGHT_SEQUENCE_MODE;
  rightCurrentSequenceInterval = rightSequenceInterval;
}

void handleRightSequenceMode(){
  if(currentMode != RIGHT_SEQUENCE_MODE){
    return;
  }

  if(currentTime < rightCurrentSequenceInterval){
    currentTime ++;
  }
  else
  {
    currentTime = 0;
    digitalWrite(currentPinIndex, LOW);
    currentPinIndex++;
    currentPinIndex %= 4;
  }

  digitalWrite(currentPinIndex, HIGH);
}
