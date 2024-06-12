#pragma once

#include "typeck/HSymbol.hxx"
#include "typeck/HSymbolType.hxx"

namespace Hyve::Typeck {
    struct HStructSymbol : public HSymbol {
        HStructSymbol() {
            SymbolType = HSymbolType::Struct;
        }
    };
}