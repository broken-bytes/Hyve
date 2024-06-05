#include "parser/HParser.hxx"
#include "parser/nodes/HAstAssignmentNode.hxx"
#include "parser/nodes/HAstBinaryExpressionNode.hxx"
#include "parser/nodes/HAstUnaryExpressionNode.hxx"
#include "parser/nodes/HAstStatementNode.hxx"
#include "parser/nodes/HAstReturnNode.hxx"
#include "parser/nodes/HAstFileNode.hxx"
#include "parser/nodes/HAstModuleDeclNode.hxx"
#include "parser/nodes/HAstFuncCallNode.hxx"
#include "parser/nodes/HAstFuncDeclNode.hxx"
#include "parser/nodes/HAstTypeNode.hxx"
#include "parser/nodes/HAstArrayNode.hxx"
#include "parser/nodes/HAstMemberAccessNode.hxx"
#include "parser/nodes/HAstVarDeclNode.hxx"
#include "parser/nodes/HAstExpressionNode.hxx"
#include "parser/nodes/HAstPropAccessNode.hxx"
#include "parser/nodes/HAstLiteralNode.hxx"
#include "parser/nodes/HAstClassNode.hxx"
#include "parser/nodes/HAstClassBodyNode.hxx"
#include "parser/nodes/HAstPrototypeNode.hxx"
#include "parser/nodes/HAstPrototypeBodyNode.hxx"
#include "parser/nodes/HAstProtocolNode.hxx"
#include "parser/nodes/HAstProtocolBodyNode.hxx"
#include "parser/nodes/HAstStructNode.hxx"
#include "parser/nodes/HAstStructBodyNode.hxx"
#include "parser/nodes/HAstInitNode.hxx"
#include <lexer/HToken.hxx>
#include <lexer/HTokenType.hxx>
#include <core/HAccessLevel.hxx>
#include <core/HCompilerError.hxx>

#include <sstream>

namespace Hyve::Parser {
    HParser::HParser(
        const std::shared_ptr<Core::HErrorHandler>& errorHandler,
        const std::shared_ptr<HModuleParser> moduleParser
    ) : _errorHandler(errorHandler), _moduleParser(moduleParser) {
	}

    std::shared_ptr<HAstNode> HParser::Parse(Lexer::HTokenStream& stream) {
        auto token = stream.Peek();

        auto ast = std::make_shared<HAstFileNode>();
        ast->Name = token.FileName;
        ast->Type = HAstNodeType::File;
        
        token = stream.PeekUntilNonLineBreak();

        // A file may start with imports, so parse them first
        while (token.Type == Lexer::HTokenType::IMPORT) {
            ast->Children.push_back(ParseImport(stream));
		}

        // Every file should start with a module declaration(or after the imports),
        // so we use the module parser
        ast->Children.push_back(_moduleParser->Parse(stream));

        return ast;
    }

    std::shared_ptr<HAstImportNode> HParser::ParseImport(Lexer::HTokenStream& stream) const {
        using enum Lexer::HTokenType;
        using enum Core::HCompilerError::ErrorCode;
        auto importNode = std::make_shared<HAstImportNode>();

        auto token = stream.Consume(IMPORT);
		
        if (token.Type != IMPORT) {
            throw Core::HCompilerError(UnexpectedToken, token.FileName, token.Line);
		}

		token = stream.Consume(IDENTIFIER);
		
        if (token.Type != IDENTIFIER) {
            throw Core::HCompilerError(UnexpectedToken, token.FileName, token.Line);
        }

        importNode->Target = token.Value;
		
        return importNode;
    }
}
