// Basic Waldo example code
//
// Using a single potentiometer connected to A0 for the 'mouth'

#include <Arduino_Waldo.h>

Waldo waldo;

void setup() {
  Serial.begin(9600);

  waldo.setup();
  waldo.add_input_analog("mouth", A0);
}

void loop() {
  waldo.loop();
}
