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
		const std::shared_ptr<HStatementParser>& statementParser,
		const std::shared_ptr<HStructParser>& structParser,
		const std::shared_ptr<HVariableParser>& varParser
	) : _errorHandler(errorHandler),
		_classParser(classParser),
		_enumParser(enumParser),
		_funcParser(funcParser),
		_propParser(propParser),
		_protocolParser(protocolParser),
		_prototypeParser(prototypeParser),
		_stmtParser(statementParser),
		_structParser(structParser),
		_varParser(varParser) { }

	std::shared_ptr<HAstNode> HModuleParser::Parse(Lexer::HTokenStream& stream) {
		using enum Lexer::HTokenType;
		using enum Core::HCompilerError::ErrorCode;

		auto moduleNode = std::make_shared<HAstModuleDeclNode>();

		auto token = stream.Consume(MODULE);

		token = stream.Consume(IDENTIFIER);
		moduleNode->Name = token.Value;

		token = stream.PeekUntilNonLineBreak();

		while (token.Type != END_OF_FILE) {
			if (IsClass(stream)) {
				moduleNode->Children.push_back(_classParser->Parse(stream));
			} else if (IsFunc(stream)) {
				moduleNode->Children.push_back(_funcParser->Parse(stream));
			} else if(IsEnum(stream)) {
				moduleNode->Children.push_back(_enumParser->Parse(stream));
			} else if (IsProtocol(stream)) {
				moduleNode->Children.push_back(_protocolParser->Parse(stream));
			} else if(IsPrototype(stream)) {
				moduleNode->Children.push_back(_prototypeParser->Parse(stream));
			} else if (IsStruct(stream)) {
				moduleNode->Children.push_back(_structParser->Parse(stream));
			} else if(IsVariable(stream)) {
				moduleNode->Children.push_back(_varParser->Parse(stream));
			} else if (IsStatement(stream)) {
				moduleNode->Children.push_back(_stmtParser->Parse(stream));
			} else {
				HandleErrorCase(stream);
				
				return moduleNode;
			}
			token = stream.PeekUntilNonLineBreak();
		}

		return moduleNode;
	}

	void HModuleParser::HandleErrorCase(Lexer::HTokenStream& stream) {
		using enum Lexer::HTokenType;
		using enum Core::HCompilerError::ErrorCode;

		// We have an invalid token. Check which one for better error messages
		auto token = stream.Consume();

		if (token.Type == MODULE) {
			_errorHandler->AddError(INVALID_MODULE_DECLARATION, token.FileName, token.Line);
		}
	}
}