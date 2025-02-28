#include "CommandDecoder.h"

namespace command
{
    FCommandDecoder::FCommandDecoder(FCommand& inCommand) : Command(inCommand)
    {

    }

    bool FCommandDecoder::RegisterInput(FInput& outInput)
    {
        if (Command.GetType() != ECommandType::RegisterInput) {
            return false;
        }

        const core::Vector<uint8_t>& data = Command.GetData();

        outInput.id = data[0];
        outInput.pin = data[1];
        outInput.type = static_cast<EInputType>(data[2]);
        outInput.label = data.Slice(3, data.Num() - 3);

        return true;
    }

    bool FCommandDecoder::InputValue(int& outId, int& outValue)
    {
        if (Command.GetType() != ECommandType::InputValue) {
            return false;
        }

        const core::Vector<uint8_t>& data = Command.GetData();
        outId = data[0];
        outValue = data[1];

        return true;
    }

    bool FCommandDecoder::Message(core::String& outMessage)
    {
        if (Command.GetType() != ECommandType::Message) {
            return false;
        }

        const core::Vector<uint8_t>& data = Command.GetData();
        outMessage = data.Slice(0, data.Num());

        return true;
    }
}
