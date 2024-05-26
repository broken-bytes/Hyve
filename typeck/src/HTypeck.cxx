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
#include <memory>

namespace Hyve::Typeck {
	HTypeck::HTypeck() {
	}

    std::shared_ptr<HSymbol> HTypeck::BuildTypeTable(
        const std::shared_ptr<Hyve::Parser::HAstNode>& ast,
        const std::shared_ptr<HSymbol>& parent
    ) {
        // Create the file symbol table as a unique_ptr
        auto fileTable = std::make_shared<HSymbol>();

        // Traverse the AST and build the symbol table
        for (const auto& node : ast->Children) {
            if (node->Type == Hyve::Parser::HAstNodeType::NominalType) {
                auto typeNode = std::dynamic_pointer_cast<Hyve::Parser::HAstTypeNode>(node);

                // Create a symbol as a unique_ptr
                auto symbol = std::make_shared<HClassSymbol>();
                symbol->Name = typeNode->Name;
                symbol->Parent = std::weak_ptr<HSymbol>(parent != nullptr ? parent : fileTable);

                // Get the children of the type node
                for (const auto& child : typeNode->Children) {
                    symbol->Children.push_back(BuildTypeTable(typeNode->Children.front(), symbol));
                }

                fileTable->Children.push_back(symbol);
            }
            else if (node->Type == Hyve::Parser::HAstNodeType::Func) {
                auto funcNode = std::dynamic_pointer_cast<Hyve::Parser::HAstFuncDeclNode>(node);

                // Create a symbol
                auto symbol = std::make_shared<HFunctionSymbol>();
                symbol->Name = funcNode->Name;
                symbol->Parent = std::weak_ptr<HSymbol>(parent != nullptr ? parent : fileTable);

                if(parent != nullptr) {
					parent->Children.push_back(symbol);
                } else {
                    fileTable->Children.push_back(symbol);
                }
            }
        }

        return fileTable; // Return the unique_ptr directly 
    }
}