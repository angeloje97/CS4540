
bool switchOn;
bool switchOnCheck;

int pinNum = 10;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(pinNum, INPUT);
   
}

void loop() {

  delay(1);
  digitalWrite(pinNum, HIGH);

  
  switchOn = digitalRead(pinNum) == 1;

  if(switchOn){
    digitalWrite(pinNum,LOW);
  }

  if(switchOnCheck != switchOn){
    switchOnCheck = switchOn;

    

    if(switchOn){
      Serial.print("Switch is on\n");
    }
    else
    {
      Serial.print("Switch is off\n");
    }
  }
}
