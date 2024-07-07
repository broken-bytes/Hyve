#pragma once

#include "parser/HParserContext.hxx"
#include <memory>
#include <string>
#include <vector>

namespace Hyve {
	namespace AST {
		struct HAstNode;
		struct HAstExpressionNode;
		struct HAstLiteralNode;
		struct HAstTypeNode;
		enum class HAstOperatorType;
	}

	namespace Lexer {
		struct HToken;
		enum class HTokenFamily;
		enum class HTokenType;
		class HTokenStream;
	}

	namespace Core {
		enum class HAccessLevel;
	}
}

namespace Hyve::Parser {
	class IHParser {
	public:
		IHParser() = default;
		virtual ~IHParser() = 0;
		[[nodiscard]] virtual std::shared_ptr<AST::HAstNode> Parse(Lexer::HTokenStream& stream) = 0;

	protected:
		/// <summary>
		/// Consumes all tokens until a token with the specified type is found.
		/// </summary>
		/// <param name=""></param>
		void Panic(Lexer::HTokenStream& stream, Lexer::HTokenType type) const;
		void Panic(Lexer::HTokenStream& stream, Lexer::HTokenFamily family) const;
		[[nodiscard]] bool CanStartStatement(Lexer::HTokenStream& stream) const;
		[[nodiscard]] bool CanBeInExpression(Lexer::HTokenStream& stream) const;
		[[nodiscard]] bool IsAccessLevel(Lexer::HTokenStream& stream) const;
		[[nodiscard]] bool IsExpression(Lexer::HTokenStream& stream) const;
		[[nodiscard]] bool IsStatement(Lexer::HTokenStream& stream) const;
		[[nodiscard]] bool IsClass(Lexer::HTokenStream& stream) const;
		[[nodiscard]] bool IsEnum(Lexer::HTokenStream& stream) const;
		[[nodiscard]] bool IsFunc(Lexer::HTokenStream& stream) const;
		[[nodiscard]] bool IsInit(Lexer::HTokenStream& stream) const;
		[[nodiscard]] bool IsProperty(Lexer::HTokenStream& stream) const;
		[[nodiscard]] bool IsContract(Lexer::HTokenStream& stream) const;
		[[nodiscard]] bool IsPrototype(Lexer::HTokenStream& stream) const;
		[[nodiscard]] bool IsStruct(Lexer::HTokenStream& stream) const;
		[[nodiscard]] bool IsVariable(Lexer::HTokenStream& stream) const;
		[[nodiscard]] std::int8_t GetOperatorPrecedence(AST::HAstOperatorType type) const;
		[[nodiscard]] bool IsOperator(Lexer::HTokenStream& stream) const;
		[[nodiscard]] bool IsStatementOperator(AST::HAstOperatorType type) const;
		[[nodiscard]] bool IsUnaryOperator(AST::HAstOperatorType type) const;
		[[nodiscard]] bool IsBinaryOperator(AST::HAstOperatorType type) const;
		[[nodiscard]] AST::HAstOperatorType GetOperatorType(const Lexer::HToken& token) const;
		[[nodiscard]] std::shared_ptr<AST::HAstExpressionNode> ParseLiteral(Lexer::HTokenStream& stream) const;
		[[nodiscard]] std::shared_ptr<AST::HAstLiteralNode> ParseString(std::string_view literal) const;
		[[nodiscard]] Core::HAccessLevel ParseAccessLevel(Lexer::HTokenStream& stream) const;
		[[nodiscard]] std::shared_ptr<AST::HAstTypeNode> ParseType(
			Lexer::HTokenStream& stream,
			std::shared_ptr<AST::HAstTypeNode> parent = nullptr
		);
		[[nodiscard]] HParserContext GetContext() const;
		void SetContext(HParserContext ctx);

	private:
		std::string _file;
		uint64_t _tokenIndex;
		HParserContext _context;
	};

	std::unique_ptr<IHParser> Create();
}

inline Hyve::Parser::IHParser::~IHParser() = default;