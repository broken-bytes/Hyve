#pragma once

#include "typeck/HSymbol.hxx"
#include "typeck/HSymbolTable.hxx"
#include "typeck/symbols/HStructSymbol.hxx"
#include <memory>
#include <string>
#include <vector>

namespace Hyve::AST {
	struct HAstNode;
    struct HAstTypeNode;
}

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
            const std::shared_ptr<AST::HAstNode>& ast,
            const std::shared_ptr<HSymbol>& parent
        );

        std::shared_ptr<HSymbolTable> MergeSymbols(
			const std::vector<std::shared_ptr<HSymbol>>& symbolTables
		);

        void InferTypes(
			const std::shared_ptr<HSymbolTable>&,
			std::shared_ptr<AST::HAstNode>& nodes
		);

        void InferTypesWithSymbolTable(
            const std::shared_ptr<HSymbolTable>&,
            const std::shared_ptr<AST::HAstNode>& nodes
        );

        void InferImportedTypes(
            const std::shared_ptr<HSymbolTable>&,
            const std::shared_ptr<AST::HAstNode>& nodes
        );

        void FindUnimportedTypes(
            const std::shared_ptr<HSymbolTable>&,
            std::shared_ptr<AST::HAstNode>& nodes
        );

    private:
        std::shared_ptr<HSymbol> _builtins;

        std::shared_ptr<AST::HAstTypeNode> CalculateExpressionType(
			const std::shared_ptr<AST::HAstNode>& node,
			const std::shared_ptr<HSymbol>& symbol
		);

        void MergeModuleWithTable(
            const std::shared_ptr<HSymbolTable>& table,
            const std::shared_ptr<HSymbol>& moduleSymbol
		);
    };
}