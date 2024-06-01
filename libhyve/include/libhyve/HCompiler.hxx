#pragma once

#include <lexer/HLexer.hxx>
#include <parser/IHParser.hxx>
#include <typeck/HTypeck.hxx>
#include <memory>
#include <string>
#include <vector>

namespace Hyve {
	class HCompiler {
	public:
		HCompiler();
		~HCompiler() = default;

		void Compile(const std::vector<std::string>& files);

	private:
		std::shared_ptr<Lexer::HLexer> _lexer;
		std::shared_ptr<Parser::IHParser> _parser;
		std::shared_ptr<Typeck::HTypeck> _typeck;

		std::string LoadSourceFile(const std::string& file) const;
	};
}