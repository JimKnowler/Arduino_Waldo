#pragma once

namespace test {
    class FTestCommands
    {
    public:
        void Run();

    private:
        void ShouldImplementCommandReset();
        void ShouldImplementCommandRegisterInput();
        void ShouldImplementCommandInputValue();
        void ShouldImplementCommandStartFrame();
        void ShouldImplementCommandEndFrame();
        void ShouldImplementCommandMessage();
    };
}
