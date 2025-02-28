#include "Device.h"

#include <Arduino.h>

namespace device 
{
    static const int kMaxNumFramesInFlight = 3;

    void FDevice::Setup()
    {
        Serial.begin(500000);

        Send(FCommand().Message("Arduino Waldo Setup"));
    
        CurrentState = State::Reset;
    }

    void FDevice::AddInput(const FInput& input)
    {
        Inputs.Add(input);

        ensure(CurrentState == State::Reset);
    }

    void FDevice::Loop()
    {
        switch (CurrentState)
        {
            case State::Reset:
                Send(Command.Reset());
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

                SendInputRegistrations();

                NumFramesInFlight = 0;
                
                CurrentState = State::SendFrame;
                break;
            case State::SendFrame:
                Send(Command.StartFrame());

                SendInputValues();

                Send(Command.EndFrame());

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

    int FDevice::AssignInputId()
    {
        LastInputId += 1;
        const int id = LastInputId;

        return id;
    }

    void FDevice::Send(const FCommand& command)
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

    void FDevice::SendInputRegistrations()
    {
        const int NumInputs = Inputs.Num();
        
        for (int i=0; i<NumInputs; i++)
        {
            const FInput& input = Inputs[i];
            Send(FCommand().RegisterInput(input));
        }
    }

    void FDevice::SendInputValues()
    {
        const int NumInputs = Inputs.Num();
        
        for (int i=0; i<NumInputs; i++)
        {
            const FInput& input = Inputs[i];
            int value;
            switch (input.type)
            {
                case EInputType::Analog:
                    value = analogRead(input.pin);
                    break;
                case EInputType::Digital:
                    value = digitalRead(input.pin);
                    break;
                default:
                    value = 0;
                    break;
            }

            Send(FCommand().InputValue(input, value));
        }
    }

} // namespace device 

