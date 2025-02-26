#include "Arduino_Waldo.h"

#include <Arduino.h>

/*
  if (Serial.available() > 0)
  {
    int byte = Serial.read();

    Serial.print("I received: ");
    Serial.println(byte, DEC);
  }
*/

Waldo::Waldo()
{

}

Waldo::~Waldo()
{
    
}

void Waldo::setup() {
    Serial.begin(2000000);
    // TODO: print message on serial (that host should ignore) that waldo has taken ownership of the serial port, and that if you
    //       are reading this in a serial message window then it will stop the waldo host from receiving the message
    Serial.print("Waldo library");

    // TODO: wait for host to respond
}
  
void Waldo::add_input_analog(const char* label, int pin) {
    // TODO: keep a local registry of sensors, with unique IDs
    
    // TODO: send message to host 
}

void Waldo::add_input_digital(const char* label, int pin) {
    // TODO: keep a local registry of sensors, with unique IDs
    
    // TODO: send message to host 
}
  
void Waldo::loop() {
    // TODO: take care of sending the current state of each sensor to the host
    //  - ANALOG: analogRead(pin)
    //  - DIGIAL: digitalRead(pin)

    // TODO: flow control - keep track of how much data is being sent to the host, and wait for host to ack

    // TODO: should we sleep in here, or make sure that main script has control of frame rate (/battery usage)
}


