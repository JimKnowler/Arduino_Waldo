#pragma once

#include <assert.h>

/**
 * @brief lightweight implementation of Ensure() for Waldo project
 * 
 */

#define ensure(_condition)  core::Ensure((_condition), #_condition)

namespace core
{
    inline bool Ensure(bool condition, const char* label) {
        if (condition) {
            return true;
        }
        
        assert(false);

        return false;
    }
}
