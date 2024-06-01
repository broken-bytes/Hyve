#pragma once

#include "parser/HAstNode.hxx"
#include "parser/HAstOperatorType.hxx"
#include "parser/HParserContext.hxx"
#include "parser/nodes/HAstLiteralNode.hxx"
#include "parser/nodes/HAstTypeNode.hxx"
#include <lexer/HToken.hxx>
#include <lexer/HTokenStream.hxx>
#include <memory>
#include <string>

namespace Hyve::Parser {
	class IHParser {
	public:
		IHParser() = default;
		virtual ~IHParser() = 0;
		[[nodiscard]] virtual std::shared_ptr<HAstNode> Parse(Lexer::HTokenStream& stream) = 0;

	protected:
		/// <summary>
		/// Consumes all tokens until a token with the specified type is found.
		/// </summary>
		/// <param name=""></param>
		void Panic(Lexer::HTokenStream& stream, Lexer::HTokenType type) const;
		void Panic(Lexer::HTokenStream& stream, Lexer::HTokenFamily family) const;
		[[nodiscard]] bool CanStartStatement(Lexer::HTokenStream& stream) const;
		[[nodiscard]] bool CanStartExpression(Lexer::HTokenStream& stream) const;
		[[nodiscard]] bool IsExpression(Lexer::HTokenStream& stream) const;
		[[nodiscard]] bool IsStatement(Lexer::HTokenStream& stream) const;
		[[nodiscard]] bool IsClass(Lexer::HTokenStream& stream) const;
		[[nodiscard]] bool IsEnum(Lexer::HTokenStream& stream) const;
		[[nodiscard]] bool IsFunc(Lexer::HTokenStream& stream) const;
		[[nodiscard]] bool IsProperty(Lexer::HTokenStream& stream) const;
		[[nodiscard]] bool IsProtocol(Lexer::HTokenStream& stream) const;
		[[nodiscard]] bool IsPrototype(Lexer::HTokenStream& stream) const;
		[[nodiscard]] bool IsStruct(Lexer::HTokenStream& stream) const;
		[[nodiscard]] bool IsVariable(Lexer::HTokenStream& stream) const;
		[[nodiscard]] std::int8_t GetOperatorPrecedence(HAstOperatorType type) const;
		[[nodiscard]] bool IsStatementOperator(HAstOperatorType type) const;
		[[nodiscard]] bool IsUnaryOperator(HAstOperatorType type) const;
		[[nodiscard]] std::shared_ptr<HAstExpressionNode> ParseLiteral(Lexer::HTokenStream& stream) const;
		[[nodiscard]] std::shared_ptr<HAstLiteralNode> ParseString(std::string_view literal) const;
		[[nodiscard]] std::shared_ptr<HAstTypeNode> ParseType(
			Lexer::HTokenStream& stream,
			std::shared_ptr<HAstTypeNode> parent = nullptr
		);
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