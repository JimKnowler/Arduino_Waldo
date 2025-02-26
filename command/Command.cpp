#include "Command.h"

CommandType Command::GetType() const 
{
    return Type;
}

const core::Vector<uint8_t>& Command::GetData() const
{
    return Data;
}

void Command::SetReset()
{
    Type = CommandType::Reset;
    Data.SetSize(0);
}

void Command::SetResetAcknowledge()
{
    Type = CommandType::ResetAcknowledge;
    Data.SetSize(0);
}

void Command::SetRegisterInput(const Input& input)
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
}

void Command::SetInputValue(const Input& input, int value)
{
    Type = CommandType::InputValue;

    ensure(input.id >= 0);
    ensure(input.id < 256);

    ensure(value >= 0);
    ensure(value < 256);

    Data.SetSize(2);
    Data.Add(input.id);
    Data.Add(value);
}
