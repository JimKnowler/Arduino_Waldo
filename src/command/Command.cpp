#include "Command.h"

CommandType FCommand::GetType() const 
{
    return Type;
}

const core::Vector<uint8_t>& FCommand::GetData() const
{
    return Data;
}

FCommand& FCommand::Reset()
{
    Type = CommandType::Reset;
    Data.SetSize(0);

    return *this;
}

FCommand& FCommand::RegisterInput(const FInput& input)
{
    Type = CommandType::RegisterInput;

    const int labelLength = input.label.Length();

    Data.SetSize(3 + labelLength);
    Data.Add(input.id);
    Data.Add(static_cast<int>(input.type));
    Data.Add(labelLength);
    for (int i=0; i<labelLength; i++)
    {
        Data.Add(input.label[i]);
    }

    return *this;
}

FCommand& FCommand::InputValue(const FInput& input, const int value)
{
    Type = CommandType::InputValue;

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

    Data.SetSize(2);
    Data.Add(input.id);
    Data.Add(mappedValue);

    return *this;
}

FCommand& FCommand::StartFrame()
{
    Type = CommandType::StartFrame;
    Data.SetSize(0);

    return *this;
}

FCommand& FCommand::EndFrame()
{
    Type = CommandType::EndFrame;
    Data.SetSize(0);

    return *this;
}

FCommand& FCommand::Message(const core::String& message)
{
    Type = CommandType::Message;

    const int Length = message.Length();
    Data.SetSize(Length);
    Data.Add(message.c_str(), Length);

    return *this;
}

FCommand& FCommand::AcknowledgeReset()
{
    Type = CommandType::AcknowledgeReset;
    Data.SetSize(0);

    return *this;
}

FCommand& FCommand::AcknowledgeFrame()
{
    Type = CommandType::AcknowledgeFrame;
    Data.SetSize(0);

    return *this;
}
