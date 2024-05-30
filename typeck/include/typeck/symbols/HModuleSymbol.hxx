#pragma once

#include "typeck/HSymbol.hxx"
#include "typeck/HSymbolType.hxx"
#include <string>

namespace Hyve::Typeck {
    class HModuleSymbol : public HSymbol {
        public:
		HModuleSymbol() {
            SymbolType = HSymbolType::Module;
        }
    };
}