#pragma once

#include "runtime/HObject.hxx"
#include <string>

namespace Hyve::Runtime {
    struct HVariable {
        HObject* Parent;
        std::string Name;
        HObject* Value;
    };
}