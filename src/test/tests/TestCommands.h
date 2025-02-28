#pragma once

namespace test {
    class FTestCommands
    {
    public:
        void Run();

    private:
        void ShouldImplementCommandReset();
        void ShouldImplementCommandRegisterInputDigital();
        void ShouldImplementCommandRegisterInputAnalog();
        void ShouldImplementCommandInputValueDigital();
        void ShouldImplementCommandInputValueAnalog();
        void ShouldImplementCommandStartFrame();
        void ShouldImplementCommandEndFrame();
        void ShouldImplementCommandMessage();
    };
}
