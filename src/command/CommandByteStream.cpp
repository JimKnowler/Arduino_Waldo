#pragma once

#include "CommandByteStream.h"

#include <Arduino.h>

namespace command
{
    // TODO: ignore random data in serial comms, until a command is available
    //       header/footer for each command?

    FCommandByteStream::FCommandByteStream()
    {
        Buffer.SetSize(32);
    }

    void FCommandByteStream::Setup()
    {
        // TODO: is there any value in adding delay() here to prevent noise on serial connection?

        Serial.begin(9600);        
    }

    void FCommandByteStream::Reset()
    {
        Buffer.Reset();
    }

    bool FCommandByteStream::Receive(FCommand& OutCommand)
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


    void FCommandByteStream::Send(const FCommand& command)
    {
        // TODO: move this to FCommandParser & rename as CommandByteStream or CommandProtocol?

        const core::Vector<uint8_t>& Data = command.GetData();
        const int numBytes = Data.Num();
        ensure(numBytes < 256);

        const uint8_t type = static_cast<uint8_t>(command.GetType());

        // 1 byte - type
        Serial.write(type);

        // 1 byte - payload size
        Serial.write(numBytes);

        // n bytes - payload
        Serial.write(Data.GetData(), numBytes);

        Serial.flush();
    }

    bool FCommandByteStream::IsReadyToParseCommand() const
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

    void FCommandByteStream::ParseCommandAndConsumeBuffer(FCommand& OutCommand)
    {
        const int Type = Buffer[0];
        const int CommandPayloadSize = Buffer[1];

        const int CommandSize = 2 + CommandPayloadSize;
        ensure(Buffer.Num() == CommandSize);

        OutCommand.Type = static_cast<ECommandType>(Type);
        OutCommand.Data = Buffer.Slice(2, CommandPayloadSize);

        Buffer.Reset();
    }

} // namespace command
