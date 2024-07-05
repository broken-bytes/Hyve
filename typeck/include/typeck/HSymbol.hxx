#pragma once

#include "typeck/HSymbolType.hxx"

#include <memory>
#include <string>
#include <vector>

namespace Hyve::Typeck {
    struct HSymbol : std::enable_shared_from_this<HSymbol> {
    public:
        std::string Name;
        HSymbolType SymbolType;
        std::weak_ptr<HSymbol> Parent;
        std::vector<std::shared_ptr<HSymbol>> Children;

        virtual ~HSymbol() = default;

		/**
		* @brief Finds a child symbol by name
		* @param name The name of the child symbol to find
		* @return The child symbol if found, otherwise nullptr
		* @note This function does not search nested children, use FindNestedChild for that
		*/
        std::shared_ptr<HSymbol> FindChild(const std::string_view name) const {
            // Finds a child symbol by name
            for (const auto& child : Children) {
				if (child->Name == name) {
					return child;
                }
			}

            return nullptr;
        }

		/**
		* @brief Finds a nested child symbol by name
		* @param name The name of the child symbol to find
		* @return The child symbol if found, otherwise nullptr
		*/
        std::shared_ptr<HSymbol> FindNestedChild(const std::string_view name) const {
            // Finds a nested child symbol by name
			for (const auto& child : Children) {
				if (child->Name == name) {
					return child;
				}

				auto nestedChild = child->FindNestedChild(name);
				if (nestedChild != nullptr) {
					return nestedChild;
				}
			}

			return nullptr;
        }

		/**
		* @brief Appends a child symbol to the symbol
		* @note If the child exists, all grandchildren of the symbol to add will be appended to the existing child
		* @param child The child symbol to append
        */
		void AppendChild(std::shared_ptr<HSymbol> child) {
            auto existingChild = FindChild(child->Name);
			if (existingChild != nullptr) {
				for (const auto& grandchild : child->Children) {
					existingChild->AppendChild(grandchild);
				}
			} else {
				child->Parent = shared_from_this();
				Children.push_back(child);
			}
		}
    };
}