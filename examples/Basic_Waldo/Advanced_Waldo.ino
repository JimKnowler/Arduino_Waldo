// Advanced Waldo example code
//
// - Potentiometers connected to A0 for the 'mouth' & A1 for the 'head'
// - Push button connected to D0 for blinking

#include <Arduino_Waldo.h>

Waldo waldo;

void setup() {
  Serial.begin(9600);

  waldo.setup();
  waldo.add_input_analog("mouth", A0);
  waldo.add_input_analog("head", A1);
  waldo.add_input_digital("blink", D0);
}

void loop() {
  waldo.loop();
}
