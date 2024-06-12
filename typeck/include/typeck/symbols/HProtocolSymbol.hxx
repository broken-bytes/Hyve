#include "typeck/HSymbol.hxx"
#include "typeck/HSymbolType.hxx"

namespace Hyve::Typeck {
    struct HProtocolSymbol : public HSymbol {
        HProtocolSymbol() {
            SymbolType = HSymbolType::Protocol;
        }
    };
}