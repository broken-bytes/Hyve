#include "parser/HParser.hxx"
#include <ast/nodes/HAstAssignmentNode.hxx>
#include <ast/nodes/HAstBinaryExpressionNode.hxx>
#include <ast/nodes/HAstUnaryExpressionNode.hxx>
#include <ast/nodes/HAstStatementNode.hxx>
#include <ast/nodes/HAstReturnNode.hxx>
#include <ast/nodes/HAstFileNode.hxx>
#include <ast/nodes/HAstModuleDeclNode.hxx>
#include <ast/nodes/HAstFuncCallNode.hxx>
#include <ast/nodes/HAstFuncDeclNode.hxx>
#include <ast/nodes/HAstTypeNode.hxx>
#include <ast/nodes/HAstArrayNode.hxx>
#include <ast/nodes/HAstMemberAccessNode.hxx>
#include <ast/nodes/HAstImportNode.hxx>
#include <ast/nodes/HAstVarDeclNode.hxx>
#include <ast/nodes/HAstExpressionNode.hxx>
#include <ast/nodes/HAstPropAccessNode.hxx>
#include <ast/nodes/HAstLiteralNode.hxx>
#include <ast/nodes/HAstStructNode.hxx>
#include <ast/nodes/HAstStructBodyNode.hxx>
#include <ast/nodes/HAstInitNode.hxx>
#include <lexer/HToken.hxx>
#include <lexer/HTokenType.hxx>
#include <core/HAccessLevel.hxx>
#include <core/HCompilerError.hxx>
#include <sstream>

namespace Hyve::Parser {
    using namespace AST;

    HParser::HParser(
        const std::shared_ptr<Core::HErrorHandler>& errorHandler,
        const std::shared_ptr<HModuleParser> moduleParser
    ) : _errorHandler(errorHandler), _moduleParser(moduleParser) {
	}

    std::shared_ptr<HAstNode> HParser::Parse(Lexer::HTokenStream& stream) {
        auto token = stream.Peek();

        auto file = std::make_shared<HAstFileNode>();
        file->Name = token.FileName;

        token = stream.PeekUntilNonLineBreak();

        // A file may start with imports, so parse them first
        while (token.Type == Lexer::HTokenType::IMPORT) {
            file->Children.push_back(ParseImport(stream));
            token = stream.PeekUntilNonLineBreak();
		}

        // Every file should start with a module declaration(or after the imports),
        // so we use the module parser
        if (auto mod = _moduleParser->Parse(stream); mod != nullptr) {
            // We need to set all children of the module to have the file as their parent
            // We also need to make sure we get the deepest module
            // This is because the module parser will return the top level module

            auto current = mod;
            while (!current->Children.empty()) {
				auto moduleNode = std::dynamic_pointer_cast<HAstModuleDeclNode>(current->Children[0]);
                if (moduleNode == nullptr) {
                    break;
                }

                current = moduleNode;
            }

            for (const auto& child : current->Children) {
				child->Parent = file;
                file->Children.push_back(child);
			}

            // Now set only the file as a child of the module
            // We do this because each module can have multiple files
            // but each file can only have one module
            // Additionally, definitions aren't technically children of the module
            current->Children = {};
            current->Children.push_back(file);
            file->Parent = current;

            return mod;
        }

        return nullptr;
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

        importNode->Name = token.Value;

        // Imports may use submodules, so we need to take that into account
        token = stream.PeekUntilNonLineBreak();

        while (token.Type == DOT) {
			stream.Consume(DOT);
			token = stream.Consume(IDENTIFIER);
			importNode->Name += "." + token.Value;
			token = stream.PeekUntilNonLineBreak();
		}
		
        return importNode;
    }
}
