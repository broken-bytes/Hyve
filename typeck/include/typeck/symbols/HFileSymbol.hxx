#pragma once

#include "typeck/HSymbol.hxx"
#include "typeck/HSymbolType.hxx"
#include <string>

namespace Hyve::Typeck {
    struct HFileSymbol : public HSymbol {
        HFileSymbol() {
            SymbolType = HSymbolType::File;
        }
    };
}