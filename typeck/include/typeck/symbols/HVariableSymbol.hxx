#include "typeck/HSymbol.hxx"
#include "typeck/HType.hxx"

#include <memory>

namespace Hyve::Typeck {
    class HVariableSymbol : public HSymbol {
    public:
        std::shared_ptr<HType> Type;
    };
}