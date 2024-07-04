#pragma once

#include <string>

namespace Hyve {
    enum class HCompilerArgumentType {
        MODULE,
        DRY_RUN,
        WARNINGS
    };

    struct HCompilerArgument {
        HCompilerArgumentType Type;
        std::string Value;
    };
}