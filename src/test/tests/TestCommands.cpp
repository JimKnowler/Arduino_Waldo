#include "TestCommands.h"

#include "command/CommandEncoder.h"
#include "core/Ensure.h"
#include "input/Input.h"

namespace test 
{
    using command::FCommandEncoder;
    using command::FCommand;
    using command::ECommandType;

    void FTestCommands::Run()
    {
        ShouldImplementCommandReset();
        ShouldImplementCommandRegisterInput();
        ShouldImplementCommandInputValue();
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

    void FTestCommands::ShouldImplementCommandRegisterInput()
    {
        const FInput inputDigital = FInput{
            .label = "my digital input",
            .pin = 73,
            .id = 34,
            .type = EInputType::Digital
        };

        FCommand registerInputDigital;
        FCommandEncoder(registerInputDigital).RegisterInput(inputDigital);
        ensure(registerInputDigital.GetType() == ECommandType::RegisterInput);
        ensure(registerInputDigital.GetData().Num() == 19);
        // TODO: test inputs to command match the output of command parser

        const FInput inputAnalog = FInput{
            .label = "my analog input",
            .pin = 73,
            .id = 34,
            .type = EInputType::Analog
        };

        FCommand registerInputAnalog;
        FCommandEncoder(registerInputAnalog).RegisterInput(inputAnalog);
        ensure(registerInputAnalog.GetType() == ECommandType::RegisterInput);
        ensure(registerInputAnalog.GetData().Num() == 18);
        // TODO: test inputs to command match the output of command parser
    }

    void FTestCommands::ShouldImplementCommandInputValue()
    {
        const FInput inputDigital = FInput{
            .label = "my digital input",
            .pin = 73,
            .id = 34,
            .type = EInputType::Digital
        };

        FCommand inputValueDigital;
        FCommandEncoder(inputValueDigital).InputValue(inputDigital, 1);
        ensure(inputValueDigital.GetType() == ECommandType::InputValue);
        ensure(inputValueDigital.GetData().Num() == 2);
        // TODO: test inputs to command match the output of command parser

        const FInput inputAnalog = FInput{
            .label = "my analog input",
            .pin = 73,
            .id = 34,
            .type = EInputType::Analog
        };

        FCommand inputValueAnalog;
        FCommandEncoder(inputValueAnalog).InputValue(inputAnalog, 1023);
        ensure(inputValueAnalog.GetType() == ECommandType::InputValue);
        ensure(inputValueAnalog.GetData().Num() == 2);
        // TODO: test inputs to command match the output of command parser
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
        // TODO: test inputs to command match the output of command parser
    }
}
