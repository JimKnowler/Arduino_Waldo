#ifndef COMMAND_H
#define COMMAND_H

#include "CommandType.h"

#include "core/Vector.h"
#include "core/String.h"

#include "input/Input.h"

#include <stdint.h>

/**
 * @struct FCommand
 * @brief Encapsulate a command and its' arguments
 */
class FCommand
{
public:
    CommandType GetType() const;

    const core::Vector<uint8_t>& GetData() const;

    ///////////////////////////////////////////////////
    // Device

    FCommand& Reset();

    FCommand& RegisterInput(const Input& input);

    FCommand& InputValue(const Input& input, int value);

    FCommand& StartFrame();

    FCommand& EndFrame();

    FCommand& Message(const core::String& message);

    ///////////////////////////////////////////////////
    // Host

    FCommand& AcknowledgeReset();

    FCommand& AcknowledgeFrame();

private:
    friend class FCommandParser;
    
    CommandType Type;

    core::Vector<uint8_t> Data;
};

#endif
