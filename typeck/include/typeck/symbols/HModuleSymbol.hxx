#pragma once

#include "typeck/HSymbol.hxx"
#include <string>

namespace Hyve::Typeck {
    class HModuleSymbol : public HSymbol {
        std::string Name;
    };
}