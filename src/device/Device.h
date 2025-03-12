#pragma once

#include "core/Vector.h"
#include "core/String.h"
#include "input/Input.h"
#include "state/State.h"
#include "command/CommandByteStream.h"
#include "command/CommandEncoder.h"
#include "command/Command.h"

namespace device
{
    class FDevice
    {
    public:
        FDevice();

        void Setup();

        void AddInput(const FInput& input);

        void Loop();

        int AssignInputId();

    private:
        void SetState(State NewState);
        void SendInputRegistrations();
        void SendInputValues();
        bool ReceiveCommand(command::FCommand& OutCommand);

        command::FCommandByteStream ByteStream;
        command::FCommandEncoder Encoder;
        command::FCommand DecodeCommand;
        command::FCommand EncodeCommand;

        int NumFramesInFlight = 0;

        int LastInputId = 0;

        core::Vector<FInput> Inputs;

        State CurrentState = State::None;

        unsigned long TimeLastCommand = 0;
    };
}
