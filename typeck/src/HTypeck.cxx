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
#include <ast/HAstNode.hxx>
#include <ast/nodes/HAstTypeNode.hxx>
#include <ast/nodes/HAstClassNode.hxx>
#include <ast/nodes/HAstFileNode.hxx>
#include <ast/nodes/HAstFuncDeclNode.hxx>
#include <ast/nodes/HAstImportNode.hxx>
#include <ast/nodes/HAstInitDeclNode.hxx>
#include <ast/nodes/HAstLiteralNode.hxx>
#include <ast/nodes/HAstModuleDeclNode.hxx>
#include <ast/nodes/HAstPropertyDeclNode.hxx>
#include <ast/nodes/HAstVarDeclNode.hxx>
#include <algorithm>
#include <iostream>
#include <memory>
#include <ranges>
#include <stdexcept>

std::vector<std::string_view> splitString(std::string_view str, char delimiter) {
    std::vector<std::string_view> tokens;
    size_t start = 0;
    size_t end;

    while ((end = str.find(delimiter, start)) != std::string_view::npos) {
        tokens.emplace_back(str.substr(start, end - start));
        start = end + 1;
    }

    tokens.emplace_back(str.substr(start));
    
    return tokens;
}

namespace Hyve::Typeck {
    using namespace AST;
    HSymbolType NodeTypeToSymbolType(HAstTypeKind type) {
        switch (type) {
        case HAstTypeKind::Class:
            return HSymbolType::Class;
        case HAstTypeKind::Enum:
            return HSymbolType::Enum;
        case HAstTypeKind::Function:
            return HSymbolType::Function;
        case HAstTypeKind::Protocol:
            return HSymbolType::Protocol;
        case HAstTypeKind::Struct:
            return HSymbolType::Struct;
        case HAstTypeKind::Prototype:
            return HSymbolType::Prototype;
        default:
            return HSymbolType::UnknownSymbol;
        }
    }

    HAstTypeKind SymbolTypeToNodeType(HSymbolType type) {
		switch (type) {
		case HSymbolType::Class:
			return HAstTypeKind::Class;
		case HSymbolType::Enum:
			return HAstTypeKind::Enum;
        case HSymbolType::File:
			return HAstTypeKind::File;
		case HSymbolType::Function:
			return HAstTypeKind::Function;
        case HSymbolType::Module:
            return HAstTypeKind::Module;
		case HSymbolType::Protocol:
			return HAstTypeKind::Protocol;
		case HSymbolType::Prototype:
			return HAstTypeKind::Prototype;
        case HSymbolType::Struct:
            return HAstTypeKind::Struct;
        case HSymbolType::Variable:
			return HAstTypeKind::Variable;
        default:
            return HAstTypeKind::UnknownKind;
		}
	}

	HTypeck::HTypeck() {
        _builtins = std::make_shared<HSymbol>();
	}

    std::shared_ptr<HSymbolTable> HTypeck::MergeSymbols(
        const std::vector<std::shared_ptr<HSymbol>>& symbolTables
    ) {
		auto mergedSymbols = std::make_shared<HSymbolTable >();

		// We only need to merge duplicate modules.
        // Since we know modules are top-level, 
        // we can just add the children of the right-hand side to the left-hand side, if the module names are the same
        // Otherwise, we just add the right-hand side to the left-hand side
        for (const auto& symbolTable : symbolTables) {
            auto moduleSymbol = std::dynamic_pointer_cast<HModuleSymbol>(symbolTable);

            if (moduleSymbol == nullptr) {
				throw std::runtime_error("Symbol table does not have a module symbol");
			}

            MergeModuleWithTable(mergedSymbols, moduleSymbol);
        }

        return mergedSymbols;
	}

    std::shared_ptr<HSymbol> HTypeck::BuildSymbolTable(
        const std::shared_ptr<HAstNode>& ast,
        const std::shared_ptr<HSymbol>& parent
    ) {
        using enum HAstTypeKind;

        // Traverse the AST and build the symbol table
        // We have a few edge cases to consider:
        // An AST always starts with a module node, followed by any number of submodules.
        // The deepest module node will have a file node.
        // This means we only need to check in the module node if we have a parent or not.

        // Do the module check here
        if (parent == nullptr) {
            auto moduleNode = std::dynamic_pointer_cast<HAstModuleDeclNode>(ast);

            std::shared_ptr<HSymbol> symbol = nullptr;

            symbol = std::make_shared<HModuleSymbol>();
            symbol->SymbolType = HSymbolType::Module;
            symbol->Name = moduleNode->Name;

            return BuildSymbolTable(ast, symbol);
        }

        for (const auto& node : ast->Children) {
            if (node->Type == HAstNodeType::Module) {
                auto moduleNode = std::dynamic_pointer_cast<HAstModuleDeclNode>(node);
                std::shared_ptr<HSymbol> symbol = nullptr;

                symbol = std::make_shared<HModuleSymbol>();
                symbol->Name = moduleNode->Name;
                parent->Children.push_back(symbol);
                symbol->Parent = std::weak_ptr<HSymbol>(parent);

                BuildSymbolTable(node, symbol);

            } else if (node->Type == HAstNodeType::NominalType) {
                auto typeNode = std::dynamic_pointer_cast<HAstTypeNode>(node);

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
            else if (node->Type == HAstNodeType::File) {
                auto fileNode = std::dynamic_pointer_cast<HAstFileNode>(node);

                // Create a symbol
                auto symbol = std::make_shared<HFileSymbol>();
                symbol->Name = fileNode->Name;
                symbol->Parent = std::weak_ptr<HSymbol>(parent);

                if (!fileNode->Children.empty()) {
                    BuildSymbolTable(fileNode, symbol);
                }

                parent->Children.push_back(symbol);
            } else if (node->Type == HAstNodeType::Func) {
                auto funcNode = std::dynamic_pointer_cast<HAstFuncDeclNode>(node);

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
            } else if (node->Type == HAstNodeType::Init) {
                auto initNode = std::dynamic_pointer_cast<HAstInitDeclNode>(node);

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
            } else if (node->Type == HAstNodeType::PropertyDecl) {
                auto declNode = std::dynamic_pointer_cast<HAstPropertyDeclNode>(node);

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
            else if (node->Type == HAstNodeType::VariableDecl) {
                auto declNode = std::dynamic_pointer_cast<HAstVarDeclNode>(node);

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
        std::shared_ptr<HAstNode>& nodes
    ) {
        // First we infer types of the local module only
        InferTypesWithSymbolTable(symbols, nodes);
        // Then we infer types of the imported modules + The Standard Library
        InferImportedTypes(symbols, nodes);
        // Finally we find any unimported types
        // This is used for fixit hints in LSP
        FindUnimportedTypes(symbols, nodes);
    }

    void HTypeck::InferTypesWithSymbolTable(
        const std::shared_ptr<HSymbolTable>& symbols,
        const std::shared_ptr<HAstNode>& nodes
    ) {
        using enum HAstNodeType;

        // Files/Modules only need their children to be inferred
        if (nodes->Type == File || nodes->Type == Module) {
            for(const auto& node: nodes->Children) {
                InferTypesWithSymbolTable(symbols, node);
			}
        } else if (nodes->Type == NominalType || nodes->Type == Func) {
            // Get the body node
            if (nodes->Children.empty()) {
                return;
            }
            auto bodyNode = nodes->Children[0];
            for (const auto& node : bodyNode->Children) {
                InferTypesWithSymbolTable(symbols, node);
            }
        } else if (nodes->Type == PropertyDecl) {
            auto declNode = std::dynamic_pointer_cast<HAstPropertyDeclNode>(nodes);

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
                
                auto foundSymbol = symbols->Find(declNode->TypeNode->Name);

                if (foundSymbol != nullptr) {
                    // We found the symbol, so we can continue
					// We need to check if the symbol is a type or not
					if (foundSymbol->SymbolType != HSymbolType::Class && foundSymbol->SymbolType != HSymbolType::Struct) {
						throw std::runtime_error("Property type is not a class or struct");
                    }
                    else {
                        // Assign the type to the symbol
                        type->Kind = SymbolTypeToNodeType(foundSymbol->SymbolType);
                        // Get the module of the symbol
                        // First we create the scope string for the symbol
                        auto scope = declNode->CreateScopeString();
                        // Then we take the first part of the scope string
                        auto moduleSymbol = scope.front();
                    }
				}
            }
        }
    }

    void HTypeck::InferImportedTypes(
        const std::shared_ptr<HSymbolTable>& symbols,
        const std::shared_ptr<HAstNode>& nodes
    ) {
        // We know that this function always only has a single file node, so we can just take the first one
        auto fileNode = HAstNode::FindNodesWithType(HAstNodeType::File, nodes);

        if(fileNode.empty()) {
			throw std::runtime_error("No file node found in AST");
		}

        // Take the first file node
        auto file = fileNode.front();

        // Get all the import nodes
        auto importNodes = HAstNode::FindNodesWithType(HAstNodeType::Import, file);
        std::vector<std::shared_ptr<HSymbol>> importedModules;

        // For each import node, we need to find the module in the symbol table
        for (const auto& childNode : importNodes) {
            auto importNode = std::dynamic_pointer_cast<HAstImportNode>(childNode);
            
            // Find each part of the import node in the symbol table
            auto parts = splitString(importNode->Name, '.');
            std::shared_ptr<HSymbol> currentSymbol = nullptr;
            std::vector<std::string_view> scope = {};

            // Scope is everything except the last part
            for (size_t i = 0; i < parts.size() - 1; i++) {
				scope.push_back(parts[i]);
			}

            auto importedModuleSymbol = symbols->Find(scope, parts.back());

            if (importedModuleSymbol == nullptr) {
				throw std::runtime_error("Imported module not found in symbol table");
			}

            importedModules.push_back(importedModuleSymbol);
		}

        // Now we have all imported modules. Check if they contain any types that refer to in the local module

        // Create a mini symbol table for the imported module
        auto importTable = std::make_shared<HSymbolTable>();

        for (const auto& importedModule : importedModules) {
            importTable->Append(importedModule);
		}

        // Infer types for the imported modules
		InferTypesWithSymbolTable(importTable, nodes);
    }

    void HTypeck::FindUnimportedTypes(
        const std::shared_ptr<HSymbolTable>&,
        std::shared_ptr<HAstNode>& nodes
    ) {

    }

    std::shared_ptr<HAstTypeNode> HTypeck::CalculateExpressionType(
        const std::shared_ptr<HAstNode>& node,
        const std::shared_ptr<HSymbol>& symbol
    ) {
        // TODO: Implement this
        
        // If we have just a literal node, we can return the type of the literal immediately
        if (node->Type == HAstNodeType::Literal) {
			auto literalNode = std::dynamic_pointer_cast<HAstLiteralNode>(node);
		}

        return nullptr;
    }

    void HTypeck::MergeModuleWithTable(
        const std::shared_ptr<HSymbolTable>& table,
        const std::shared_ptr<HSymbol>& moduleSymbol
    ) {
        auto foundSymbol = table->Find(moduleSymbol->Name);

		if (foundSymbol == nullptr) {
			table->Append(moduleSymbol);
		} else {
            for (const auto& child : moduleSymbol->Children) {
                foundSymbol->AppendChild(child);
            }
		}
    }
}