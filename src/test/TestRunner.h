#pragma once

namespace test
{
    class FTestRunner
    {
    public:
        /**
         * @brief run all test cases
         */
        void Run();

    private:
        void TestCommands();
        void TestString();
        void TestVector();
    };
}
