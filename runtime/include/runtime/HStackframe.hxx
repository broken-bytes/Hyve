#pragma once

#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

namespace Hyve::Runtime {
    struct HStackframe {
        // The addresses that are in the stack frame
        std::vector<uintptr_t> Addresses;
    };
}