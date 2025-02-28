#pragma once

#include "Command.h"

namespace command
{
    class FCommandDecoder
    {
    public:
        FCommandDecoder(FCommand& command);

    private:
        FCommand& Command;
    };
}