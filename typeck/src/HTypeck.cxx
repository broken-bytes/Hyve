#include "typeck/HTypeck.hxx"
#include "typeck/HSymbolTable.hxx"
#include "typeck/HSymbol.hxx"
#include "typeck/symbols/HClassSymbol.hxx"
#include "typeck/symbols/HEnumSymbol.hxx"
#include "typeck/symbols/HFileSymbol.hxx"
#include "typeck/symbols/HFunctionSymbol.hxx"
#include "typeck/symbols/HModuleSymbol.hxx"
#include "typeck/symbols/HPropertySymbol.hxx"
#include "typeck/symbols/HProtocolSymbol.hxx"
#include "typeck/symbols/HPrototypeSymbol.hxx"
#include "typeck/symbols/HStructSymbol.hxx"
#include "typeck/symbols/HVariableSymbol.hxx"
#include <parser/HAstNode.hxx>
#include <parser/nodes/HAstTypeNode.hxx>
#include <parser/nodes/HAstClassNode.hxx>
#include <parser/nodes/HAstFileNode.hxx>
#include <parser/nodes/HAstFuncDeclNode.hxx>
#include <parser/nodes/HAstInitDeclNode.hxx>
#include <parser/nodes/HAstLiteralNode.hxx>
#include <parser/nodes/HAstModuleDeclNode.hxx>
#include <parser/nodes/HAstPropertyDeclNode.hxx>
#include <parser/nodes/HAstVarDeclNode.hxx>
#include <algorithm>
#include <memory>
#include <ranges>
#include <stdexcept>

namespace Hyve::Typeck {
    HSymbolType NodeTypeToSymbolType(Parser::HAstTypeKind type) {
        switch (type) {
        case Parser::HAstTypeKind::Class:
            return HSymbolType::Class;
        case Parser::HAstTypeKind::Enum:
            return HSymbolType::Enum;
        case Parser::HAstTypeKind::Function:
            return HSymbolType::Function;
        case Parser::HAstTypeKind::Protocol:
            return HSymbolType::Protocol;
        case Parser::HAstTypeKind::Struct:
            return HSymbolType::Struct;
        case Parser::HAstTypeKind::Prototype:
            return HSymbolType::Prototype;
        default:
            return HSymbolType::UnknownSymbol;
        }
    }

    Parser::HAstTypeKind SymbolTypeToNodeType(HSymbolType type) {
		switch (type) {
		case HSymbolType::Class:
			return Parser::HAstTypeKind::Class;
		case HSymbolType::Enum:
			return Parser::HAstTypeKind::Enum;
        case HSymbolType::File:
			return Parser::HAstTypeKind::File;
		case HSymbolType::Function:
			return Parser::HAstTypeKind::Function;
        case HSymbolType::Module:
            return Parser::HAstTypeKind::Module;
		case HSymbolType::Protocol:
			return Parser::HAstTypeKind::Protocol;
		case HSymbolType::Prototype:
			return Parser::HAstTypeKind::Prototype;
        case HSymbolType::Struct:
            return Parser::HAstTypeKind::Struct;
        case HSymbolType::Variable:
			return Parser::HAstTypeKind::Variable;
        default:
            return Parser::HAstTypeKind::UnknownKind;
		}
	}

	HTypeck::HTypeck() {
        _builtins = std::make_shared<HSymbol>();
	}

    std::shared_ptr<HSymbolTable> HTypeck::MergeSymbols(
        const std::vector<std::shared_ptr<HSymbol>>& symbolTables
    ) {
		std::vector<std::shared_ptr<HSymbol>> mergedSymbols;

		// We only need to merge duplicate modules.
        // Since we know modules are top-level, 
        // we can just add the children of the right-hand side to the left-hand side, if the module names are the same
        // Otherwise, we just add the right-hand side to the left-hand side
        for (const auto& symbolTable : symbolTables) {
            auto moduleSymbol = std::dynamic_pointer_cast<HModuleSymbol>(symbolTable);

            if (moduleSymbol == nullptr) {
				throw std::runtime_error("Symbol table does not have a module symbol");
			}

            auto existingModule = std::ranges::find_if(
				mergedSymbols,
				[moduleSymbol](const std::shared_ptr<HSymbol>& symbol) {
					return symbol->Name == moduleSymbol->Name && symbol->SymbolType == HSymbolType::Module;
				}
			);

			if (existingModule != mergedSymbols.end()) {
				// Merge the children of the right-hand side to the left-hand side
				for (const auto& child : moduleSymbol->Children) {
					(*existingModule)->Children.push_back(child);
				}
			} else {
				mergedSymbols.push_back(moduleSymbol);
			}
        }

		return std::make_shared<HSymbolTable>(mergedSymbols);
	}

    std::shared_ptr<HSymbol> HTypeck::BuildSymbolTable(
        const std::shared_ptr<Hyve::Parser::HAstNode>& ast,
        const std::shared_ptr<HSymbol>& parent
    ) {
        using enum Parser::HAstTypeKind;

        // Traverse the AST and build the symbol table
        // We have a few edge cases to consider:
        // An AST always starts with a module node, followed by any number of submodules.
        // The deepest module node will have a file node.
        // This means we only need to check in the module node if we have a parent or not.

        // Do the module check here
        if (parent == nullptr) {
            auto moduleNode = std::dynamic_pointer_cast<Hyve::Parser::HAstModuleDeclNode>(ast);

            std::shared_ptr<HSymbol> symbol = nullptr;

            symbol = std::make_shared<HModuleSymbol>();
            symbol->SymbolType = HSymbolType::Module;
            symbol->Name = moduleNode->Name;

            return BuildSymbolTable(ast, symbol);
        }

        for (const auto& node : ast->Children) {
            if (node->Type == Parser::HAstNodeType::Module) {
                auto moduleNode = std::dynamic_pointer_cast<Hyve::Parser::HAstModuleDeclNode>(node);
                std::shared_ptr<HSymbol> symbol = nullptr;

                symbol = std::make_shared<HModuleSymbol>();
                symbol->Name = moduleNode->Name;
                parent->Children.push_back(symbol);
                symbol->Parent = std::weak_ptr<HSymbol>(parent);

                BuildSymbolTable(node, symbol);

            } else if (node->Type == Hyve::Parser::HAstNodeType::NominalType) {
                auto typeNode = std::dynamic_pointer_cast<Hyve::Parser::HAstTypeNode>(node);

                // Create a symbol as a unique_ptr
                std::shared_ptr<HSymbol> symbol = nullptr;

                if (typeNode->Kind == Class) {
                    symbol = std::make_shared<HClassSymbol>();
                }
                else if (typeNode->Kind == Enum) {
                    symbol = std::make_shared<HEnumSymbol>();
                }
                else if (typeNode->Kind == Protocol) {
                    symbol = std::make_shared<HProtocolSymbol>();
                }
                else if (typeNode->Kind == Prototype) {
                    symbol = std::make_shared<HPrototypeSymbol>();
                }
                else if (typeNode->Kind == Struct) {
                    symbol = std::make_shared<HStructSymbol>();
                }

                symbol->Name = typeNode->Name;
                symbol->Parent = std::weak_ptr<HSymbol>(parent);

                // Get the children of the the body node, if any
                if (!typeNode->Children.empty()) {
                    auto bodyNode = typeNode->Children[0];

                    BuildSymbolTable(bodyNode, symbol);
                }

                parent->Children.push_back(symbol);

            }
            else if (node->Type == Hyve::Parser::HAstNodeType::File) {
                auto fileNode = std::dynamic_pointer_cast<Hyve::Parser::HAstFileNode>(node);

                // Create a symbol
                auto symbol = std::make_shared<HFileSymbol>();
                symbol->Name = fileNode->Name;
                symbol->Parent = std::weak_ptr<HSymbol>(parent);

                if (!fileNode->Children.empty()) {
                    BuildSymbolTable(fileNode, symbol);
                }

                parent->Children.push_back(symbol);
            } else if (node->Type == Hyve::Parser::HAstNodeType::Func) {
                auto funcNode = std::dynamic_pointer_cast<Hyve::Parser::HAstFuncDeclNode>(node);

                // Create a symbol
                auto symbol = std::make_shared<HFunctionSymbol>();
                symbol->Name = funcNode->Name;
                symbol->Parent = std::weak_ptr<HSymbol>(parent);
                symbol->AccessLevel = funcNode->AccessLevel;

                // Get the children of the the body node, if any
                if (!funcNode->Children.empty()) {
                    auto bodyNode = funcNode->Children[0];

                    BuildSymbolTable(bodyNode, symbol);
                }

			    parent->Children.push_back(symbol);
            } else if (node->Type == Hyve::Parser::HAstNodeType::Init) {
                auto initNode = std::dynamic_pointer_cast<Parser::HAstInitDeclNode>(node);

                // Create a symbol
                auto symbol = std::make_shared<HFunctionSymbol>();
                symbol->Name = initNode->Name;
                symbol->Parent = std::weak_ptr<HSymbol>(parent);
                symbol->AccessLevel = initNode->AccessLevel;

                // Get the children of the the body node, if any
                if (!initNode->Children.empty()) {
                    auto bodyNode = initNode->Children[0];

                    BuildSymbolTable(bodyNode, symbol);
                }

                parent->Children.push_back(symbol);
            } else if (node->Type == Hyve::Parser::HAstNodeType::PropertyDecl) {
                auto declNode = std::dynamic_pointer_cast<Hyve::Parser::HAstPropertyDeclNode>(node);

                // Create a symbol
                auto symbol = std::make_shared<HPropertySymbol>();
                symbol->Name = declNode->Name;
                symbol->Parent = std::weak_ptr<HSymbol>(parent);
                symbol->AccessLevel = declNode->AccessLevel;

                auto type = std::make_shared<HType>();

                if(declNode->TypeNode != nullptr) {
					type->SymbolType = NodeTypeToSymbolType(declNode->TypeNode->Kind);
					type->Name = declNode->TypeNode->Name;
				} else {
					type->SymbolType = HSymbolType::UnknownSymbol;
                    type->Name = "";
				}

                symbol->Type = type;

                // Get the children of the type node
                for (const auto& child : declNode->Children) {
                    symbol->Children.push_back(BuildSymbolTable(child, symbol));
                }

                parent->Children.push_back(symbol);
            }
            else if (node->Type == Hyve::Parser::HAstNodeType::VariableDecl) {
                auto declNode = std::dynamic_pointer_cast<Hyve::Parser::HAstVarDeclNode>(node);

                // Create a symbol
                auto symbol = std::make_shared<HVariableSymbol>();
                symbol->Name = declNode->Name;
                symbol->Parent = std::weak_ptr<HSymbol>(parent);

                auto type = std::make_shared<HType>();

                if (declNode->TypeNode != nullptr) {
                    type->SymbolType = NodeTypeToSymbolType(declNode->TypeNode->Kind);
                    type->Name = declNode->TypeNode->Name;
                }
                else {
                    type->SymbolType = HSymbolType::UnknownSymbol;
                    type->Name = "";
                }

                symbol->Type = type;

                // Get the children of the type node
                for (const auto& child : declNode->Children) {
                    symbol->Children.push_back(BuildSymbolTable(child, symbol));
                }

                parent->Children.push_back(symbol);
            }
        }

        return parent;
    }

    void HTypeck::InferTypes(
        const std::shared_ptr<HSymbolTable>& symbols,
        std::shared_ptr<Parser::HAstNode>& nodes
    ) {
        using enum Parser::HAstNodeType;
        // Files/Modules only need their children to be inferred
        if (nodes->Type == File || nodes->Type == Module) {
            for(auto& node: nodes->Children) {
				InferTypes(symbols, node);
			}
        } else if (nodes->Type == NominalType || nodes->Type == Func) {
            // Get the body node
            if (nodes->Children.empty()) {
                return;
            }
            auto bodyNode = nodes->Children[0];
            for (auto& node : bodyNode->Children) {
                InferTypes(symbols, node);
            }
        } else if (nodes->Type == PropertyDecl) {
            auto declNode = std::dynamic_pointer_cast<Parser::HAstPropertyDeclNode>(nodes);

            // We only infer the type if the type node is null and the initializer is not null
            if (declNode->TypeNode == nullptr) {
                if (declNode->Initializer != nullptr) {
                    // Get the type of the initializer expression
                    declNode->TypeNode = CalculateExpressionType(declNode->Initializer, nullptr);
                } else {
					throw std::runtime_error("Property declaration does not have a type or initializer");
                }
            } else {
                // Check that the type actually exists
                // We do this by checking if the type is in the current scope
                // If it is not, we go one level up and check again, until we reach the top level
                // We traverse the tree in a depth-first manner
                auto type = declNode->TypeNode;
                
                auto foundSymbol = symbols->Find(declNode->CreateScopeString(), declNode->TypeNode->Name);
            }
        }
    }

    std::shared_ptr<Parser::HAstTypeNode> HTypeck::CalculateExpressionType(
        const std::shared_ptr<Parser::HAstNode>& node,
        const std::shared_ptr<HSymbol>& symbol
    ) {
        // TODO: Implement this
        
        // If we have just a literal node, we can return the type of the literal immediately
        if (node->Type == Parser::HAstNodeType::Literal) {
			auto literalNode = std::dynamic_pointer_cast<Parser::HAstLiteralNode>(node);
			
		}

        return nullptr;
    }
}