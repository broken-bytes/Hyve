#include "parser/parsers/HModuleParser.hxx"
#include "parser/HAstNode.hxx"
#include "parser/nodes/HAstModuleDeclNode.hxx"
#include <lexer/HToken.hxx>
#include <core/HCompilerError.hxx>
#include <string_view>
#include <vector>

namespace Hyve::Parser {
	std::shared_ptr<HAstNode> HModuleParser::Parse(
		std::string_view source, 
		std::vector<Lexer::HToken>& tokens
	) {
		using enum Lexer::HTokenType;
		using enum Core::HCompilerError::ErrorCode;

		auto moduleNode = std::make_shared<HAstModuleDeclNode>();

		auto token = Consume(MODULE, "Expected module at file root");

		moduleNode->Name = token.Value;

		auto token = ParseNextNonLN();
		token = Peek();

		if(IsClass()) {
			moduleNode->Children.push_back(_classParser->Parse(source, tokens));
		}

		return moduleNode;
	}
}