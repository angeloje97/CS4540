bool longBlink;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.print(HIGH);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  longBlink = false;
  for(int i = 0; i < 3; i++){
    for(int i = 0; i < 3; i++)
    {
      digitalWrite(8, HIGH);
      delay(longBlink ? 500 : 250);
      digitalWrite(8, LOW);
      delay(longBlink ? 500 : 250);
    }

    longBlink = !longBlink;
  }

  delay(1000);
}
