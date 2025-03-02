#pragma once

namespace test
{
    class FTestVector
    {
    public:
        void Run();

    private:
        void ShouldConstruct();
        void ShouldAddValue();
        void ShouldAddValues();
        void ShouldCopyConstruct();
        void ShouldAssign();
        void ShouldSetSize();
        void ShouldSetSizeThenAddElements();
    };
}
