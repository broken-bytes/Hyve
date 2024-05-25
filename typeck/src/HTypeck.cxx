#include "typeck/HTypeck.hxx"

#include <parser/nodes/HAstTypeNode.hxx>

namespace Hyve::Typeck {
	HTypeck::HTypeck() {
	}

	std::vector<std::string> HTypeck::BuildTypeTable(const Hyve::Parser::HAstNode& ast) {
		std::vector<std::string> typeTable;
		for (const auto& node : ast.Children) {
			// We have a type declaration
			if (node->Type == Parser::HAstNodeType::NominalType) {
				// Convert the node to a type node
				auto typeNode = std::dynamic_pointer_cast<Parser::HAstTypeNode>(node);
				// Add the type to the type table
				typeTable.push_back(typeNode->Value);
			}
			else {
				auto childTable = BuildTypeTable(*node);
				typeTable.insert(typeTable.end(), childTable.begin(), childTable.end());
			}

		}
		return typeTable;
	}
}