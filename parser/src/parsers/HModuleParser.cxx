#include "parser/parsers/HModuleParser.hxx"
#include "parser/HAstNode.hxx"
#include "parser/nodes/HAstModuleDeclNode.hxx"
#include <lexer/HToken.hxx>
#include <core/HCompilerError.hxx>
#include <string_view>
#include <vector>

namespace Hyve::Parser {
	// NOSONAR disable brain-overload
	HModuleParser::HModuleParser(
		const std::shared_ptr<Core::HErrorHandler>& errorHandler,
		const std::shared_ptr<HClassParser>& classParser,
		const std::shared_ptr<HEnumParser>& enumParser,
		const std::shared_ptr<HFuncParser>& funcParser,
		const std::shared_ptr<HPropertyParser>& propParser,
		const std::shared_ptr<HProtocolParser>& protocolParser,
		const std::shared_ptr<HPrototypeParser>& prototypeParser,
		const std::shared_ptr<HStructParser>& structParser,
		const std::shared_ptr<HVariableParser>& varParser
	) : _errorHandler(errorHandler),
		_classParser(classParser),
		_enumParser(enumParser),
		_funcParser(funcParser),
		_propParser(propParser),
		_protocolParser(protocolParser),
		_prototypeParser(prototypeParser),
		_structParser(structParser),
		_varParser(varParser) { }

	std::shared_ptr<HAstNode> HModuleParser::Parse(
		std::string_view fileName,
		std::vector<Lexer::HToken>& tokens
	) {
		using enum Lexer::HTokenType;
		using enum Core::HCompilerError::ErrorCode;

		auto moduleNode = std::make_shared<HAstModuleDeclNode>();

		auto token = Consume(MODULE);

		moduleNode->Name = token.Value;

		token = ParseNextNonLN();
		token = Peek();

		while (token.Type != END_OF_FILE) {
			if (IsClass()) {
				moduleNode->Children.push_back(_classParser->Parse(fileName, tokens));
			} else if (IsFunc()) {
				moduleNode->Children.push_back(_funcParser->Parse(fileName, tokens));
			} else if(IsEnum()) {
				moduleNode->Children.push_back(_enumParser->Parse(fileName, tokens));
			} else if (IsProtocol()) {
				moduleNode->Children.push_back(_protocolParser->Parse(fileName, tokens));
			} else if(IsPrototype()) {
				moduleNode->Children.push_back(_prototypeParser->Parse(fileName, tokens));
			} else if (IsStruct()) {
				moduleNode->Children.push_back(_structParser->Parse(fileName, tokens));
			} else {
				HandleErrorCase();
			}
			token = ParseNextNonLN();
			token = Peek();
		}

		return moduleNode;
	}

	void HModuleParser::HandleErrorCase() {
		using enum Lexer::HTokenType;
		using enum Core::HCompilerError::ErrorCode;

		// We have an invalid token. Check which one for better error messages
		auto token = Peek();

		if (token.Type == MODULE) {
			_errorHandler->AddError(INVALID_MODULE_DECLARATION, token.FileName, token.Line);
		}
	}
}