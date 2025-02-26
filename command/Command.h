#pragma once

#include "CommandType.h"

#include "core/Vector.h"
#include "core/String.h"

#include "input/Input.h"

/**
 * @struct Command
 * @brief Encapsulate a command and its' arguments
 */
class Command
{
public:
    CommandType GetType() const;

    const core::Vector<uint8_t>& GetData() const;

    void SetReset();

    void SetResetAcknowledge();

    void SetRegisterInput(const Input& input);

    void SetInputValue(const Input& input, int value);

private:
    friend class CommandParser;
    
    CommandType Type;

    core::Vector<uint8_t> Data;
};
