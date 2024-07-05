#pragma once

#include "typeck/HSymbol.hxx"
#include "typeck/HSymbolTable.hxx"
#include "typeck/symbols/HStructSymbol.hxx"
#include <parser/HAstNode.hxx>
#include <parser/nodes/HAstTypeNode.hxx>

#include <memory>
#include <string>
#include <vector>

namespace Hyve::Typeck {
    class HTypeck {
    public:
        HTypeck();
        /// <summary>
        /// Builds the type table from a given AST node.
        /// </summary>
        /// <param name="ast">The node to use</param>
        /// <param name="parent">The parent symbol to use</param>
        std::shared_ptr<HSymbol> BuildSymbolTable(
            const std::shared_ptr<Hyve::Parser::HAstNode>& ast,
            const std::shared_ptr<HSymbol>& parent
        );

        std::shared_ptr<HSymbolTable> MergeSymbols(
			const std::vector<std::shared_ptr<HSymbol>>& symbolTables
		);

        void InferTypes(
			const std::shared_ptr<HSymbolTable>&,
			std::shared_ptr<Parser::HAstNode>& nodes
		);

        void InferTypesWithSymbolTable(
            const std::shared_ptr<HSymbolTable>&,
            const std::shared_ptr<Parser::HAstNode>& nodes
        );

        void InferImportedTypes(
            const std::shared_ptr<HSymbolTable>&,
            const std::shared_ptr<Parser::HAstNode>& nodes
        );

        void FindUnimportedTypes(
            const std::shared_ptr<HSymbolTable>&,
            std::shared_ptr<Parser::HAstNode>& nodes
        );

    private:
        std::shared_ptr<HSymbol> _builtins;

        std::shared_ptr<Parser::HAstTypeNode> CalculateExpressionType(
			const std::shared_ptr<Parser::HAstNode>& node,
			const std::shared_ptr<HSymbol>& symbol
		);

        void MergeModuleWithTable(
            const std::shared_ptr<HSymbolTable>& table,
            const std::shared_ptr<HSymbol>& moduleSymbol
		);
    };
}