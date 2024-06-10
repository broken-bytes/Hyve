#pragma once

#include "typeck/HSymbol.hxx"
#include <memory>
#include <string_view>
#include <vector>

namespace Hyve::Typeck {
    struct HSymbolTable {
    public:
        explicit HSymbolTable(
            std::vector<std::shared_ptr<HSymbol>> children = {}
        );
        
        std::shared_ptr<HSymbol> Find(std::vector<std::string_view> scope, std::string_view name) const;

    private:
        std::vector<std::shared_ptr<HSymbol>> _children;
	};
}