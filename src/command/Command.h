#ifndef COMMAND_H
#define COMMAND_H

#include "CommandType.h"

#include "core/Vector.h"
#include "core/String.h"

#include "input/Input.h"

#include <stdint.h>

namespace command
{
    /**
     * @struct FCommand
     * @brief Encapsulate a command and its' arguments
     */
    class FCommand
    {
    public:
        ECommandType GetType() const;

        const core::Vector<uint8_t>& GetData() const;

    private:
        friend class FCommandByteStream;
        friend class FCommandEncoder;
        
        ECommandType Type;

        core::Vector<uint8_t> Data;
    };
}

#endif
