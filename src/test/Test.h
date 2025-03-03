#pragma once

#include <AUnit.h>
using namespace aunit;

// Extend AUnit to support specific typings
#define assertEqualChar(_a, _b) assertEqual(static_cast<char>(_a), static_cast<char>(_b))
#define assertEqualStr(_a, _b) assertEqual((_a).c_str(), (_b).c_str())
