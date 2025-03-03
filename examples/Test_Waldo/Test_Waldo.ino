// Run Waldo automated unit tests

#include <AUnit.h>

void setup() {
    // wait for stability on some boards, to prevent garbage Serial
    delay(1000);

    Serial.begin(9600);
}

void loop() {
    aunit::TestRunner::run();
}
