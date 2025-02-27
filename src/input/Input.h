#pragma once

#include "core/String.h"

#include "InputType.h"

struct Input {
    core::String label;
    int pin;
    int id;
    InputType type;
};