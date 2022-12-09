int greenPin = 8;
int controllerPin = 10;

bool switchOn;

void setup() {
  pinMode(greenPin, INPUT);
  pinMode(controllerPin, INPUT);

}

void loop() {
  digitalWrite(controllerPin, HIGH);


  switchOn = digitalRead(controllerPin) == 1;

  digitalWrite(greenPin, switchOn ? HIGH: LOW);

  if(switchOn){
    digitalWrite(controllerPin, LOW);
  }

}
