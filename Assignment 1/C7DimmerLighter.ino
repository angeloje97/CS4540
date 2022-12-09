int lightingSwitch = 12;
int dimmingSwitch = 10;
int lightLED = 8;

bool lighting;
bool dimming;

float lightingMaxValue = 1000;
float lightingCurrentValue = 0;
float percentageValue = 0;

void setup() {
  pinMode(lightingSwitch, INPUT);
  pinMode(dimmingSwitch, INPUT);
  pinMode(lightLED, INPUT);

}

void loop() {
  delay(1);
  digitalWrite(lightingSwitch, HIGH);
  digitalWrite(dimmingSwitch, HIGH);

  lighting = digitalRead(lightingSwitch) == 1;
  dimming = digitalRead(dimmingSwitch) == 1;

  if(lighting && dimming){
    lighting = false;
    dimming = false;

    digitalWrite(lightingSwitch, LOW);
    digitalWrite(dimmingSwitch, LOW);
  }

  if(lighting){
    digitalWrite(lightingSwitch, LOW);
    if(lightingCurrentValue < lightingMaxValue){
      lightingCurrentValue += 1;
    }
  }

  if(dimming){
    digitalWrite(lightingSwitch, LOW);
    
    if(lightingCurrentValue > 0) {
      lightingCurrentValue -= 1;
    }
  }

  percentageValue = lightingCurrentValue / lightingMaxValue;

  digitalWrite(lightLED, percentageValue);
}
