#pragma once

#include "typeck/HSymbolType.hxx"

#include <memory>
#include <string>
#include <vector>

namespace Hyve::Typeck {
    struct HSymbol {
    public:
        std::string Name;
        HSymbolType SymbolType;
        std::weak_ptr<HSymbol> Parent;
        std::vector<std::shared_ptr<HSymbol>> Children;

        virtual ~HSymbol() = default;
    };
}