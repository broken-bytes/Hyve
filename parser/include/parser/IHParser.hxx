#pragma once

#include "parser/HAstNode.hxx"
#include "parser/HAstOperatorType.hxx"
#include "parser/HParserContext.hxx"
#include "parser/nodes/HAstLiteralNode.hxx"
#include "parser/nodes/HAstTypeNode.hxx"
#include <lexer/HToken.hxx>
#include <memory>
#include <string>

namespace Hyve::Parser {
	class IHParser {
	public:
		IHParser() = default;
		virtual ~IHParser() = 0;
		[[nodiscard]] virtual std::shared_ptr<HAstNode> Parse(
			std::string_view fileName,
			std::vector<Lexer::HToken>& tokens
		) = 0;

	protected:
		void SetFile(std::string_view file);
		void SetTokens(const std::vector<Lexer::HToken>& tokens);
		[[nodiscard]] bool CanStartStatement();
		[[nodiscard]] bool CanStartExpression();
		[[nodiscard]] bool IsExpression();
		[[nodiscard]] bool IsStatement();
		[[nodiscard]] bool IsClass();
		[[nodiscard]] bool IsEnum();
		[[nodiscard]] bool IsFunc();
		[[nodiscard]] bool IsProperty();
		[[nodiscard]] bool IsProtocol();
		[[nodiscard]] bool IsPrototype();
		[[nodiscard]] bool IsStruct();
		[[nodiscard]] bool IsVariable();
		[[nodiscard]] std::int8_t GetOperatorPrecedence(HAstOperatorType type) const;
		[[nodiscard]] bool IsStatementOperator(HAstOperatorType type) const;
		[[nodiscard]] bool IsUnaryOperator(HAstOperatorType type) const;
		[[nodiscard]] Lexer::HToken& Consume(Lexer::HTokenFamily expected);
		[[nodiscard]] Lexer::HToken& Consume(Lexer::HTokenType expected);
		[[maybe_unused]] Lexer::HToken& Consume();
		[[nodiscard]] Lexer::HToken ParseNextNonLN();
		[[nodiscard]] std::shared_ptr<HAstExpressionNode> ParseLiteral();
		[[nodiscard]] std::shared_ptr<HAstLiteralNode> ParseString(std::string_view literal) const;
		[[nodiscard]] std::shared_ptr<HAstTypeNode> ParseType(
			std::shared_ptr<HAstTypeNode> parent = nullptr
		);
		[[nodiscard]] Lexer::HToken Peek() const;
		[[nodiscard]] std::vector<Lexer::HToken> Peek(uint8_t offset) const;
		[[nodiscard]] HParserContext GetContext() const;
		void SetContext(HParserContext ctx);

	private:
		std::string _file;
		std::vector<Lexer::HToken> _tokens;
		uint64_t _tokenIndex;
		HParserContext _context;
	};

	std::unique_ptr<IHParser> Create();
}

inline Hyve::Parser::IHParser::~IHParser() = default;