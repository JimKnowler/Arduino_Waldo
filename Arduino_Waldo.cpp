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

// TODO: add timeout, such that if host doesn't respond after 'n' seconds then the arduino client restarts and waits for a connection
// TODO: perhaps we should have a special character that can be used to flush the serial port connection at any time.
//       - the device can send this when it times out and effectively restart the serial communication.
//       - perhaps it could be associated with a unique ID, that the host can acknowledge and reply with to confirm that the 
//         connection has been successfully reset.


Waldo::Waldo()
{

}

Waldo::~Waldo()
{
    
}

void Waldo::setup() 
{
    Serial.begin(2000000);
    // TODO: print message on serial (that host should ignore) that waldo has taken ownership of the serial port, and that if you
    //       are reading this in a serial message window then it will stop the waldo host from receiving the message
    Serial.print("Waldo library");

    // TODO: wait for host to respond (or enter state where we're waiting for host to respond)
}
  
void Waldo::add_input_analog(const char* label, int pin) 
{
    Input input = Input{
        .label = label,
        .pin = pin,
        .id = assignInputId(),
        .type = Input::Type::Analog
    };

    Inputs.Add(input);
    
    // TODO: send message to host (or notify state machine that there are new inputs to register)    
}

void Waldo::add_input_digital(const char* label, int pin) 
{
    Input input = Input{
        .label = label,
        .pin = pin,
        .id = assignInputId(),
        .type = Input::Type::Digital
    };

    Inputs.Add(input);
    
    // TODO: send message to host (or notify state machine that there are new inputs to register)
}
  
void Waldo::loop() 
{
    // TODO: state machine
    //  - handle timeout on connection + resetting
    //  - handle registering inputs - when connection is reset, and when new inputs are registered

    // TODO: take care of sending the current state of each sensor to the host
    //  - ANALOG: analogRead(pin)
    //  - DIGIAL: digitalRead(pin)

    // TODO: flow control - keep track of how much data is being sent to the host, and wait for host to ack

    // TODO: should we sleep in here, or make sure that main script has control of frame rate (/battery usage)
}

int Waldo::assignInputId()
{
    lastInputId += 1;
    const int id = lastInputId;

    return id;
}
