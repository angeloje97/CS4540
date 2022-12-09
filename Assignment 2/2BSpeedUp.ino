

#include <Stepper.h>

bool enabled = true;

int STEPS = 2048;

Stepper stepper(STEPS, 8, 10, 9, 11);

int currentSpeed = 2;
int maxSpeed = 25;

void setup() {
  stepper.setSpeed(currentSpeed);
  Serial.begin(9600);
}

void loop() {
  if(!enabled) return;

  if(currentSpeed < maxSpeed){
    stepper.step(STEPS/8);
    currentSpeed += 1;

    Serial.print("The current Speed is ");
    Serial.println(currentSpeed);
  }
  else{
    long int t1 = millis();
    stepper.step(STEPS);
    long int t2 = millis();

    long int timeDifference = t2 - t1;
    Serial.println("One revolution has passed");
    Serial.print("Total time taken: ");
    Serial.print(timeDifference);
    Serial.println("ms");
  }

  

  stepper.setSpeed(currentSpeed);

}

/* 
  It seems that I can go up to a maximum of 25 speed before the motor is going to break;
*/
