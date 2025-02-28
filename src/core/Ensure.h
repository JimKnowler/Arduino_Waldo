#pragma once

#include <Arduino.h>

/**
 * @brief lightweight implementation of Ensure() for Waldo project
 * 
 */

#define ensure(_condition)  core::Ensure((_condition), #_condition, __PRETTY_FUNCTION__, __FILE__, __LINE__)
#define ensureEq(_actual, _expected) core::EnsureEq(static_cast<int>(_actual), static_cast<int>(_expected), \
                                                    #_actual, #_expected, __PRETTY_FUNCTION__, __FILE__, __LINE__)

#define ensureCharEq(_actual, _expected) core::EnsureCharEq(static_cast<char>(_actual), static_cast<char>(_expected), \
                                                    #_actual, #_expected, __PRETTY_FUNCTION__, __FILE__, __LINE__)


namespace core
{
    bool Ensure(bool condition, const char* label, const char* function, const char* file, const int line);
    bool EnsureEq(int actual, int expected, const char* labelActual, const char* labelExpected, const char* function, const char* file, const int line);
    bool EnsureCharEq(char actual, char expected, const char* labelActual, const char* labelExpected, const char* function, const char* file, const int line);
}
