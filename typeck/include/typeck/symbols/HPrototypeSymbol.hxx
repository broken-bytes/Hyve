#include "typeck/HSymbol.hxx"
#include "typeck/HSymbolType.hxx"

namespace Hyve::Typeck {
    struct HPrototypeSymbol : public HSymbol {
        HPrototypeSymbol() {
            SymbolType = HSymbolType::Prototype;
        }
    };
}