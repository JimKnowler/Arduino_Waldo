#pragma once

#include "core/String.h"

#include "InputType.h"

struct FInput {
    core::String label;
    int pin;
    int id;
    EInputType type;
};
