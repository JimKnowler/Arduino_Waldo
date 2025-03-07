#pragma once

#include "Command.h"

namespace command
{
    /**
     * @class FCommandParser
     * @brief Parse input from serial connection to generate commands
     * 
     */
    class FCommandByteStream
    {
    public:
        FCommandByteStream();

        void Setup();

        void Reset();

        bool Receive(FCommand& OutCommand);
        
        void Send(const FCommand& Command);

    private:
        void SkipToGuard();

        // is there enough data in the buffer to parse the next command
        bool IsReadyToParseCommand() const;

        // parse buffer into OutCommand and empty the buffer
        void ParseCommandAndConsumeBuffer(FCommand& OutCommand);

        core::Vector<uint8_t> Buffer;

        core::Vector<uint8_t> Guard;
    };
}
