#include "TestCommands.h"

#include "command/CommandEncoder.h"
#include "command/CommandDecoder.h"
#include "core/Ensure.h"
#include "input/Input.h"

namespace test 
{
    using command::FCommandDecoder;
    using command::FCommandEncoder;
    using command::FCommand;
    using command::ECommandType;

    void FTestCommands::Run()
    {
        ShouldImplementCommandReset();
        ShouldImplementCommandRegisterInputDigital();
        ShouldImplementCommandRegisterInputAnalog();
        ShouldImplementCommandInputValueDigital();
        ShouldImplementCommandInputValueAnalog();
        ShouldImplementCommandStartFrame();
        ShouldImplementCommandEndFrame();
        ShouldImplementCommandMessage();
    }

    void FTestCommands::ShouldImplementCommandReset()
    {
        FCommand reset;
        FCommandEncoder(reset).Reset();
        ensure(reset.GetType() == ECommandType::Reset);
        ensure(reset.GetData().Num() == 0);
    }

    void FTestCommands::ShouldImplementCommandRegisterInputDigital()
    {
        const FInput kInputDigital = FInput{
            .label = "my digital input",
            .pin = 73,
            .id = 34,
            .type = EInputType::Digital
        };

        FCommand registerInputDigital;
        FCommandEncoder(registerInputDigital).RegisterInput(kInputDigital);
        ensure(registerInputDigital.GetType() == ECommandType::RegisterInput);
        ensure(registerInputDigital.GetData().Num() == 19);
        
        FCommandDecoder decoder(registerInputDigital);
        FInput inputDecoded;
        ensure(decoder.RegisterInput(inputDecoded));
        ensureStrEq(inputDecoded.label, kInputDigital.label);
        ensureEq(inputDecoded.pin, kInputDigital.pin);
        ensureEq(inputDecoded.id, kInputDigital.id);
        ensureEq(inputDecoded.type, EInputType::Digital);
    }

    void FTestCommands::ShouldImplementCommandRegisterInputAnalog()
    {
        const FInput kInputAnalog = FInput{
            .label = "my analog input",
            .pin = 73,
            .id = 34,
            .type = EInputType::Analog
        };

        FCommand registerInputAnalog;
        FCommandEncoder(registerInputAnalog).RegisterInput(kInputAnalog);
        ensure(registerInputAnalog.GetType() == ECommandType::RegisterInput);
        ensure(registerInputAnalog.GetData().Num() == 18);

        FCommandDecoder decoder(registerInputAnalog);
        FInput inputDecoded;
        ensure(decoder.RegisterInput(inputDecoded));
        ensureStrEq(inputDecoded.label, kInputAnalog.label);
        ensureEq(inputDecoded.pin, kInputAnalog.pin);
        ensureEq(inputDecoded.id, kInputAnalog.id);
        ensureEq(inputDecoded.type, EInputType::Analog);
    }

    void FTestCommands::ShouldImplementCommandInputValueDigital()
    {
        const FInput kInputDigital = FInput{
            .label = "my digital input",
            .pin = 73,
            .id = 34,
            .type = EInputType::Digital
        };
        
        const int kValue = 1;

        FCommand inputValueDigital;
        FCommandEncoder(inputValueDigital).InputValue(kInputDigital, kValue);
        ensure(inputValueDigital.GetType() == ECommandType::InputValue);
        ensure(inputValueDigital.GetData().Num() == 2);
        
        FCommandDecoder decoder(inputValueDigital);
        int id = -1;
        int value = -1;
        ensure(decoder.InputValue(id, value));
        ensureEq(id, kInputDigital.id);
        ensureEq(value, kValue);
    }

    void FTestCommands::ShouldImplementCommandInputValueAnalog()
    {
        const FInput kInputAnalog = FInput{
            .label = "my analog input",
            .pin = 74,
            .id = 35,
            .type = EInputType::Analog
        };

        const int kValue = 1021;

        FCommand inputValueAnalog;
        FCommandEncoder(inputValueAnalog).InputValue(kInputAnalog, kValue);
        ensure(inputValueAnalog.GetType() == ECommandType::InputValue);
        ensure(inputValueAnalog.GetData().Num() == 2);
        
        FCommandDecoder decoder(inputValueAnalog);
        int id = -1;
        int value = -1;
        ensure(decoder.InputValue(id, value));
        ensureEq(id, kInputAnalog.id);
        const int kMappedValue = kValue / 4;
        ensureEq(value, kMappedValue);
    }

    void FTestCommands::ShouldImplementCommandStartFrame()
    {
        FCommand startFrame;
        FCommandEncoder(startFrame).StartFrame();
        ensureCharEq(startFrame.GetType(), ECommandType::StartFrame);
        ensureEq(startFrame.GetData().Num(), 0);
    }

    void FTestCommands::ShouldImplementCommandEndFrame()
    {
        FCommand endFrame;
        FCommandEncoder(endFrame).EndFrame();
        ensureCharEq(endFrame.GetType(), ECommandType::EndFrame);
        ensureEq(endFrame.GetData().Num(), 0);
    }

    void FTestCommands::ShouldImplementCommandMessage()
    {
        const core::String strMessage("My Test Message");
        FCommand message;
        FCommandEncoder(message).Message(strMessage);
        ensureCharEq(message.GetType(), ECommandType::Message);
        ensureEq(message.GetData().Num(), strMessage.Length());
        
        FCommandDecoder decoder(message);
        core::String strMessageDecoded;
        ensure(decoder.Message(strMessageDecoded));
        ensureStrEq(strMessageDecoded, strMessage);
    }
}
