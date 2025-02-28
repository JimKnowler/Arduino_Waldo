#pragma once

namespace core
{
    template <typename T>
    T Max(const T& a, const T& b) {
        return (a > b) ? a : b;
    }
}