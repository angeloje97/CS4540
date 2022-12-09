

#include <Stepper.h>

bool enabled = true;

int STEPS = 2048;

Stepper stepper(STEPS, 8, 10, 9, 11);

int currentSpeed = 10;

void setup() {
  stepper.setSpeed(currentSpeed);
  Serial.begin(9600);
}

void loop() {
  if(!enabled) return;
  stepper.step(STEPS/4);
  Serial.println("Quater revolutions turned");

}
