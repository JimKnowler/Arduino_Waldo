// Advanced Waldo example code
//
// - Potentiometers connected to Analog pin A0 for the 'mouth' & A1 for the 'head'
// - Push button connected to Digital pin 2 for blinking

#include <Waldo.h>

Waldo waldo;

// Analog Pins
const uint8_t PinMouth = A0;
const uint8_t PinHead = A1;

// Digital Pins
const uint8_t PinBlink = 2;

void setup() {
    // Wait for stability on some boards, to prevent garbage Serial
    delay(1000);

    Serial.begin(9600);

    // Configure waldo
    waldo.setup();
    waldo.add_input_analog("mouth", PinMouth);
    waldo.add_input_analog("head", PinHead);
    waldo.add_input_digital("blink", PinBlink);
}

void loop() {
    waldo.loop();
}
