#pragma once

#include "typeck/HSymbol.hxx"
#include "typeck/HSymbolType.hxx"

namespace Hyve::Typeck {
    struct HContractSymbol : public HSymbol {
        HContractSymbol() {
            SymbolType = HSymbolType::Contract;
        }
    };
}