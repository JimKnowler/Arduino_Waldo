#include "Test.h"

#include "core/Vector.h"
#include "core/String.h"

// TODO: SetSize() after adding data - make sure that Used is reset to 0
//  - when setting a larger size
//  - when setting a smaller size
//  - when setting the same size as current

test(Vector, ShouldConstruct)
{
    core::Vector<uint8_t> vector;
    ensure(vector.Num() == 0);
    ensure(vector.GetData() == nullptr);
}

test(Vector, ShouldAddValue)
{
    core::Vector<uint8_t> vector;
    
    vector.Add(11);
    ensure(vector.Num() == 1);
    ensure(vector[0] == 11);

    vector.Add(22);
    ensure(vector.Num() == 2);
    ensure(vector[0] == 11);
    ensure(vector[1] == 22);

    vector.Add(33);
    vector.Add(44);
    ensure(vector.Num() == 4);
    ensure(vector[0] == 11);
    ensure(vector[1] == 22);
    ensure(vector[2] == 33);
    ensure(vector[3] == 44);

    vector.Add(55);
    ensure(vector.Num() == 5);
    ensure(vector[0] == 11);
    ensure(vector[1] == 22);
    ensure(vector[2] == 33);
    ensure(vector[3] == 44);
    ensure(vector[4] == 55);
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
    ensure(vector.Num() == 13);
    ensure(vector[0] == 11);
    ensure(vector[1] == 22);
    ensure(vector[2] == 33);
    ensure(vector[3] == 44);
    ensure(vector[4] == 55);
    ensure(vector[5] == 1);
    ensure(vector[6] == 2);
    ensure(vector[7] == 3);
    ensure(vector[8] == 4);
    ensure(vector[9] == 5);
    ensure(vector[10] == 6);
    ensure(vector[11] == 7);
    ensure(vector[12] == 8);
}

test(Vector, ShouldCopyConstruct)
{
    core::Vector<uint8_t> vector;
    const uint8_t kValues[] = {8,7,6,5,4,3};
    vector.Add(kValues, 6);

    core::Vector<uint8_t> vector2(vector);
    ensureEq(vector2.Num(), 6);
    ensureEq(vector2[0], 8);
    ensureEq(vector2[1], 7);
    ensureEq(vector2[2], 6);
    ensureEq(vector2[3], 5);
    ensureEq(vector2[4], 4);
    ensureEq(vector2[5], 3);
}

test(Vector, ShouldAssign)
{
    core::Vector<uint8_t> vector;
    const uint8_t kValues[] = {8,7,6,5,4};
    vector.Add(kValues, 5);

    core::Vector<uint8_t> vector2;
    vector2 = vector;
    ensureEq(vector2.Num(), 5);
    ensureEq(vector2[0], 8);
    ensureEq(vector2[1], 7);
    ensureEq(vector2[2], 6);
    ensureEq(vector2[3], 5);
    ensureEq(vector2[4], 4);
}

test(Vector, ShouldSetSize)
{
    core::Vector<char> vector;
    vector.SetSize(32);
    ensureEq(vector.Num(), 0);
    ensure(vector.GetData() != nullptr);
}

test(Vector, ShouldSetSizeThenAddElements)
{
    const core::String message("my test message");
    const int Length = message.Length();
    
    core::Vector<char> vector;
    vector.SetSize(Length);
    vector.Add(message.c_str(), Length);
}
