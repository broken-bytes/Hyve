#pragma once

#include "ast/HAstNodeType.hxx"
#include <memory>
#include <ranges>
#include <string>
#include <vector>

namespace Hyve::AST {
    struct HAstNode {
		std::string Name;

		HAstNode() {
			Children = {};
		}

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
			std::ranges::reverse(scope);

			return scope;
		}

		static inline std::vector<std::shared_ptr<HAstNode>> FindNodesWithType(HAstNodeType type, std::shared_ptr<HAstNode> root) {
			auto nodes = std::vector<std::shared_ptr<HAstNode>>();

			auto currentNode = root;

			if (currentNode->Type == type) {
				nodes.push_back(std::shared_ptr<HAstNode>(currentNode));
			}

			for(const auto& child : currentNode->Children) {
				for(const auto& node : FindNodesWithType(type, child)) {
					nodes.push_back(node);
				}
			}

			return nodes;
		}

		static inline std::shared_ptr<HAstNode> Root(std::shared_ptr<HAstNode> node) {
			auto currentNode = node;

			while (currentNode->Parent.lock() != nullptr) {
				currentNode = currentNode->Parent.lock();
			}

			return currentNode;
		}
    };
}