#pragma once

#include "typeck/HSymbol.hxx"
#include <parser/HAstNode.hxx>

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
        std::shared_ptr<HSymbol> BuildTypeTable(
            const std::shared_ptr<Hyve::Parser::HAstNode>& ast,
            const std::shared_ptr<HSymbol>& parent
        );

        void InferTypes(
            const std::vector<std::shared_ptr<HSymbol>>& symbols, 
            const std::shared_ptr<Parser::HAstNode>& ast
        );
    };
}