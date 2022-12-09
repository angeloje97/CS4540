/*
 * MotorKnob
 *
 * A stepper motor follows the turns of a potentiometer
 * (or other sensor) on analog input 0.
 *
 * http://www.arduino.cc/en/Reference/Stepper
 * This example code is in the public domain.
 */

#include <Stepper.h>

bool enabled = true;

// change this to the number of steps on your motor
#define STEPS 2048

// create an instance of the stepper class, specifying
// the number of steps of the motor and the pins it's
// attached to
Stepper stepper(STEPS, 8, 10, 9, 11);
  
// the previous reading from the analog input
int previous = 0;

void setup() {
  // set the speed of the motor to 30 RPMs
  stepper.setSpeed(10);
  Serial.begin(9600);
}

void loop() {
  if(!enabled) return;
  // get the sensor value
  Serial.println("Rotating normal");
  stepper.step(STEPS/2);
  Serial.println("Rotating the other way");
  stepper.step(-(STEPS/2));

}

/*
 * Question 2A: does it return to it’s original start point? Or has it forgotten where it is.
 * I don't think it remembers where the original start point is in memory.
 * However it goe sdirectly back to where the starting point is because
 * That's just how precise it is..
   */
