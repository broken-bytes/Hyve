#pragma once

#include <string>
#include <vector>

namespace Hyve::Runtime {
    struct HStackframe {
        std::string FunctionName; // Name of the function in this frame
        uintptr_t InstructionPointer; // Address of the instruction being executed
        std::vector<uintptr_t> LocalVariables; // Addresses of local variables
        std::vector<uintptr_t> Stack; // Addresses of stack variables
        std::vector<uintptr_t> Arguments; // Addresses of arguments
    };
}