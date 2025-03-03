#include "command/CommandEncoder.h"
#include "command/CommandDecoder.h"
#include "core/Ensure.h"
#include "input/Input.h"
#include "Test.h"

using command::FCommandDecoder;
using command::FCommandEncoder;
using command::FCommand;
using command::ECommandType;

test(Command, ShouldImplementCommandReset)
{
    FCommand reset;
    FCommandEncoder(reset).Reset();
    assertEqualChar(reset.GetType(), ECommandType::Reset);
    assertEqual(reset.GetData().Num(), 0);
}

test(Command, ShouldImplementCommandRegisterInputDigital)
{
    const FInput kInputDigital = FInput{
        .label = "my digital input",
        .pin = 73,
        .id = 34,
        .type = EInputType::Digital
    };

    FCommand registerInputDigital;
    FCommandEncoder(registerInputDigital).RegisterInput(kInputDigital);
    assertEqualChar(registerInputDigital.GetType(), ECommandType::RegisterInput);
    assertEqual(registerInputDigital.GetData().Num(), 19);
    
    FCommandDecoder decoder(registerInputDigital);
    FInput inputDecoded;
    assertTrue(decoder.RegisterInput(inputDecoded));
    assertEqualStr(inputDecoded.label, kInputDigital.label);
    assertEqual(inputDecoded.pin, kInputDigital.pin);
    assertEqual(inputDecoded.id, kInputDigital.id);
    assertEqualChar(inputDecoded.type, EInputType::Digital);
}

test(Command, ShouldImplementCommandRegisterInputAnalog)
{
    const FInput kInputAnalog = FInput{
        .label = "my analog input",
        .pin = 73,
        .id = 34,
        .type = EInputType::Analog
    };

    FCommand registerInputAnalog;
    FCommandEncoder(registerInputAnalog).RegisterInput(kInputAnalog);
    assertEqualChar(registerInputAnalog.GetType(), ECommandType::RegisterInput);
    assertEqual(registerInputAnalog.GetData().Num(), 18);

    FCommandDecoder decoder(registerInputAnalog);
    FInput inputDecoded;
    assertTrue(decoder.RegisterInput(inputDecoded));
    assertEqualStr(inputDecoded.label, kInputAnalog.label);
    assertEqual(inputDecoded.pin, kInputAnalog.pin);
    assertEqual(inputDecoded.id, kInputAnalog.id);
    assertEqualChar(inputDecoded.type, EInputType::Analog);
}

test(Command, ShouldImplementCommandInputValueDigital)
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
    assertEqualChar(inputValueDigital.GetType(), ECommandType::InputValue);
    assertEqual(inputValueDigital.GetData().Num(), 2);
    
    FCommandDecoder decoder(inputValueDigital);
    int id = -1;
    int value = -1;
    assertTrue(decoder.InputValue(id, value));
    ensureEq(id, kInputDigital.id);
    ensureEq(value, kValue);
}

test(Command, ShouldImplementCommandInputValueAnalog)
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
    assertEqualChar(inputValueAnalog.GetType(), ECommandType::InputValue);
    assertEqual(inputValueAnalog.GetData().Num(), 2);
    
    FCommandDecoder decoder(inputValueAnalog);
    int id = -1;
    int value = -1;
    assertTrue(decoder.InputValue(id, value));
    assertEqual(id, kInputAnalog.id);
    const int kMappedValue = kValue / 4;
    assertEqual(value, kMappedValue);
}

test(Command, ShouldImplementCommandStartFrame)
{
    FCommand startFrame;
    FCommandEncoder(startFrame).StartFrame();
    assertEqualChar(startFrame.GetType(), ECommandType::StartFrame);
    assertEqual(startFrame.GetData().Num(), 0);
}

test(Command, ShouldImplementCommandEndFrame)
{
    FCommand endFrame;
    FCommandEncoder(endFrame).EndFrame();
    assertEqualChar(endFrame.GetType(), ECommandType::EndFrame);
    assertEqual(endFrame.GetData().Num(), 0);
}

test(Command, ShouldImplementCommandMessage)
{
    const core::String strMessage("My Test Message");
    FCommand message;
    FCommandEncoder(message).Message(strMessage);
    assertEqualChar(message.GetType(), ECommandType::Message);
    assertEqual(message.GetData().Num(), strMessage.Length());
    
    FCommandDecoder decoder(message);
    core::String strMessageDecoded;
    assertTrue(decoder.Message(strMessageDecoded));
    assertEqualStr(strMessageDecoded, strMessage);
}
