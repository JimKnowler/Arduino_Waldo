#include "CommandEncoder.h"

namespace command
{
    FCommandEncoder::FCommandEncoder(FCommand& inCommand) : Command(inCommand)
    {

    }
    
    FCommand& FCommandEncoder::Reset()
    {
        Command.Type = ECommandType::Reset;
        Command.Data.SetSize(0);

        return Command;
    }

    FCommand& FCommandEncoder::RegisterInput(const FInput& input)
    {
        Command.Type = ECommandType::RegisterInput;

        const int labelLength = input.label.Length();

        Command.Data.SetSize(3 + labelLength);
        Command.Data.Add(input.id);
        Command.Data.Add(input.pin);
        Command.Data.Add(static_cast<int>(input.type));
        Command.Data.Add(input.label.c_str(), input.label.Length());

        return Command;
    }

    FCommand& FCommandEncoder::InputValue(const FInput& input, const int value)
    {
        Command.Type = ECommandType::InputValue;

        // TODO: use uint8 for id, and add ensure/guards at the moment where we allocate a new id
        ensure(input.id >= 0);
        ensure(input.id < 256);

        ensure(value >= 0);

        int mappedValue;

        switch (input.type)
        {
            case EInputType::Analog:
            {
                // TODO: support multi-byte values
                // TODO: support configuring active range of an analog input
                ensure(value < 1024);
                mappedValue = value / 4;
                break;
            }
            case EInputType::Digital:
            default:
            {
                ensure(value <= 1);
                mappedValue = value;
                break;
            }
        }

        Command.Data.SetSize(2);
        Command.Data.Add(input.id);
        Command.Data.Add(mappedValue);

        return Command;
    }

    FCommand& FCommandEncoder::StartFrame()
    {
        Command.Type = ECommandType::StartFrame;
        Command.Data.SetSize(0);

        return Command;
    }

    FCommand& FCommandEncoder::EndFrame()
    {
        Command.Type = ECommandType::EndFrame;
        Command.Data.SetSize(0);

        return Command;
    }

    FCommand& FCommandEncoder::Message(const core::String& message)
    {
        Command.Type = ECommandType::Message;

        const int Length = message.Length();
        Command.Data.SetSize(Length);
        Command.Data.Add(message.c_str(), Length);

        return Command;
    }

    FCommand& FCommandEncoder::AcknowledgeReset()
    {
        Command.Type = ECommandType::AcknowledgeReset;
        Command.Data.SetSize(0);

        return Command;
    }

    FCommand& FCommandEncoder::AcknowledgeFrame()
    {
        Command.Type = ECommandType::AcknowledgeFrame;
        Command.Data.SetSize(0);

        return Command;
    }
}
