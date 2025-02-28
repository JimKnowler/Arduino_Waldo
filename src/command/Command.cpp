#include "Command.h"

namespace command
{
    ECommandType FCommand::GetType() const 
    {
        return Type;
    }

    const core::Vector<uint8_t>& FCommand::GetData() const
    {
        return Data;
    }
}
