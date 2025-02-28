#include "TestRunner.h"

#include <Arduino.h>

#include "tests/TestCommands.h"
#include "tests/TestString.h"
#include "tests/TestVector.h"

namespace test
{
    void FTestRunner::Run() {
        Serial.begin(500000);

        Serial.println(">>>>>> TestRunner: begin");
        Serial.println(".........................");
        Serial.flush();

        TestCommands();
        TestString();
        TestVector();

        Serial.println("<<<<<< TestRunner: finish");
        Serial.println(".........................");
        Serial.flush();

        exit(0);
    }

    void FTestRunner::TestCommands() {
        FTestCommands test;
        test.Run();
    }

    void FTestRunner::TestString() {
        FTestString test;
        test.Run();
    }

    void FTestRunner::TestVector() {
        FTestVector test;
        test.Run();
    }
}
