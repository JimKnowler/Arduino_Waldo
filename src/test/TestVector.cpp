#include "Test.h"

#if ENABLE_WALDO_TESTS

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

test(Vector, ShouldReset)
{
    core::Vector<char> vector;
    vector.Reset(32);
    assertEqual(vector.Num(), 0);
    assertNotEqual(vector.GetData(), static_cast<char*>(nullptr));
}

test(Vector, ShouldResetThenAddElements)
{
    const core::String message("my test message");
    const int Length = message.Length();
    
    core::Vector<char> vector;
    vector.Reset(Length);
    vector.Add(message.c_str(), Length);
}

test(Vector, ShouldResetWithSmallerSize)
{
    core::Vector<char> vector;
    vector.Reset(32);
    vector.Add('a');
    vector.Reset(0);
    assertEqual(vector.Num(), 0);
}

test(Vector, ShouldResetWithLargerSize)
{
    core::Vector<char> vector;
    vector.Reset(32);
    vector.Add('a');
    vector.Reset(64);
    assertEqual(vector.Num(), 0);
}

test(Vector, ShouldResetWithSameSize)
{
    core::Vector<char> vector;
    vector.Reset(32);
    vector.Add('a');
    vector.Reset(32);
    assertEqual(vector.Num(), 0);
}

namespace
{
    struct FMyType {
        static int ConstructorCount;
        static int DestructorCount;
        static int AssignmentCount;
        
        FMyType(int id = 0) {
            ConstructorCount += 1;
            Id = id;
        }

        ~FMyType() {
            DestructorCount += 1;
        }

        FMyType& operator=(const FMyType& Other) {
            AssignmentCount += 1;
        }

        static void Reset() {
            ConstructorCount = 0;
            DestructorCount = 0;
            AssignmentCount = 0;
        }

        int Id;
    };

    int FMyType::ConstructorCount = 0;
    int FMyType::DestructorCount = 0;
    int FMyType::AssignmentCount = 0;
}

test(Vector, ShouldDestructElementsWhenReset)
{
    FMyType::Reset();
    core::Vector<FMyType> vector;
    assertEqual(FMyType::ConstructorCount, 0);
    assertEqual(FMyType::AssignmentCount, 0);
    assertEqual(FMyType::DestructorCount, 0);

    FMyType::Reset();
    vector.Reset(32);
    assertEqual(FMyType::ConstructorCount, 0);
    assertEqual(FMyType::AssignmentCount, 0);
    assertEqual(FMyType::DestructorCount, 0);

    FMyType element;
    FMyType::Reset();
    vector.Add(element);
    assertEqual(FMyType::ConstructorCount, 0);
    assertEqual(FMyType::AssignmentCount, 1);       // to copy element into place
    assertEqual(FMyType::DestructorCount, 0);

    FMyType::Reset();
    vector.Reset(0);
    assertEqual(FMyType::ConstructorCount, 0);
    assertEqual(FMyType::AssignmentCount, 0);
    assertEqual(FMyType::DestructorCount, 1);       // destruct element in vector
}

test(Vector, ShouldDestructElementsWhenResized)
{
    core::Vector<FMyType> vector;
    vector.Add(FMyType());
    vector.Add(FMyType());

    FMyType::Reset();
    vector.Resize(128);
    assertEqual(FMyType::ConstructorCount, 0);
    assertEqual(FMyType::AssignmentCount, 2);       // copy across 2 elements
    assertEqual(FMyType::DestructorCount, 2);       // destroy 2 old elements
}

test(Vector, ShouldUseAssignmentWhenCopyingAnotherVector)
{
    core::Vector<FMyType> vector;
    vector.Add(FMyType());
    vector.Add(FMyType());

    core::Vector<FMyType> vector2;
    FMyType::Reset();
    vector2 = vector;

    assertEqual(FMyType::ConstructorCount, 0);
    assertEqual(FMyType::AssignmentCount, 2);       // copy across 2 elements
    assertEqual(FMyType::DestructorCount, 0);
}

test(Vector, ShouldUseAssignmentWhenAddingAnElement)
{
    core::Vector<FMyType> vector;
    FMyType element;
    FMyType::Reset();

    vector.Add(element);
    
    assertEqual(FMyType::ConstructorCount, 0);
    assertEqual(FMyType::AssignmentCount, 1);
    assertEqual(FMyType::DestructorCount, 0);
}

test(Vector, ShouldUseAssignmentWhenAddingMultipleElements)
{
    core::Vector<FMyType> vector;
    const int kArraySize = 5;
    FMyType array[kArraySize];
    FMyType::Reset();

    vector.Add(array, kArraySize);
    
    assertEqual(FMyType::ConstructorCount, 0);
    assertEqual(FMyType::AssignmentCount, kArraySize);
    assertEqual(FMyType::DestructorCount, 0);
}

test(Vector, ShouldRemoveElement)
{
    core::Vector<int> vector;
    vector.Add(1);
    vector.Add(2);
    vector.Add(3);

    vector.RemoveAt(1);
    
    assertEqual(vector.Num(), 2);
    assertEqual(vector[0], 1);
    assertEqual(vector[1], 3);
}

test(Vector, ShouldUseDestructorWhenRemovingElement)
{
    core::Vector<FMyType> vector;
    vector.Add(FMyType(1));
    vector.Add(FMyType(2));
    vector.Add(FMyType(3));

    FMyType::Reset();

    vector.RemoveAt(0);
    assertEqual(FMyType::ConstructorCount, 0);
    assertEqual(FMyType::AssignmentCount, 2);       // copy down elements from indexes 1,2 to 0,1
    assertEqual(FMyType::DestructorCount, 1);

    FMyType::Reset();
    vector.RemoveAt(1);
    assertEqual(FMyType::ConstructorCount, 0);
    assertEqual(FMyType::AssignmentCount, 0);
    assertEqual(FMyType::DestructorCount, 1);
}

namespace
{
    /**
     * @brief a struct that allocates memory in constuctor, and frees it in destructor
     * 
     */
    struct FMyComplexType
    {
        const int kDataSize = 16;

        FMyComplexType() {
            Data = malloc(kDataSize);
        }

        ~FMyComplexType() {
            free(Data);
        }

        FMyComplexType& operator=(const FMyComplexType& Other)
        {
            // NOTE: assignment operator is required to prevent
            //       class from just copying the 'Data' pointer,
            //       which would lead to double-free crash

            Data = malloc(kDataSize);
            memcpy(Data, Other.Data, kDataSize);

            return *this;
        }

        void* Data;
    };
}

test(Vector, ShouldWorkWithComplexTypes)
{
    core::Vector<FMyComplexType> vector;
    vector.Add(FMyComplexType());
    vector.Add(FMyComplexType());
    vector.Add(FMyComplexType());
    vector.Add(FMyComplexType());
    vector.Reset(16);
    vector.Add(FMyComplexType());
}

#endif
