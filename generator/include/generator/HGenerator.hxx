#pragma once

#include <memory>
#include <string>
#include <string_view>

namespace Hyve::AST {
	struct HAstNode;
	struct HAstExpressionNode;
	struct HAstFuncDeclNode;
	struct HAstTypeNode;
}

namespace llvm {
	class ConstantData;
	class Function;
	class LLVMContext;
	class Module;
	class Type;
}

namespace Hyve::Generator {
	class HGenerator {
	public:
		HGenerator() = default;
		~HGenerator() = default;

		std::string GenerateIR(std::string_view fileName, std::shared_ptr<AST::HAstNode> nodes) const;

		llvm::Function* GenerateFunction(llvm::LLVMContext& context, llvm::Module* llvmModule, std::shared_ptr<AST::HAstFuncDeclNode> func) const;
		llvm::Type* GetType(llvm::LLVMContext& context, std::shared_ptr<AST::HAstTypeNode> type) const;
		llvm::ConstantData* GetConstantData(llvm::LLVMContext& context, std::shared_ptr<AST::HAstExpressionNode> node) const;
	};
}