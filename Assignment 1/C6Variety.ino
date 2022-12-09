int controllerPin = 10;
int greenPin = 2;
int redPin = 4;  
int bluePin = 6;
int whitePin = 8;

bool switchOn;
bool switchOnCheck;

bool stopLightMode;
bool discoMode;


bool clicked;
bool doubleClicked;
float doubleClickTimer = 1000;
float doubleClickTime;
bool pressing;
bool longPressed;
float longPressDelay = 1000;
float longPressTime;


float stopLightTimer = 500;
float stopLightTime = 0;
int stopLightIndex = 2;

float discoTimer = 150;
float discoTime = 0;
int randomIndex = 2;

void setup() {
  
  Serial.begin(9600);
}

void loop() {
  delay(1);
  digitalWrite(controllerPin, HIGH);

  handleTimers();
  handleStopLightMode();
  handleDiscoMode();
  
  switchOn = digitalRead(controllerPin) == 1;

  if(switchOn){
    digitalWrite(controllerPin, LOW);
  }

  if(switchOnCheck != switchOn){
    switchOnCheck = switchOn;

    if(switchOn){
      onSwitchOn();
    }
    else{
      onSwitchOff();
    }
  }
}

void handleTimers(){

  if(pressing){
    longPressTime++;
    if(longPressTime > longPressDelay){
      onLongPress();
      longPressed = true;
      pressing = false;
    }
  }

  if(clicked){
    if(doubleClicked){
      doubleClicked = false;
      clicked = false;
    }
    doubleClickTime ++;

    if(doubleClickTime > doubleClickTimer){
      clicked = false;
      onShortPress();
      doubleClickTime = 0;
    }
  }
}

void onSwitchOn(){
  pressing = true;
  doubleClicked = false;
}

void onSwitchOff(){
  pressing = false;
  longPressTime = 0;

  if(longPressed){
    longPressed = false;
    return;
  }

  if(clicked){
    onDoublePress();
    doubleClickTime = 0;
    doubleClicked = true;
    clicked = false;
    return;
  }

  clicked = true;
}

void onLongPress(){
  stopLightMode = false;
  discoMode = false;
  pressing = false;
  Serial.print("Long pressed\n");

  for(int i = 2; i <= 8; i += 2){
    digitalWrite(i, LOW);
  }
}

void onShortPress(){
  Serial.print("Short pressed \n");
  stopLightMode = true;
  discoMode = false;
}

void onDoublePress(){
  Serial.print("Double pressed \n");
  stopLightMode = false;
  discoMode = true;

}

void handleDiscoMode(){
  if(!discoMode) return;
  discoTime ++;

  for(int i = 2; i <= 8; i+=2){
    digitalWrite(i, i == randomIndex ? HIGH : LOW);
  }

  if(discoTime > discoTimer){
    discoTime = 0;

    int currentIndex = randomIndex;

    while(randomIndex == currentIndex){
      randomIndex = random(1,5)*2;
    }
  }
  
}

void handleStopLightMode(){
  if(!stopLightMode) return;
  stopLightTime++;
  
  digitalWrite(stopLightIndex, HIGH);
  
  for(int i = 2; i <= 8; i += 2){
    if(i != stopLightIndex){
      digitalWrite(i, LOW);
    }
  }

  if(stopLightTime > stopLightTimer){
    stopLightIndex += 2;
    stopLightTime = 0;

    if(stopLightIndex > 8){
      stopLightIndex = 2;
    }
  }
}
