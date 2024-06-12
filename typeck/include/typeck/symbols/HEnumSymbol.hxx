#pragma once

#include "typeck/HSymbol.hxx"
#include "typeck/HSymbolType.hxx"

namespace Hyve::Typeck {
    struct HEnumSymbol : public HSymbol {
        HEnumSymbol() {
            SymbolType = HSymbolType::Enum;
        }
    };
}