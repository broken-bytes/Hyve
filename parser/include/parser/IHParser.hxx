#pragma once

#include "parser/HAstNode.hxx"
#include "parser/HAstOperatorType.hxx"
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
		void SetTokens(const std::vector<Lexer::HToken>& tokens);
		[[nodiscard]] bool CanStartStatement();
		[[nodiscard]] bool CanStartExpression();
		[[nodiscard]] bool IsExpression();
		[[nodiscard]] bool IsStatement();
		[[nodiscard]] bool IsClass();
		[[nodiscard]] bool IsEnum();
		[[nodiscard]] bool IsFunc();
		[[nodiscard]] bool IsProtocol();
		[[nodiscard]] bool IsPrototype();
		[[nodiscard]] bool IsStruct();
		[[nodiscard]] std::int8_t GetOperatorPrecedence(HAstOperatorType type);
		[[nodiscard]] bool IsStatementOperator(HAstOperatorType type);
		[[nodiscard]] bool IsUnaryOperator(HAstOperatorType type);
		[[nodiscard]] Lexer::HToken& Consume(Lexer::HTokenFamily expected, std::string_view error);
		[[nodiscard]] Lexer::HToken& Consume(Lexer::HTokenType expected, std::string_view error);
		[[maybe_unused]] Lexer::HToken& Consume();
		[[nodiscard]] Lexer::HToken ParseNextNonLN();
		[[nodiscard]] std::shared_ptr<HAstExpressionNode> ParseLiteral();
		[[nodiscard]] std::shared_ptr<HAstLiteralNode> ParseString(std::string_view literal);
		[[nodiscard]] std::shared_ptr<HAstTypeNode> ParseType(std::shared_ptr<HAstTypeNode> parent = nullptr);
		[[nodiscard]] Lexer::HToken Peek();
		[[nodiscard]] std::vector<Lexer::HToken> Peek(uint8_t offset);

	private:
		std::vector<Lexer::HToken> _tokens;
		uint64_t _tokenIndex;
	};
}