#include "typeck/HTypeck.hxx"
#include "typeck/HSymbolTable.hxx"
#include "typeck/HSymbol.hxx"
#include "typeck/symbols/HClassSymbol.hxx"
#include "typeck/symbols/HFunctionSymbol.hxx"
#include "typeck/symbols/HProtocolSymbol.hxx"
#include "typeck/symbols/HPrototypeSymbol.hxx"
#include "typeck/symbols/HStructSymbol.hxx"
#include "typeck/symbols/HVariableSymbol.hxx"
#include <parser/nodes/HAstTypeNode.hxx>
#include <parser/nodes/HAstClassNode.hxx>
#include <parser/nodes/HAstFuncDeclNode.hxx>
#include <parser/nodes/HAstLiteralNode.hxx>
#include <parser/nodes/HAstVarDeclNode.hxx>
#include <memory>

namespace Hyve::Typeck {
	HTypeck::HTypeck() {
	}

    std::shared_ptr<HSymbol> HTypeck::BuildTypeTable(
        const std::shared_ptr<Hyve::Parser::HAstNode>& ast,
        const std::shared_ptr<HSymbol>& parent
    ) {
        // Traverse the AST and build the symbol table
        for (const auto& node : ast->Children) {
            if (node->Type == Hyve::Parser::HAstNodeType::NominalType) {
                auto typeNode = std::dynamic_pointer_cast<Hyve::Parser::HAstTypeNode>(node);

                // Create a symbol as a unique_ptr
                auto symbol = std::make_shared<HClassSymbol>();
                symbol->Name = typeNode->Name;
                symbol->Parent = std::weak_ptr<HSymbol>(parent);

                // Get the children of the the body node, if any
                if (!typeNode->Children.empty()) {
                    auto bodyNode = typeNode->Children[0];

                    BuildTypeTable(bodyNode, symbol);  
                }

                parent->Children.push_back(symbol);
                
            }
            else if (node->Type == Hyve::Parser::HAstNodeType::Func) {
                auto funcNode = std::dynamic_pointer_cast<Hyve::Parser::HAstFuncDeclNode>(node);

                // Create a symbol
                auto symbol = std::make_shared<HFunctionSymbol>();
                symbol->Name = funcNode->Name;
                symbol->Parent = std::weak_ptr<HSymbol>(parent);

                // Get the children of the the body node, if any
                if (!funcNode->Children.empty()) {
                    auto bodyNode = funcNode->Children[0];

                    BuildTypeTable(bodyNode, symbol);
                }

			    parent->Children.push_back(symbol);
            }
            else if (node->Type == Hyve::Parser::HAstNodeType::Decl) {
                auto declNode = std::dynamic_pointer_cast<Hyve::Parser::HAstVarDeclNode>(node);

                // Create a symbol
                auto symbol = std::make_shared<HVariableSymbol>();
                symbol->Name = declNode->Name;
                symbol->Parent = std::weak_ptr<HSymbol>(parent);

                // Get the children of the type node
                for (const auto& child : declNode->Children) {
                    symbol->Children.push_back(BuildTypeTable(child, symbol));
                }

                parent->Children.push_back(symbol);
            }
        }

        return parent;
    }

    void HTypeck::InferTypes(
        const std::vector<std::shared_ptr<HSymbol>>& symbols,
        const std::shared_ptr<Parser::HAstNode>& ast
    ) {
        for (const auto& node : ast->Children) {
            // First infer all the types of the children
            InferTypes(symbols, node);

            if (node->Type == Parser::HAstNodeType::Decl) {
                auto declNode = std::dynamic_pointer_cast<Parser::HAstVarDeclNode>(node);

                // We need to infer the type of the variable
                if (declNode->TypeNode != nullptr) {
                    if (declNode->Initializer->ExpressionType == Parser::ExpressionType::Literal) {
                        auto literalNode = std::dynamic_pointer_cast<Parser::HAstLiteralNode>(declNode->Initializer);

                        if (literalNode->Type == "String") {
                            declNode->TypeNode = std::make_shared<Parser::HAstTypeNode>();
                            declNode->TypeNode->Type = Parser::HAstNodeType::Literal;
                            declNode->TypeNode->Name = "String";
                        }
                    }
                }
            }
		}
    }
}