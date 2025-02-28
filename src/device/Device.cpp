#include "Device.h"

#include <Arduino.h>

namespace device 
{
    static const int kMaxNumFramesInFlight = 3;

    FDevice::FDevice() : Encoder(Command)
    {
        
    }

    void FDevice::Setup()
    {
        Serial.begin(500000);

        ByteStream.Send(Encoder.Message("Arduino Waldo Setup"));
    
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
                ByteStream.Send(Encoder.Reset());
                CurrentState = State::WaitAcknowledgeReset;
                break;
            case State::WaitAcknowledgeReset:            
                if (!ByteStream.Receive(Command)) {
                    // not enough data from host to parse a command
                    break;
                }
                
                if (Command.GetType() != command::ECommandType::AcknowledgeReset) {
                    // ignore unexpected command from host
                    break;
                }

                SendInputRegistrations();

                NumFramesInFlight = 0;
                
                CurrentState = State::SendFrame;
                break;
            case State::SendFrame:
                ByteStream.Send(Encoder.StartFrame());

                SendInputValues();

                ByteStream.Send(Encoder.EndFrame());

                NumFramesInFlight += 1;
                
                if (NumFramesInFlight >= kMaxNumFramesInFlight) {
                    CurrentState = State::WaitAcknowledgeFrame;
                }
                break;
            case State::WaitAcknowledgeFrame:
                if (!ByteStream.Receive(Command)) {
                    // not enough data from host to receive a command
                    break;
                }

                if (Command.GetType() != command::ECommandType::AcknowledgeFrame) {
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

    void FDevice::SendInputRegistrations()
    {
        const int NumInputs = Inputs.Num();
        
        for (int i=0; i<NumInputs; i++)
        {
            const FInput& input = Inputs[i];
            ByteStream.Send(Encoder.RegisterInput(input));
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

            ByteStream.Send(Encoder.InputValue(input, value));
        }
    }

} // namespace device 

