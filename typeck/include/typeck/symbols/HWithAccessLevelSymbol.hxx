#pragma once

#include "typeck/HSymbol.hxx"
#include "typeck/HType.hxx"
#include <core/HAccessLevel.hxx>
#include <memory>

namespace Hyve::Typeck {
    struct HWithAccessLevelSymbol : public HSymbol {
    public:
        Core::HAccessLevel AccessLevel;
    };
}