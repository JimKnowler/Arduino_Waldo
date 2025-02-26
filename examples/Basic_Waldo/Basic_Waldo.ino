// Some basic Waldo example code

#include <Arduino_Waldo.h>

Waldo waldo;

void setup() {
  waldo.setup();
  waldo.add_input_analog("mouth", A0);
}

void loop() {
  waldo.loop();
}