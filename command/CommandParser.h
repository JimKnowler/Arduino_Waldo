#pragma once

#include "Command.h"

/**
 * @class CommandParser
 * @brief Parse input from serial connection to generate commands
 * 
 */
class CommandParser
{
public:
    CommandParser();

    void Reset();

    bool Parse(Command& OutCommand);

private:
    // is there enough data in the buffer to parse the next command
    bool IsReadyToParseCommand() const;

    // parse buffer into OutCommand and empty the buffer
    void ParseCommandAndConsumeBuffer(Command& OutCommand);

    core::Vector<uint8_t> Buffer;
};
