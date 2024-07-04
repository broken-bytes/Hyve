#pragma once

#include <lexer/HLexer.hxx>
#include <parser/IHParser.hxx>
#include <typeck/HTypeck.hxx>
#include <generator/HGenerator.hxx>
#include <map>
#include <memory>
#include <string>
#include <vector>

namespace Hyve {
	struct HCompilerArgument;

	class HCompiler {
	public:
		HCompiler();
		~HCompiler() = default;

		void Compile(
			const std::vector<std::string>& files, 
			std::vector<HCompilerArgument> arguments
		);

	private:
		std::shared_ptr<Lexer::HLexer> _lexer;
		std::shared_ptr<Parser::IHParser> _parser;
		std::shared_ptr<Typeck::HTypeck> _typeck;
		std::shared_ptr<Generator::HGenerator> _generator;

		std::string LoadSourceFile(const std::string& file) const;
	};
}