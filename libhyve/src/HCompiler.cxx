#include "libhyve/HCompiler.hxx"
#include <parser/IHParser.hxx>
#include <fstream>

namespace Hyve {
    HCompiler::HCompiler() {
        _lexer = std::make_shared<Lexer::HLexer>();
        _parser = Parser::Create();
        _typeck = std::make_shared<Typeck::HTypeck>();
    }

	void HCompiler::Compile(const std::vector<std::string>& files) {
        std::vector<std::shared_ptr<Typeck::HSymbol>> symbols = {};
        std::vector<std::shared_ptr<Parser::HAstNode>> asts = {};

        for(const auto& file : files) {
			auto source = LoadSourceFile(file);
			auto tokens = _lexer->Tokenize(source, file);
			auto ast = _parser->Parse(tokens);
            asts.push_back(ast);
            auto symbolTable = _typeck->BuildTypeTable(ast, nullptr);
            symbols.push_back(symbolTable);
		}

        // TODO: Merge the symbol tables
        std::shared_ptr<Typeck::HSymbol> symbolTable = {};

        for (auto& ast : asts) {
            _typeck->InferTypes(symbols, ast);
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