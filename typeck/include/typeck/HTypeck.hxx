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
        /// <param name="code">The node to use</param>
        /// <returns>The symbol table</returns>
        [[nodiscard]] std::shared_ptr<HSymbol> BuildTypeTable(
            const std::shared_ptr<Hyve::Parser::HAstNode>& ast,
            const std::shared_ptr<HSymbol>& parent = nullptr
        );

    private:
    };
}