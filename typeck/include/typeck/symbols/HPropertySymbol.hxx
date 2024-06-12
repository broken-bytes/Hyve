#include "typeck/HSymbol.hxx"
#include "typeck/HType.hxx"
#include "typeck/HSymbolType.hxx"
#include "typeck/symbols/HWithAccessLevelSymbol.hxx"
#include <core/HAccessLevel.hxx>

#include <memory>

namespace Hyve::Typeck {
    struct HPropertySymbol : public HWithAccessLevelSymbol {
        std::shared_ptr<HType> Type;

        HPropertySymbol() {
            SymbolType = HSymbolType::Property;
        }
    };
}