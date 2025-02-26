#pragma once

namespace core
{
    template <typename T>
    struct Slice
    {
        T* Data;
        int Start;
        int Length;

        inline T& operator[](int index) {
            return Data[Start + index];
        }
    };
}
