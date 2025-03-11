#pragma once

#include "CommandByteStream.h"

#include <Arduino.h>

namespace command
{
    namespace
    {
        constexpr int CommandHeaderSize = 2;                // [0] = Type, [1] = Size
    }

    FCommandByteStream::FCommandByteStream()
    {
        Buffer.Reset(32);
        
        const uint8_t GuardData[] = {'W','A','L','D','O'};
        Guard.Add(GuardData, 5);
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

            SkipToGuard();

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
        const core::Vector<uint8_t>& Data = command.GetData();
        const int numBytes = Data.Num();
        ensure(numBytes < 256);

        const uint8_t type = static_cast<uint8_t>(command.GetType());

        // 5 bytes - Guard
        Serial.write(Guard.GetData(), Guard.Num());

        // 1 byte - type
        Serial.write(type);

        // 1 byte - payload size
        Serial.write(numBytes);

        // n bytes - payload
        Serial.write(Data.GetData(), numBytes);

        // wait until data has been sent
        Serial.flush();
    }

    void FCommandByteStream::SkipToGuard()
    {
        while (!Buffer.IsEmpty())
        {
            bool bHasValidGuard = true;
            
            const int GuardSize = core::Min(Guard.Num(), Buffer.Num());
            
            for (int i=0; i<GuardSize; i++)
            {
                if (Buffer[i] != Guard[i])
                {
                    Buffer.RemoveAt(0);
                    bHasValidGuard = false;
                    break;
                }
            }

            if (bHasValidGuard)
            {
                return;
            }
        }
    }

    bool FCommandByteStream::IsReadyToParseCommand() const
    {
        const int GuardSize = Guard.Num();
        const int BufferSize = Buffer.Num();
        
        if (BufferSize < (GuardSize + CommandHeaderSize)) {
            return false;
        }

        const int CommandPayloadSize = Buffer[GuardSize + 1];
        const int CommandSize = GuardSize + CommandHeaderSize + CommandPayloadSize;
        if (BufferSize < CommandSize) 
        {
            return false;
        }
        
        ensure(BufferSize == CommandSize);

        return true;
    }

    void FCommandByteStream::ParseCommandAndConsumeBuffer(FCommand& OutCommand)
    {
        const int GuardSize = Guard.Num();
    
        const int Type = Buffer[GuardSize + 0];
        const int CommandPayloadSize = Buffer[GuardSize + 1];

        const int CommandSize = GuardSize + CommandHeaderSize + CommandPayloadSize;
        ensure(Buffer.Num() == CommandSize);

        OutCommand.Type = static_cast<ECommandType>(Type);
        OutCommand.Data.Reset();
        OutCommand.Data.Add(Buffer.GetData() + GuardSize + CommandHeaderSize, CommandPayloadSize);

        Buffer.Reset();
    }

} // namespace command
