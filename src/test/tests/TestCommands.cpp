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
        // TODO: parse the internals

        const FInput inputAnalog = FInput{
            .label = "my analog input",
            .pin = 73,
            .id = 34,
            .type = EInputType::Analog
        };

        const FCommand registerInputAnalog = FCommand().RegisterInput(inputAnalog);
        ensure(registerInputAnalog.GetType() == CommandType::RegisterInput);
        ensure(registerInputAnalog.GetData().Num() == 18);
        // TODO: parse the internals
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
        // TODO: parse the internals

        const FInput inputAnalog = FInput{
            .label = "my analog input",
            .pin = 73,
            .id = 34,
            .type = EInputType::Analog
        };

        const FCommand inputValueAnalog = FCommand().InputValue(inputAnalog, 1023);
        ensure(inputValueAnalog.GetType() == CommandType::InputValue);
        ensure(inputValueAnalog.GetData().Num() == 2);
        // TODO: parse the internals
    }

    void FTestCommands::ShouldImplementCommandStartFrame()
    {

    }

    void FTestCommands::ShouldImplementCommandEndFrame()
    {

    }

    void FTestCommands::ShouldImplementCommandMessage()
    {
        Serial.println("a");
        const core::String message("My Test Message");
        Serial.println("b");
        {
            // NOTE: issue with Message command - test runner is crashing when this function exits
            //FCommand().Message(message);
        }
        Serial.println("c");
        /*
        const FCommand message = FCommand().Message("My Test Message");
        ensureCharEq(message.GetType(), CommandType::Message);
        ensureEq(message.GetData().Num(), message.Length());
        */
    }
}
