#include "Test.h"

#include "core/Vector.h"
#include "core/String.h"

test(Vector, ShouldConstruct)
{
    core::Vector<uint8_t> vector;
    assertEqual(vector.Num(), 0);
    assertEqual(vector.GetData(), nullptr);
}

test(Vector, ShouldAddValue)
{
    core::Vector<uint8_t> vector;
    
    vector.Add(11);
    assertEqual(vector.Num(), 1);
    assertEqual(vector[0], 11);

    vector.Add(22);
    assertEqual(vector.Num(), 2);
    assertEqual(vector[0], 11);
    assertEqual(vector[1], 22);

    vector.Add(33);
    vector.Add(44);
    assertEqual(vector.Num(), 4);
    assertEqual(vector[0], 11);
    assertEqual(vector[1], 22);
    assertEqual(vector[2], 33);
    assertEqual(vector[3], 44);

    vector.Add(55);
    assertEqual(vector.Num(), 5);
    assertEqual(vector[0], 11);
    assertEqual(vector[1], 22);
    assertEqual(vector[2], 33);
    assertEqual(vector[3], 44);
    assertEqual(vector[4], 55);
}

test(Vector, ShouldAddValues)
{
    core::Vector<uint8_t> vector;
    
    vector.Add(11);
    vector.Add(22);
    vector.Add(33);
    vector.Add(44);
    vector.Add(55);

    const uint8_t kValues[] = {1,2,3,4,5,6,7,8};
    vector.Add(kValues, 8);
    assertEqual(vector.Num(), 13);
    assertEqual(vector[0], 11);
    assertEqual(vector[1], 22);
    assertEqual(vector[2], 33);
    assertEqual(vector[3], 44);
    assertEqual(vector[4], 55);
    assertEqual(vector[5], 1);
    assertEqual(vector[6], 2);
    assertEqual(vector[7], 3);
    assertEqual(vector[8], 4);
    assertEqual(vector[9], 5);
    assertEqual(vector[10], 6);
    assertEqual(vector[11], 7);
    assertEqual(vector[12], 8);
}

test(Vector, ShouldCopyConstruct)
{
    core::Vector<uint8_t> vector;
    const uint8_t kValues[] = {8,7,6,5,4,3};
    vector.Add(kValues, 6);

    core::Vector<uint8_t> vector2(vector);
    assertEqual(vector2.Num(), 6);
    assertEqual(vector2[0], 8);
    assertEqual(vector2[1], 7);
    assertEqual(vector2[2], 6);
    assertEqual(vector2[3], 5);
    assertEqual(vector2[4], 4);
    assertEqual(vector2[5], 3);
}

test(Vector, ShouldAssign)
{
    core::Vector<uint8_t> vector;
    const uint8_t kValues[] = {8,7,6,5,4};
    vector.Add(kValues, 5);

    core::Vector<uint8_t> vector2;
    vector2 = vector;
    assertEqual(vector2.Num(), 5);
    assertEqual(vector2[0], 8);
    assertEqual(vector2[1], 7);
    assertEqual(vector2[2], 6);
    assertEqual(vector2[3], 5);
    assertEqual(vector2[4], 4);
}

test(Vector, ShouldSetSize)
{
    core::Vector<char> vector;
    vector.SetSize(32);
    assertEqual(vector.Num(), 0);
    assertNotEqual(vector.GetData(), static_cast<char*>(nullptr));
}

test(Vector, ShouldSetSizeThenAddElements)
{
    const core::String message("my test message");
    const int Length = message.Length();
    
    core::Vector<char> vector;
    vector.SetSize(Length);
    vector.Add(message.c_str(), Length);
}

test(Vector, ShouldSetSmallerSize)
{
    core::Vector<char> vector;
    vector.SetSize(32);
    vector.Add('a');
    vector.SetSize(0);
    assertEqual(vector.Num(), 0);
}

test(Vector, ShouldSetLargerSize)
{
    core::Vector<char> vector;
    vector.SetSize(32);
    vector.Add('a');
    vector.SetSize(64);
    assertEqual(vector.Num(), 0);
}

test(Vector, ShouldSetSameSize)
{
    core::Vector<char> vector;
    vector.SetSize(32);
    vector.Add('a');
    vector.SetSize(32);
    assertEqual(vector.Num(), 0);
}
