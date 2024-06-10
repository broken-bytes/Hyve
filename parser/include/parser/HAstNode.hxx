#pragma once

#include "HAstNodeType.hxx"
#include <memory>
#include <ranges>
#include <string>
#include <vector>

namespace Hyve::Parser {
    struct HAstNode {
		std::string Name;

        virtual ~HAstNode() = default;
        HAstNodeType Type;
        std::weak_ptr<HAstNode> Parent;
        std::vector<std::shared_ptr<HAstNode>> Children;

        inline std::vector<std::string_view> CreateScopeString() const {
			std::vector<std::string_view> scope;
			
			auto* currentNode = this;

			while (currentNode != nullptr) {
				// We have some edge cases where we have a node with no name
				// Block Nodes, Struct Bodies, Class Bodies, etc.
				// We will skip these nodes in the scope
				if(currentNode->Name.empty()) {
					currentNode = currentNode->Parent.lock().get();
					continue;
				}
				scope.push_back(currentNode->Name);
				currentNode = currentNode->Parent.lock().get();
			}
			
			// Reverse the scope so it is in the correct order since we went bottom up
			std::reverse(scope.begin(), scope.end());

			return scope;
		}
    };
}