#include "parser/parsers/HModuleParser.hxx"
#include <ast/HAstNode.hxx>
#include <ast/nodes/HAstModuleDeclNode.hxx>
#include <lexer/HToken.hxx>
#include <core/HCompilerError.hxx>
#include <string_view>
#include <vector>

namespace Hyve::Parser {
	using namespace AST;

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
		using enum Lexer::HTokenFamily;
		using enum Core::HCompilerError::ErrorCode;
		
		auto rootModule = std::make_shared<HAstModuleDeclNode>();

		auto token = stream.Consume(MODULE);

		token = stream.Consume(IDENTIFIER);
		rootModule->Name = token.Value;

		// We may have nested modules.
		// We keep parsing until we reach anything other than a dot followed by an identifier
		while(stream.Peek().Type == DOT) {
			token = stream.Consume(DOT);
			token = stream.PeekUntilNonLineBreak();
			
			if (token.Type == IDENTIFIER) {
				token = stream.Consume(IDENTIFIER);
				auto moduleNode = std::make_shared<HAstModuleDeclNode>();
				moduleNode->Name = token.Value;

				// Get the deepest module node
				auto currentModule = rootModule;
				while (!currentModule->Children.empty()) {
					currentModule = std::static_pointer_cast<HAstModuleDeclNode>(currentModule->Children.back());
				}

				moduleNode->Parent = currentModule;
				currentModule->Children.push_back(moduleNode);

			} else {
				_errorHandler->AddError(INVALID_MODULE_DECLARATION, token.FileName, token.Line);
				Panic(stream, KEYWORD);
				token = stream.PeekUntilNonLineBreak();
			}
		}

		token = stream.PeekUntilNonLineBreak();

		// Get the deepest module node
		auto moduleNode = rootModule;
		while (!moduleNode->Children.empty()) {
			moduleNode = std::static_pointer_cast<HAstModuleDeclNode>(moduleNode->Children.back());
		}

		auto tokens = stream.Peek(2);

		while (token.Type != END_OF_FILE) {
			if (IsClass(stream)) {
				moduleNode->Children.push_back(_classParser->Parse(stream));
			} else if (IsFunc(stream)) {
				moduleNode->Children.push_back(_funcParser->Parse(stream));
			} else if(IsEnum(stream)) {
				moduleNode->Children.push_back(_enumParser->Parse(stream));
			} else if (IsContract(stream)) {
				moduleNode->Children.push_back(_protocolParser->Parse(stream));
			} else if(IsPrototype(stream)) {
				moduleNode->Children.push_back(_prototypeParser->Parse(stream));
			} else if (IsStruct(stream)) {
				moduleNode->Children.push_back(_structParser->Parse(stream));
			} else if(IsVariable(stream)) {
				moduleNode->Children.push_back(_varParser->Parse(stream));
			} else if (IsStatement({ tokens.front(), tokens.back() })) {
				moduleNode->Children.push_back(_stmtParser->Parse(stream));
			} else {
				HandleErrorCase(stream);
				
				return rootModule;
			}
			// Make module node the parent of the class node
			moduleNode->Children.back()->Parent = moduleNode;
			token = stream.PeekUntilNonLineBreak();
		}

		return rootModule;
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