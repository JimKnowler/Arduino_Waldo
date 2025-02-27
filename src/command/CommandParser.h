#pragma once

#include "Command.h"

/**
 * @class FCommandParser
 * @brief Parse input from serial connection to generate commands
 * 
 */
class FCommandParser
{
public:
    FCommandParser();

    void Reset();

    bool Parse(FCommand& OutCommand);

private:
    // is there enough data in the buffer to parse the next command
    bool IsReadyToParseCommand() const;

    // parse buffer into OutCommand and empty the buffer
    void ParseCommandAndConsumeBuffer(FCommand& OutCommand);

    core::Vector<uint8_t> Buffer;
};
