#include <Arduino.h>
#include <cstdint>

#define BASE_DELAY 1000

void changeMode();
void changeSpeed();

namespace global {
  unsigned int counter = 0;
  bool mode = false;
  uint8_t speed = 0;
  unsigned int delay = 1000;
  unsigned int pines[5] = {PB5, PB6, PB7, PB8, PB9};
  bool led_status = false;
}

void setup() {
  for(int i = 0; i < 5; i++){
    pinMode(global::pines[i], OUTPUT);
  }
  pinMode(PA5, INPUT);
  pinMode(PA6, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  attachInterrupt(PA5, changeMode, RISING);
  attachInterrupt(PA6, changeSpeed, RISING);
}

void loop() {
  for (size_t pos = 0; pos < 5; pos++) {
    bool bit = (global::counter & (1 << pos)) >> pos;
    digitalWrite(
        global::pines[pos], bit
    );
  }
  delay(global::delay);
  global::counter = (!global::mode) 
                  ? global::counter + 1 
                  : global::counter - 1;
  global::delay = (global::speed <= 4) ? BASE_DELAY >> global::speed : 1000;
}

void changeMode() {
  global::mode = !global::mode;
}

void changeSpeed() {
  global::speed = (global::speed <= 4) ? global::speed+1 : 1;
}