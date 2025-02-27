#pragma once

#include "core/Vector.h"
#include "core/String.h"
#include "input/Input.h"
#include "state/State.h"
#include "command/CommandParser.h"
#include "command/Command.h"

namespace device
{
    class FDevice
    {
    public:
        void Setup();

        void AddInput(const FInput& input);

        void Loop();

        int AssignInputId();

    private:

        void Send(const FCommand& command);
        void SendInputRegistrations();
        void SendInputValues();

        FCommandParser Parser;
        FCommand Command;

        int NumFramesInFlight = 0;

        int LastInputId = 0;

        core::Vector<FInput> Inputs;

        State CurrentState = State::None;
    };
}
