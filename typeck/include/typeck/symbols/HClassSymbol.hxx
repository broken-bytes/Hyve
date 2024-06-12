#pragma once

#include "typeck/HSymbol.hxx"
#include "typeck/HSymbolType.hxx"

namespace Hyve::Typeck {
    struct HClassSymbol : public HSymbol {
        HClassSymbol() {
            SymbolType = HSymbolType::Class;
        }
    };
}