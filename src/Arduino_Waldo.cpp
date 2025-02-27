#include "Arduino_Waldo.h"

#include <Arduino.h>

namespace
{
    static const int kMaxNumFramesInFlight = 3;
}

Waldo::Waldo()
{

}

Waldo::~Waldo()
{
    
}

void Waldo::setup() 
{
    Serial.begin(2000000);

    send(FCommand().Message("Arduino Waldo Setup"));

    CurrentState = State::Reset;
}
  
void Waldo::add_input_analog(const char* label, int pin) 
{
    Input input = Input{
        .label = label,
        .pin = pin,
        .id = assignInputId(),
        .type = InputType::Analog
    };

    Inputs.Add(input);

    ensure(CurrentState == State::Reset);
}

void Waldo::add_input_digital(const char* label, int pin) 
{
    Input input = Input{
        .label = label,
        .pin = pin,
        .id = assignInputId(),
        .type = InputType::Digital
    };

    Inputs.Add(input);

    ensure(CurrentState == State::Reset);
}
  
void Waldo::loop() 
{
    switch (CurrentState)
    {
        case State::Reset:
            send(Command.Reset());
            CurrentState = State::WaitAcknowledgeReset;
            break;
        case State::WaitAcknowledgeReset:            
            if (!Parser.Parse(Command)) {
                // not enough data from host to parse a command
                break;
            }
            
            if (Command.GetType() != CommandType::AcknowledgeReset) {
                // ignore unexpected command from host
                break;
            }

            sendInputRegistrations();

            NumFramesInFlight = 0;
            
            CurrentState = State::SendFrame;
            break;
        case State::SendFrame:
            send(Command.StartFrame());

            sendInputValues();

            send(Command.EndFrame());

            NumFramesInFlight += 1;
            
            if (NumFramesInFlight >= kMaxNumFramesInFlight) {
                CurrentState = State::WaitAcknowledgeFrame;
            }
            break;
        case State::WaitAcknowledgeFrame:
            if (!Parser.Parse(Command)) {
                // not enough data from host to parse a command
                break;
            }

            if (Command.GetType() != CommandType::AcknowledgeFrame) {
                // ignore unexpected command from host
                break;
            }

            NumFramesInFlight -= 1;
            
            if (NumFramesInFlight < kMaxNumFramesInFlight) {
                CurrentState = State::SendFrame;
            }

            break;
        case State::None:
        default:
            break;
    }
}

int Waldo::assignInputId()
{
    LastInputId += 1;
    const int id = LastInputId;

    return id;
}

void Waldo::send(const FCommand& command)
{
    const core::Vector<uint8_t>& Data = command.GetData();
    const int numBytes = Data.Num();
    ensure(numBytes < 256);

    const uint8_t type = static_cast<uint8_t>(command.GetType());

    // 1 byte - type
    Serial.write(type);

    // 1 byte - payload size
    Serial.write(numBytes);

    // n bytes - payload
    Serial.write(Data.GetData(), numBytes);
}

void Waldo::sendInputRegistrations()
{
    const int NumInputs = Inputs.Num();
    
    for (int i=0; i<NumInputs; i++)
    {
        const Input& input = Inputs[i];
        send(FCommand().RegisterInput(input));
    }
}

void Waldo::sendInputValues()
{
    const int NumInputs = Inputs.Num();
    
    for (int i=0; i<NumInputs; i++)
    {
        const Input& input = Inputs[i];
        int value;
        switch (input.type)
        {
            case InputType::Analog:
                value = analogRead(input.pin);
                break;
            case InputType::Digital:
                value = digitalRead(input.pin);
                break;
            default:
                value = 0;
                break;
        }

        send(FCommand().InputValue(input, value));
    }
}
