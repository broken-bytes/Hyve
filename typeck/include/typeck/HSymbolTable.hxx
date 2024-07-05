#pragma once

#include "typeck/HSymbol.hxx"
#include <memory>
#include <string_view>
#include <vector>

namespace Hyve::Typeck {
    struct HSymbolTable {
    public:
        explicit HSymbolTable();

        void Append(const std::shared_ptr<HSymbol>& symbol);
        
        std::shared_ptr<HSymbol> Find(std::vector<std::string_view> scope, std::string_view name) const;
        std::shared_ptr<HSymbol> Find(std::string_view name) const;

    private:
        std::vector<std::shared_ptr<HSymbol>> _children;

        std::shared_ptr<HSymbol> FindInScope(std::shared_ptr<HSymbol> scope, std::string_view name) const;

#ifdef HYVE_BOOTSTRAP
        void AddBuiltInTypes();
#endif
	};
}