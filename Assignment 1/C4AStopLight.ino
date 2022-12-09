int controllerPin = 10;
int greenPin = 2;
int redPin = 4;  
int bluePin = 6;
int whitePin = 8;

bool switchOn;
bool switchOnCheck;


void setup() {
  
  Serial.begin(9600);
}

void loop() {
  delay(1);
  digitalWrite(controllerPin, HIGH);

  for(int i = 2; i <= 8; i += 2){
    digitalWrite(i, HIGH);

    delay(250);
    digitalWrite(i, LOW);
  }

  switchOn = digitalRead(controllerPin) == 1;

  if(switchOn){
    digitalWrite(controllerPin, LOW);
  }

  if(switchOnCheck != switchOn){
    switchOnCheck = switchOn;

    if(switchOn){
      Serial.print("Switch is on\n");
      OnSwitchOn();
    }
    else{
      Serial.print("Switch is off\n");
    }
  }
}

void OnSwitchOn(){
  
}
