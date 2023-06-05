#include <Arduino.h>

unsigned int counter = 0;
bool mode = false;
byte speed = 0;
unsigned int delay = 1000;

void setup() {
  for(int i = 5; i < 15; i++){
    pinMode(PB0+i, OUTPUT);
  }
  pinMode(PA5, INPUT);
  pinMode(PA6, INPUT);
  attachInterrupt(PA5, changeMode, RISING);
  attachInterrupt(PA6, changeMode, RISING);
}

void loop() {
  // put your main code here, to run repeatedly:

}

void changeMode() {
    mode = !mode;
}

void changeSpeed() {
    speed = (speed <= 4) ? speed++ : 1;
}

unsigned int computeDelay() {
    delay = (speed < 4) ? delay >> speed : 1000;
}