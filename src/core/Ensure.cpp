#include "core/Ensure.h"

#include "core/String.h"

namespace core
{
    bool Ensure(bool condition, const char* label, const char* function, const char* file, const int line) {
        if (condition) {
            return true;
        }
        
        Serial.print("ensure failed [");
        Serial.print(label);
        Serial.println("]");

        Serial.print("--> in function [");
        Serial.print(function);
        Serial.print("]");
        Serial.print(" in file [");
        Serial.print(file);
        Serial.print("] at line [");
        Serial.print(line);
        Serial.println("]");

        return false;
    }

    bool EnsureEq(int actual, int expected, const char* labelActual, const char* labelExpected, const char* function, const char* file, const int line) {
        if (actual == expected) {
            return true;
        }
        
        Serial.print("ensureEq failed: actual[");
        Serial.print(labelActual);
        Serial.print("] != expected[");
        Serial.print(labelExpected);
        Serial.println("]");

        Serial.print("--> ");
        Serial.print(actual, DEC);
        Serial.print(" != ");
        Serial.print(expected, DEC);
        Serial.println("]");

        Serial.print("--> in function [");
        Serial.print(function);
        Serial.print("] in file [");
        Serial.print(file);
        Serial.print("] at line [");
        Serial.print(line);
        Serial.println("]");

        return false;
    }

    bool EnsureCharEq(char actual, char expected, const char* labelActual, const char* labelExpected, const char* function, const char* file, const int line) {
        if (actual == expected) {
            return true;
        }
        
        Serial.print("ensureCharEq failed: actual[");
        Serial.print(labelActual);
        Serial.print("] != expected[");
        Serial.print(labelExpected);
        Serial.println("]");

        Serial.print("--> [");
        char buffer[2];
        buffer[1] = 0;
        buffer[0] = actual;
        Serial.print(buffer);
        Serial.print("] != [");
        buffer[0] = expected;
        Serial.print(buffer);
        Serial.println("]");

        Serial.print("--> in function [");
        Serial.print(function);
        Serial.print("] in file [");
        Serial.print(file);
        Serial.print("] at line [");
        Serial.print(line);
        Serial.println("]");

        return false;
    }

    bool EnsureStrEq(const core::String& actual, const core::String& expected, const char* labelActual, const char* labelExpected, const char* function, const char* file, const int line)
    {
        if (actual == expected) {
            return true;
        }
        
        Serial.print("ensureStrEq failed: actual[");
        Serial.print(labelActual);
        Serial.print("] != expected[");
        Serial.print(labelExpected);
        Serial.println("]");

        Serial.print("--> [");
        Serial.print(actual.c_str());
        Serial.print("] != [");
        Serial.print(expected.c_str());
        Serial.println("]");

        Serial.print("--> in function [");
        Serial.print(function);
        Serial.print("] in file [");
        Serial.print(file);
        Serial.print("] at line [");
        Serial.print(line);
        Serial.println("]");

        return false;
    }
}
