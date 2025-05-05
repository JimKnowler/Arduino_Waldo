// Basic Waldo example code
//
// Using a single potentiometer connected to A0 for the 'mouth'

#include <Waldo.h>

Waldo waldo;

void setup() {
    // Wait for stability on some boards, to prevent garbage Serial
    delay(1000);
    
    Serial.begin(9600);

    // Configure waldo
    waldo.setup();
    waldo.add_input_analog("mouth", A0);
}

void loop() {
    waldo.loop();
}
