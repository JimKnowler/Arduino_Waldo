// Advanced Waldo example code
//
// - Potentiometers connected to A0 for the 'mouth' & A1 for the 'head'
// - Push button connected to D0 for blinking

#include <Waldo.h>

Waldo waldo;

void setup() {
    // Wait for stability on some boards, to prevent garbage Serial
    delay(1000);

    Serial.begin(9600);

    // Configure waldo
    waldo.setup();
    waldo.add_input_analog("mouth", A0);
    waldo.add_input_analog("head", A1);
    waldo.add_input_digital("blink", D0);
}

void loop() {
    waldo.loop();
}
