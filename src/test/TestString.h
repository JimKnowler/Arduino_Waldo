#pragma once

namespace test
{
    class FTestString
    {
    public:
        void Run();

    private:
        void ShouldConstruct();
        void ShouldConstructFromRawString();
        void ShouldCopyConstruct();
        void ShouldAssignRawString();
    };
}