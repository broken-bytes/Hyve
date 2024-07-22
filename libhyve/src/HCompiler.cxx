#include "libhyve/HCompiler.hxx"
#include <libhyve/HCompilerArgument.hxx>
#include <parser/IHParser.hxx>
#include <fstream>
#include <map>
#include <memory>
#include <vector>

// TESTING ONLY
#include <generator/HGenerator.hxx>

namespace Hyve {
    HCompiler::HCompiler() {
        _lexer = Lexer::HLexer::Create();
        _parser = Parser::Create();
        _typeck = std::make_shared<Typeck::HTypeck>();
        _generator = std::make_shared<Generator::HGenerator>();
    }

    void HCompiler::Compile(
        const std::vector<std::string>& files, 
        const std::vector<HCompilerArgument>& arguments
    ) {
        std::map<std::string_view, std::shared_ptr<Typeck::HSymbol>> symbols = {};
        std::map<std::string_view, std::shared_ptr<AST::HAstNode>> asts = {};

        for(const auto& file : files) {
		    auto source = LoadSourceFile(file);
		    auto tokens = _lexer->Tokenize(source, file);
		    auto ast = _parser->Parse(tokens);
            asts[file] = ast;
            auto symbolTable = _typeck->BuildSymbolTable(ast, nullptr);

            symbols[file] = symbolTable;
	    }

        auto symbolTable = _typeck->MergeSymbols(
            std::vector<std::shared_ptr<Typeck::HSymbol>>{
                std::ranges::begin(symbols | std::views::values), std::ranges::end(symbols | std::views::values)
            }
        );

        for (auto& ast : asts) {
            _typeck->InferTypes(symbolTable, ast.second);
        }

        for (auto& ast : asts) {
            _generator->GenerateIR(ast.first, ast.second);
        }
	}

	std::string HCompiler::LoadSourceFile(const std::string& file) const {
        std::ifstream fileStream(file, std::ios::binary | std::ios::ate);

        if (!fileStream) {
            throw std::runtime_error("Cannot open file: " + file);
        }

        auto fileSize = fileStream.tellg();
        std::string fileContent(fileSize, '\0');
        fileStream.seekg(0);
        fileStream.read(&fileContent[0], fileSize);

        return fileContent;
	}
}