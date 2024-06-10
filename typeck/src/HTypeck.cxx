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

    std::vector<std::shared_ptr<HSymbol>> HTypeck::MergeSymbols(
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

		return mergedSymbols;
	}

    std::shared_ptr<HSymbol> HTypeck::BuildTypeTable(
        const std::shared_ptr<Hyve::Parser::HAstNode>& ast,
        const std::shared_ptr<HSymbol>& parent
    ) {
        if (parent == nullptr && ast->Type == Hyve::Parser::HAstNodeType::File) {
            auto fileNode = std::dynamic_pointer_cast<Hyve::Parser::HAstFileNode>(ast);

            // Create the symbol
            auto fileSymbol = std::make_shared<HFileSymbol>();
            fileSymbol->Name = fileNode->Name;
            fileSymbol->SymbolType = HSymbolType::File;

            // Get the children of the the body node, if any
            if (fileNode->Children.empty()) {
                return fileSymbol;
            }

            // Check if the file has a module declaration, if so, create a module symbol. 
            // Otherwise we need to add it to the unnamed module
            auto moduleNode = std::ranges::find_if(
                fileNode->Children, 
                [](const std::shared_ptr<Hyve::Parser::HAstNode>& node) {
					return node->Type == Hyve::Parser::HAstNodeType::Module;
				}
			);

            auto typedModuleNode = std::dynamic_pointer_cast<Hyve::Parser::HAstModuleDeclNode>(*moduleNode);

            if (moduleNode == fileNode->Children.end()) {
                // Throw an error if the file does not have a module declaration for now
                throw std::runtime_error("File does not have a module declaration");
            }

            auto moduleSymbol = std::make_shared<HModuleSymbol>();
            moduleSymbol->Name = typedModuleNode->Name;

            // Set the parent of the file symbol to the module symbol
            fileSymbol->Parent = std::weak_ptr<HSymbol>(moduleSymbol);

            // Add the file symbol to the module symbol children
            moduleSymbol->Children.push_back(fileSymbol);

            BuildTypeTable(typedModuleNode, fileSymbol);

            return moduleSymbol;
        }

        // Traverse the AST and build the symbol table
        for (const auto& node : ast->Children) {
            if (node->Type == Hyve::Parser::HAstNodeType::NominalType) {
                auto typeNode = std::dynamic_pointer_cast<Hyve::Parser::HAstTypeNode>(node);

                // Create a symbol as a unique_ptr
                std::shared_ptr<HSymbol> symbol = nullptr;

                if (typeNode->Kind == Parser::HAstTypeKind::Class) {
                    symbol = std::make_shared<HClassSymbol>();
                    symbol->SymbolType = HSymbolType::Class;
                } else if (typeNode->Kind == Parser::HAstTypeKind::Enum) {
                    symbol = std::make_shared<HEnumSymbol>();
                    symbol->SymbolType = HSymbolType::Enum;
                } else if (typeNode->Kind == Parser::HAstTypeKind::Protocol) {
                    symbol = std::make_shared<HProtocolSymbol>();
                    symbol->SymbolType = HSymbolType::Protocol;
                } else if (typeNode->Kind == Parser::HAstTypeKind::Prototype) {
                    symbol = std::make_shared<HPrototypeSymbol>();
                    symbol->SymbolType = HSymbolType::Prototype;
			    } else if (typeNode->Kind == Parser::HAstTypeKind::Struct) {
                    symbol = std::make_shared<HStructSymbol>();
                    symbol->SymbolType = HSymbolType::Struct;
                }
					
                symbol->Name = typeNode->Name;
                symbol->Parent = std::weak_ptr<HSymbol>(parent);

                // Get the children of the the body node, if any
                if (!typeNode->Children.empty()) {
                    auto bodyNode = typeNode->Children[0];

                    BuildTypeTable(bodyNode, symbol);  
                }

                parent->Children.push_back(symbol);
                
            } else if (node->Type == Hyve::Parser::HAstNodeType::Func) {
                auto funcNode = std::dynamic_pointer_cast<Hyve::Parser::HAstFuncDeclNode>(node);

                // Create a symbol
                auto symbol = std::make_shared<HFunctionSymbol>();
                symbol->Name = funcNode->Name;
                symbol->Parent = std::weak_ptr<HSymbol>(parent);
                symbol->SymbolType = HSymbolType::Function;
                symbol->AccessLevel = funcNode->AccessLevel;

                // Get the children of the the body node, if any
                if (!funcNode->Children.empty()) {
                    auto bodyNode = funcNode->Children[0];

                    BuildTypeTable(bodyNode, symbol);
                }

			    parent->Children.push_back(symbol);
            } else if (node->Type == Hyve::Parser::HAstNodeType::PropertyDecl) {
                auto declNode = std::dynamic_pointer_cast<Hyve::Parser::HAstPropertyDeclNode>(node);

                // Create a symbol
                auto symbol = std::make_shared<HPropertySymbol>();
                symbol->Name = declNode->Name;
                symbol->Parent = std::weak_ptr<HSymbol>(parent);
                symbol->SymbolType = HSymbolType::Variable;
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
                    symbol->Children.push_back(BuildTypeTable(child, symbol));
                }

                parent->Children.push_back(symbol);
            }
            else if (node->Type == Hyve::Parser::HAstNodeType::VariableDecl) {
                auto declNode = std::dynamic_pointer_cast<Hyve::Parser::HAstVarDeclNode>(node);

                // Create a symbol
                auto symbol = std::make_shared<HVariableSymbol>();
                symbol->Name = declNode->Name;
                symbol->Parent = std::weak_ptr<HSymbol>(parent);
                symbol->SymbolType = HSymbolType::Variable;

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
                    symbol->Children.push_back(BuildTypeTable(child, symbol));
                }

                parent->Children.push_back(symbol);
            }
        }

        return parent;
    }

    void HTypeck::InferTypes(
        const std::vector<std::shared_ptr<HSymbol>>& symbols,
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