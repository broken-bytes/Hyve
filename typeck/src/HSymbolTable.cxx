#include "typeck/HSymbolTable.hxx"
#include "typeck/symbols/HModuleSymbol.hxx"
#include <algorithm>
#include <memory>
#include <ranges>

namespace Hyve::Typeck {
    HSymbolTable::HSymbolTable() {
#ifdef HYVE_BOOTSTRAP
        // Add the built-in types to the symbol table
		AddBuiltInTypes();
#endif
    }

    void HSymbolTable::Append(const std::shared_ptr<HSymbol>& symbol) {
        // Check for emptiness to increase performance
        if (_children.empty()) {
            _children.push_back(symbol);

            return;
        }

        // Check if the symbol is already in the symbol table
        auto existingSymbol = std::ranges::find_if(_children, [&](const auto& child) {
				return child->Name == symbol->Name;
			}
		);

        // If the symbol is not in the symbol table, add it
		if (existingSymbol == _children.end()) {
			_children.push_back(symbol);
        }
        else {
            // If the symbol is in the symbol table, update it
            for (const auto& child : symbol->Children) {
                (*existingSymbol)->AppendChild(child);
            }
        }
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

    std::shared_ptr<HSymbol> HSymbolTable::Find(std::string_view name) const {
        // Find the first matching symbol in the root scope
        for (auto& child : _children) {
            if (child->Name == name) {
                return child;
            }
            else {
                return child->FindNestedChild(name);
            }
        }

        return nullptr;
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

#ifdef HYVE_BOOTSTRAP
    void HSymbolTable::AddBuiltInTypes() {
        // Add the low-level types to the symbol table

		auto int8Type = std::make_shared<HSymbol>();
        int8Type->Name = "i8";
        int8Type->SymbolType = HSymbolType::Struct;

        auto int16Type = std::make_shared<HSymbol>();
        int16Type->Name = "i16";
        int16Type->SymbolType = HSymbolType::Struct;

        auto int32Type = std::make_shared<HSymbol>();
        int32Type->Name = "i32";
        int32Type->SymbolType = HSymbolType::Struct;

        auto int64Type = std::make_shared<HSymbol>();
        int64Type->Name = "i64";
        int64Type->SymbolType = HSymbolType::Struct;

		auto floatType = std::make_shared<HSymbol>();
        floatType->Name = "float";
		floatType->SymbolType = HSymbolType::Struct;

        auto doubleType = std::make_shared<HSymbol>();
        doubleType->Name = "double";
        doubleType->SymbolType = HSymbolType::Struct;

        auto lowLevelModule = std::make_shared<HModuleSymbol>();
        lowLevelModule->Name = "lowlevel";

        lowLevelModule->Children.push_back(int8Type);
        lowLevelModule->Children.push_back(int16Type);
        lowLevelModule->Children.push_back(int32Type);
        lowLevelModule->Children.push_back(int64Type);
        lowLevelModule->Children.push_back(floatType);
        lowLevelModule->Children.push_back(doubleType);

        // Create the "hyve" module
        auto hyveModule = std::make_shared<HModuleSymbol>();
        hyveModule->Name = "hyve";

        // Add the low-level module to the "hyve" module
        hyveModule->Children.push_back(lowLevelModule);

        // Add the "hyve" module to the symbol table
        _children.push_back(hyveModule);
    }
#endif
}