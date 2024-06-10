#include "typeck/HSymbolTable.hxx"
#include <algorithm>
#include <ranges>

namespace Hyve::Typeck {
    HSymbolTable::HSymbolTable(
        const std::vector<std::shared_ptr<HSymbol>>& children
    ) : _children(children) {
        // TODO: Add the Builtin symbols
    }

    std::shared_ptr<HSymbol> HSymbolTable::Find(std::vector<std::string_view> scope, std::string_view name) const {
        using enum HSymbolType;
        // We need to check for each higher level scope if the symbol is there, if not we go one level up
        
        // Make sure scope is not empty
        if (scope.empty()) {
			return nullptr;
		}

        // We need to find the root scope which is the module
        auto root = std::ranges::find_if(_children, [&](const auto& child) {
                return child->Name == scope[0] && child->SymbolType == Module;
            }
        );

        // If we didn't find the root scope, return nullptr
        if (root == _children.end()) {
            return nullptr;
        }

        // We found the root scope, now we need to find the symbol in the scope
        auto currentScope = *root;

        for (size_t i = 1; i < scope.size(); i++) {
			auto nextScope = FindInScope(currentScope, scope[i]);
			if (nextScope == nullptr) {
				return nullptr;
			}

			currentScope = nextScope;
		}

        // We found the scope, now we need to find the symbol in the scope
		return FindInScope(currentScope, name);
    }

    std::shared_ptr<HSymbol> HSymbolTable::FindInScope(std::shared_ptr<HSymbol> scope, std::string_view name) const {
        // Find the first matching symbol in the scope
        for (auto& child : scope->Children) {
            if (child->Name == name) {
                return child;
			}
        }

        return nullptr;
    }
}