#pragma once

#include "CommandParser.h"

#include <Arduino.h>

CommandParser::CommandParser()
{
    Buffer.SetSize(32);
}

void CommandParser::Reset()
{
    Buffer.Reset();
}

bool CommandParser::Parse(Command& OutCommand)
{
    const int available = Serial.available();

    for (int i=0; i<available; i++)
    {
        const int byte = Serial.read();

        Buffer.Add(byte);

        if (ReadyToParse()) 
        {
            ParseCommandAndConsumeBuffer(OutCommand);

            return true;
        }
    }

    return false;
}

bool CommandParser::IsReadyToParseCommand() const
{
    const int BufferSize = Buffer.Num();

    if (BufferSize < 2) {
        return false;
    }

    const int CommandPayloadSize = Buffer[1];
    const int CommandSize = 2 + CommandPayloadSize;
    if (Buffer < CommandSize) 
    {
        return false;
    }
    
    return (Buffer == CommandSize);
}

void CommandParser::ParseCommandAndConsumeBuffer(Command& OutCommand)
{
    const int Type = Buffer[0];
    const int CommandSize = Buffer[1];
    OutCommand = {
        .Type = static_cast<CommandType>(Type),
        .Data = Buffer.Slice(2, CommandSize);
    };

    ensure(Buffer.Length() == (2 + CommandSize));
    Buffer.Reset();
}
