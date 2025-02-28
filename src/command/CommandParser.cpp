#pragma once

#include "CommandParser.h"

#include <Arduino.h>

// TODO: ignore random data in serial comms, until a command is available
//       header/footer for each command?

FCommandParser::FCommandParser()
{
    Buffer.SetSize(32);
}

void FCommandParser::Reset()
{
    Buffer.Reset();
}

bool FCommandParser::Parse(FCommand& OutCommand)
{
    const int available = Serial.available();

    for (int i=0; i<available; i++)
    {
        const int byte = Serial.read();

        Buffer.Add(byte);

        if (IsReadyToParseCommand())
        {
            ParseCommandAndConsumeBuffer(OutCommand);

            return true;
        }
    }

    return false;
}

bool FCommandParser::IsReadyToParseCommand() const
{
    const int BufferSize = Buffer.Num();

    if (BufferSize < 2) {
        return false;
    }

    const int CommandPayloadSize = Buffer[1];
    const int CommandSize = 2 + CommandPayloadSize;
    if (BufferSize < CommandSize) 
    {
        return false;
    }
    
    ensure(BufferSize == CommandSize);

    return true;
}

void FCommandParser::ParseCommandAndConsumeBuffer(FCommand& OutCommand)
{
    const int Type = Buffer[0];
    const int CommandPayloadSize = Buffer[1];

    const int CommandSize = 2 + CommandPayloadSize;
    ensure(Buffer.Num() == CommandSize);

    OutCommand.Type = static_cast<CommandType>(Type);
    OutCommand.Data = Buffer.Slice(2, CommandPayloadSize);

    Buffer.Reset();
}
