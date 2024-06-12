#pragma once

#include "typeck/HSymbol.hxx"
#include "typeck/HType.hxx"
#include "typeck/HSymbolType.hxx"
#include <memory>

namespace Hyve::Typeck {
    struct HVariableSymbol : public HSymbol {
        std::shared_ptr<HType> Type;

        HVariableSymbol() {
            SymbolType = HSymbolType::Variable;
        }
    };
}