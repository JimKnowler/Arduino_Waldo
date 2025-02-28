#pragma once

#include "Command.h"

namespace command
{
    class FCommandDecoder
    {
    public:
        FCommandDecoder(FCommand& command);

        bool RegisterInput(FInput& outInput);

        bool InputValue(int& outId, int& outValue);

        bool Message(core::String& outMessage);

    private:
        FCommand& Command;
    };
}