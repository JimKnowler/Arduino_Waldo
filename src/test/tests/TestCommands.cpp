#include "TestCommands.h"

#include "command/CommandParser.h"
#include "core/Ensure.h"
#include "input/Input.h"

namespace test 
{
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
        const FCommand reset = FCommand().Reset();
        ensure(reset.GetType() == CommandType::Reset);
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

        const FCommand registerInputDigital = FCommand().RegisterInput(inputDigital);
        ensure(registerInputDigital.GetType() == CommandType::RegisterInput);
        ensure(registerInputDigital.GetData().Num() == 19);
        // TODO: test inputs to command match the output of command parser

        const FInput inputAnalog = FInput{
            .label = "my analog input",
            .pin = 73,
            .id = 34,
            .type = EInputType::Analog
        };

        const FCommand registerInputAnalog = FCommand().RegisterInput(inputAnalog);
        ensure(registerInputAnalog.GetType() == CommandType::RegisterInput);
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

        const FCommand inputValueDigital = FCommand().InputValue(inputDigital, 1);
        ensure(inputValueDigital.GetType() == CommandType::InputValue);
        ensure(inputValueDigital.GetData().Num() == 2);
        // TODO: test inputs to command match the output of command parser

        const FInput inputAnalog = FInput{
            .label = "my analog input",
            .pin = 73,
            .id = 34,
            .type = EInputType::Analog
        };

        const FCommand inputValueAnalog = FCommand().InputValue(inputAnalog, 1023);
        ensure(inputValueAnalog.GetType() == CommandType::InputValue);
        ensure(inputValueAnalog.GetData().Num() == 2);
        // TODO: test inputs to command match the output of command parser
    }

    void FTestCommands::ShouldImplementCommandStartFrame()
    {
        const FCommand startFrame = FCommand().StartFrame();
        ensureCharEq(startFrame.GetType(), CommandType::StartFrame);
        ensureEq(startFrame.GetData().Num(), 0);
    }

    void FTestCommands::ShouldImplementCommandEndFrame()
    {
        const FCommand endFrame = FCommand().EndFrame();
        ensureCharEq(endFrame.GetType(), CommandType::EndFrame);
        ensureEq(endFrame.GetData().Num(), 0);
    }

    void FTestCommands::ShouldImplementCommandMessage()
    {
        const core::String strMessage("My Test Message");
        const FCommand message = FCommand().Message(strMessage);
        ensureCharEq(message.GetType(), CommandType::Message);
        ensureEq(message.GetData().Num(), strMessage.Length());
        // TODO: test inputs to command match the output of command parser
    }
}
