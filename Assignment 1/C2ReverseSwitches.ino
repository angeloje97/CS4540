int controllerPin = 10;
int greenPin = 4;

bool switchOn;
bool switchOnCheck;


void setup() {
  
  Serial.begin(9600);
}

void loop() {
  delay(1);
  digitalWrite(controllerPin, HIGH);

  
  digitalWrite(greenPin, switchOn ? LOW : HIGH);

  switchOn = digitalRead(controllerPin) == 1;

  if(switchOn){
    digitalWrite(controllerPin, LOW);
  }

  if(switchOnCheck != switchOn){
    switchOnCheck = switchOn;

    if(switchOn){
      Serial.print("Switch is on\n");
    }
    else{
      Serial.print("Switch is off\n");
    }
  }
}
