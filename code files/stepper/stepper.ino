#include<Stepper.h>
const int spr = 200;
Stepper steper(spr, 8, 9, 10, 11);

void setup() {
  // put your setup code here, to run once:
  steper.setSpeed(60);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  steper.step(spr);
  delay(1000);
  steper.step(-spr);
  delay(1000);
}
