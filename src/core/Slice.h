#pragma once

#include "Ensure.h"

namespace core
{
    template <typename T>
    struct Slice
    {
        T* Data;
        int Start;
        int Length;

        inline T& operator[](int index) {
            ensure(index >= 0 );
            ensure(index < Length);
            return Data[Start + index];
        }
    };
}
