#pragma once

#include "Command.h"

namespace command
{
    class FCommandEncoder {
    public:
        FCommandEncoder(FCommand& command);

        ///////////////////////////////////////////////////
        // Device

        FCommand& Reset();

        FCommand& RegisterInput(const FInput& input);

        FCommand& InputValue(const FInput& input, const int value);

        FCommand& StartFrame();

        FCommand& EndFrame();

        FCommand& Message(const core::String& message);

        ///////////////////////////////////////////////////
        // Host

        FCommand& AcknowledgeReset();

        FCommand& AcknowledgeFrame();

    private:
        FCommand& Command;
    };
}
