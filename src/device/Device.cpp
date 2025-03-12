#include "Device.h"

#include <Arduino.h>

// Enable whether the device will timeout and restart connection
#define ENABLE_TIMEOUT 1

// Debug receiving commands, by echoing them back to host as messages
#define ENABLE_ECHO_COMMANDS 0

// Debug current state, by reporting it to host every loop in a message
#define ENABLE_ECHO_STATE 0

// Debug state changes, by reporting them to host as messages
#define ENABLE_ECHO_STATE_CHANGES 0

// Debug timeouts, by reporting them to host as messages
#define ENABLE_ECHO_TIMEOUT 0

namespace device 
{
    static const int kMaxNumFramesInFlight = 3;
    static const unsigned long kMaxMillisBetweenCommands = 2000;

    FDevice::FDevice() : Encoder(EncodeCommand)
    {
        
    }

    void FDevice::Setup()
    {
        ByteStream.Reset();

        ByteStream.Send(Encoder.Message("Arduino Waldo Setup"));
    
        SetState(State::Reset);

        TimeLastCommand = millis();
    }

    void FDevice::AddInput(const FInput& input)
    {
        Inputs.Add(input);

        ensure(CurrentState == State::Reset);
    }

    void FDevice::Loop()
    {
#if ENABLE_ECHO_STATE
        {
            char temp[64];
            sprintf(temp, "current state [%d] time since last command [%lu]",
                static_cast<int>(CurrentState), (millis() - TimeLastCommand));
            ByteStream.Send(Encoder.Message(temp));
        }
#endif
        switch (CurrentState)
        {
            case State::Reset:
                ByteStream.Send(Encoder.Reset());
                SetState(State::WaitAcknowledgeReset);
                break;
            case State::WaitAcknowledgeReset:
            {
                if (!ReceiveCommand(DecodeCommand)) {
                    // not enough data from host to parse a command
                    break;
                }
                
                switch (DecodeCommand.GetType())
                {
                    case command::ECommandType::AcknowledgeReset:
                    {
                        SendInputRegistrations();

                        NumFramesInFlight = 0;
                        
                        SetState(State::SendFrame);

                        break;
                    }
                    case command::ECommandType::Reset:
                    {
                        SetState(State::Reset);

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
                    SetState(State::WaitAcknowledgeFrame);
                }
            
                break;
            }
            case State::WaitAcknowledgeFrame:
            {
                if (!ReceiveCommand(DecodeCommand)) {
                    // not enough data from host to receive a command
                    break;
                }

                switch (DecodeCommand.GetType())
                {
                    case command::ECommandType::AcknowledgeFrame:
                    {
                        NumFramesInFlight = core::Max(NumFramesInFlight - 1, 0);
                        
                        if (NumFramesInFlight < kMaxNumFramesInFlight) {
                            SetState(State::SendFrame);
                        }
            
                        break;
                    }
                    case command::ECommandType::Reset:
                    {
                        SetState(State::Reset);

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

        if (ByteStream.Receive(OutCommand))
        {
            TimeLastCommand = currentTime;

#if ENABLE_ECHO_COMMANDS
            {
                char temp[64];
                sprintf(temp, "received command [%c] while in state [%d]",
                    static_cast<char>(OutCommand.GetType()), static_cast<int>(CurrentState));
                ByteStream.Send(Encoder.Message(temp));
            }
#endif

            return true;
        }        

#if ENABLE_TIMEOUT
        const unsigned long elapsed = currentTime - TimeLastCommand;

        if (elapsed > kMaxMillisBetweenCommands)
        {
#if ENABLE_ECHO_TIMEOUT
            {
                char temp[64];
                sprintf(temp, "timeout - while in state [%d]", static_cast<int>(CurrentState));
                ByteStream.Send(Encoder.Message(temp));
            }
#endif

            ByteStream.Reset();
            TimeLastCommand = currentTime;
            SetState(State::WaitAcknowledgeReset);
            NumFramesInFlight = 0;
        }
#endif

        return false;
    }

    void FDevice::SetState(State NewState)
    {
#if ENABLE_ECHO_STATE_CHANGES
        char temp[64];
        sprintf(temp, "SetState [%d] - while in state [%d]", static_cast<int>(NewState), static_cast<int>(CurrentState));
        ByteStream.Send(Encoder.Message(temp));
#endif 
        CurrentState = NewState;
    }

} // namespace device 

