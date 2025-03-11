#include "Device.h"

#include <Arduino.h>

#define USE_TIMEOUT 0

namespace device 
{
    static const int kMaxNumFramesInFlight = 3;
    static const unsigned long kMaxMillisBetweenCommands = 500;

    FDevice::FDevice() : Encoder(Command)
    {
        
    }

    void FDevice::Setup()
    {
        ByteStream.Reset();

        ByteStream.Send(Encoder.Message("Arduino Waldo Setup"));
    
        CurrentState = State::Reset;

        TimeLastCommand = millis();
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
            {
                if (!ReceiveCommand(Command)) {
                    // not enough data from host to parse a command
                    break;
                }
                
                switch (Command.GetType())
                {
                    case command::ECommandType::AcknowledgeReset:
                    {
                        SendInputRegistrations();

                        NumFramesInFlight = 0;
                        
                        CurrentState = State::SendFrame;

                        break;
                    }
                    case command::ECommandType::Reset:
                    {
                        CurrentState = State::Reset;

                        break;
                    }
                    default:
                        break;
                }
                
                break;
            }
            case State::SendFrame:
            {
                ByteStream.Send(Encoder.StartFrame());

                SendInputValues();

                ByteStream.Send(Encoder.EndFrame());

                NumFramesInFlight = core::Min(NumFramesInFlight + 1, kMaxNumFramesInFlight);
                
                if (NumFramesInFlight >= kMaxNumFramesInFlight) {
                    CurrentState = State::WaitAcknowledgeFrame;
                }
            
                break;
            }
            case State::WaitAcknowledgeFrame:
            {
                if (!ReceiveCommand(Command)) {
                    // not enough data from host to receive a command
                    break;
                }

                switch (Command.GetType())
                {
                    case command::ECommandType::AcknowledgeFrame:
                    {
                        NumFramesInFlight = core::Max(NumFramesInFlight - 1, 0);
                        
                        if (NumFramesInFlight < kMaxNumFramesInFlight) {
                            CurrentState = State::SendFrame;
                        }
            
                        break;
                    }
                    case command::ECommandType::Reset:
                    {
                        CurrentState = State::Reset;

                        break;
                    }
                    default:
                        break;
                }             

                break;
            }
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

    bool FDevice::ReceiveCommand(command::FCommand& OutCommand)
    {
        const unsigned long currentTime = millis();

        if (ByteStream.Receive(Command))
        {
            TimeLastCommand = currentTime;

            return true;
        }        

#if USE_TIMEOUT
        const unsigned long elapsed = currentTime - TimeLastCommand;

        if (elapsed > kMaxMillisBetweenCommands)
        {
            ByteStream.Send(Encoder.Message("timeout\n"));

            ByteStream.Reset();
            TimeLastCommand = currentTime;
            CurrentState = State::WaitAcknowledgeReset;
            NumFramesInFlight = 0;
        }
#endif

        return false;
    }

} // namespace device 

