#pragma once

#if defined(ARDUINO_API_VERSION)
// AUnit doesn't support new Arduino API
# define ENABLE_WALDO_TESTS 0
#endif

#if ENABLE_WALDO_TESTS

#include <AUnit.h>
using namespace aunit;

// Extend AUnit to support specific typings
#define assertEqualChar(_a, _b) assertEqual(static_cast<char>(_a), static_cast<char>(_b))
#define assertEqualStr(_a, _b) assertEqual((_a).c_str(), (_b).c_str())

#endif 