#include "TestString.h"

#include "core/String.h"

namespace test
{
    void FTestString::Run()
    {
        ShouldConstruct();
        ShouldConstructFromRawString();
        ShouldCopyConstruct();
        ShouldAssignRawString();
    }

    void FTestString::ShouldConstruct()
    {
        const core::String string;
        ensureEq(string.Length(), 0);
        ensureEq(string[0], 0);
    }

    void FTestString::ShouldConstructFromRawString()
    {
        const core::String string("hello");
        ensureEq(string.Length(), 5);
        ensureCharEq(string[0], 'h');
        ensureCharEq(string[1], 'e');
        ensureCharEq(string[2], 'l');
        ensureCharEq(string[3], 'l');
        ensureCharEq(string[4], 'o');
        ensureCharEq(string[5], 0);
    }

    void FTestString::ShouldCopyConstruct()
    {
        const core::String string("hello");
        const core::String stringCopy(string);

        ensureEq(stringCopy.Length(), 5);
        ensureCharEq(stringCopy[0], 'h');
        ensureCharEq(stringCopy[1], 'e');
        ensureCharEq(stringCopy[2], 'l');
        ensureCharEq(stringCopy[3], 'l');
        ensureCharEq(stringCopy[4], 'o');
        ensureCharEq(stringCopy[5], 0);
    }

    void FTestString::ShouldAssignRawString()
    {
        core::String string;

        string = "hello";
        ensureEq(string.Length(), 5);
        ensureCharEq(string[0], 'h');
        ensureCharEq(string[1], 'e');
        ensureCharEq(string[2], 'l');
        ensureCharEq(string[3], 'l');
        ensureCharEq(string[4], 'o');
        ensureCharEq(string[5], 0);
    }

}