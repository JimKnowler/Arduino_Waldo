#include "Test.h"

#include "core/String.h"


test(String, ShouldConstruct)
{
    const core::String string;
    assertEqual(string.Length(), 0);
    assertEqualChar(string[0], 0);
}

test(String, ShouldConstructFromRawString)
{
    const core::String string("hello");
    assertEqual(string.Length(), 5);
    assertEqualChar(string[0], 'h');
    assertEqualChar(string[1], 'e');
    assertEqualChar(string[2], 'l');
    assertEqualChar(string[3], 'l');
    assertEqualChar(string[4], 'o');
    assertEqualChar(string[5], 0);
}

test(String, ShouldCopyConstruct)
{
    const core::String string("hello");
    const core::String stringCopy(string);

    assertEqual(stringCopy.Length(), 5);
    assertEqualChar(stringCopy[0], 'h');
    assertEqualChar(stringCopy[1], 'e');
    assertEqualChar(stringCopy[2], 'l');
    assertEqualChar(stringCopy[3], 'l');
    assertEqualChar(stringCopy[4], 'o');
    assertEqualChar(stringCopy[5], 0);
}

test(String, ShouldAssignRawString)
{
    core::String string;

    string = "hello";
    assertEqual(string.Length(), 5);
    assertEqualChar(string[0], 'h');
    assertEqualChar(string[1], 'e');
    assertEqualChar(string[2], 'l');
    assertEqualChar(string[3], 'l');
    assertEqualChar(string[4], 'o');
    assertEqualChar(string[5], 0);
}
