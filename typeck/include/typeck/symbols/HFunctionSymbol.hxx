#include "typeck/HSymbol.hxx"
#include "typeck/symbols/HWithAccessLevelSymbol.hxx"
#include "typeck/HSymbolType.hxx"

namespace Hyve::Typeck {
    struct HFunctionSymbol : public HWithAccessLevelSymbol {
        HFunctionSymbol() {
            SymbolType = HSymbolType::Function;
        }
    };
}