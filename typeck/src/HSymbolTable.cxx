#include "typeck/HSymbolTable.hxx"
#include <algorithm>
#include <ranges>

namespace Hyve::Typeck {
    HSymbolTable::HSymbolTable(
        std::vector<std::shared_ptr<HSymbol>> children = {}
    ) : _children(children) {}

    std::shared_ptr<HSymbol> HSymbolTable::Find(std::vector<std::string_view> scope, std::string_view name) const {
        // We need to check for each higher level scope if the symbol is there, if not we go one level up
        // First we need to get all files that match the top level scope(module)
        std::vector<std::shared_ptr<HSymbol>> files = {};

        // Make sure scope is not empty
        if (scope.size() == 0) {
			return nullptr;
		}

        auto scopeStart = scope.begin();

        std::ranges::copy_if(
            _children, 
            std::back_inserter(files),
            [scopeStart](const std::shared_ptr<HSymbol>& elem) {
                return elem->Name == *scopeStart;
            }
        );

        // If no files are found, we can return nullptr, because the module is empty
        if (files.size() == 0) {
			return nullptr;
		}

        std::shared_ptr<HSymbol> foundSymbol = nullptr;
        // Now we need to check if the symbol is in the file
		for (auto file : files) {
            auto result = std::ranges::find_if(
                file->Children,
				[name](const std::shared_ptr<HSymbol>& elem) {
					return elem->Name == name;
				}
            );

            if (result != file->Children.end()) {
                foundSymbol = *result;
                break;
            }
		}

        return foundSymbol;
    }

}