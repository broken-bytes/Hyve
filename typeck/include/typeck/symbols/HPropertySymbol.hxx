#include "typeck/HSymbol.hxx"
#include "typeck/HType.hxx"
#include "typeck/symbols/HWithAccessLevelSymbol.hxx"
#include <core/HAccessLevel.hxx>

#include <memory>

namespace Hyve::Typeck {
    struct HPropertySymbol : public HWithAccessLevelSymbol {
    public:
        std::shared_ptr<HType> Type;
    };
}