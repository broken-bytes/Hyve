#include "generator/HGenerator.hxx"
#include <ast/HAstNode.hxx>
#include <ast/nodes/HAstFuncDeclNode.hxx>
#include <ast/nodes/HAstLiteralNode.hxx>
#include <ast/nodes/HAstModuleDeclNode.hxx>
#include <ast/nodes/HAstReturnNode.hxx>
#include <ast/nodes/HAstUnaryExpressionNode.hxx>
#include <llvm/ADT/APFloat.h>
#include <llvm/IR/Constant.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/ExecutionEngine/ExecutionEngine.h>
#include <llvm/ExecutionEngine/GenericValue.h>
#include <llvm/Target/TargetMachine.h>
#include <llvm/Target/TargetOptions.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/CodeGen/TargetRegisterInfo.h>
#include <llvm/TargetParser/TargetParser.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/CodeGen/Passes.h>
#include <llvm/MC/TargetRegistry.h>
#include <llvm/Support/FileSystem.h>
#include <llvm/Option/Option.h>
#include <llvm/IR/LegacyPassManager.h>
#include <llvm/IRReader/IRReader.h>
#include <llvm/Object/ObjectFile.h>
#include <llvm/IR/PassManager.h>
#include <llvm/Passes/PassBuilder.h>
#include <llvm/TargetParser/Host.h>
#include <llvm/Support/InitLLVM.h>
#include <llvm/Linker/Linker.h>
#include <filesystem>
#include <memory>
#include <optional>

using namespace llvm;

#ifdef HYVE_BOOTSTRAP
std::unique_ptr<Module> LoadLowLevelStandardLibrary(llvm::LLVMContext& context) {
	// Load the low level standard library LLVM IR code and link it with the current module
	SMDiagnostic err;
	auto path = std::filesystem::current_path() / "low_level.bc";
	auto mod = parseIRFile(path.string(), err, context);
	if (!mod) {
		err.print("HyveCompiler", errs());
		return nullptr;
	}

	return mod;
}

void LinkStandardLibrary(llvm::LLVMContext& context, llvm::Module* currentModule) {
	auto lowLevelModule = LoadLowLevelStandardLibrary(context);
	if (!lowLevelModule) {
		return;
	}

	// Link the low level standard library with the current module
	if (Linker::linkModules(*currentModule, std::move(lowLevelModule))) {
		errs() << "Error linking modules\n";

		return;
	}

	// Print the module to stdout
	currentModule->print(outs(), nullptr);
}
#endif

namespace Hyve::Generator {
	using namespace AST;

	std::string HGenerator::GenerateIR(std::string_view fileName, std::shared_ptr<HAstNode> nodes) const {
		// Initialize the target registry etc.
		InitializeNativeTarget();
		InitializeNativeTargetAsmPrinter();
		InitializeNativeTargetAsmParser();

		// Create a context to hold the LLVM constructs
		LLVMContext context;

		// Create a new module
		auto currentModule = std::make_unique<Module>(fileName, context);

		// We can assume that the first node is a module declaration
		auto astModule = std::dynamic_pointer_cast<HAstModuleDeclNode>(nodes);

		std::string moduleName = astModule->Name;

		// Traverse each node and its children(For now we only support function declarations)
		// Note: We can assume that the first child of the module declaration is always the file we processed
		for (const auto& node : astModule->Children.front()->Children) {
			if(node->Type == HAstNodeType::Func) {
				auto function = std::dynamic_pointer_cast<HAstFuncDeclNode>(node);
				GenerateFunction(&context, currentModule.get(), function);
			}
		}

		// Print the module to stdout
		currentModule->print(outs(), nullptr);

		// Set up the target machine
		std::string targetTriple = sys::getDefaultTargetTriple();
		currentModule->setTargetTriple(targetTriple);
		std::string Error;
		const Target* Target = TargetRegistry::lookupTarget(targetTriple, Error);

		if (!Target) {
			errs() << "Error: " << Error;
			return "";
		}

		TargetOptions opt;
		auto RM = std::optional<Reloc::Model>();
		auto targetMachine = std::unique_ptr<TargetMachine>(
			Target->createTargetMachine(targetTriple, "generic", "", opt, RM)
		);

		currentModule->setDataLayout(targetMachine->createDataLayout());

#ifdef HYVE_BOOTSTRAP
		// Link the standard library
		//LinkStandardLibrary(context, currentModule.get());
#endif

		std::error_code EC;
		raw_fd_ostream dest(std::string(fileName) + ".o", EC, sys::fs::OF_None);

		if (EC) {
			errs() << "Could not open file: " << EC.message();
			return "";
		}

		legacy::PassManager pass;
		if (targetMachine->addPassesToEmitFile(pass, dest, nullptr, CodeGenFileType::ObjectFile)) {
			errs() << "TargetMachine can't emit a file of this type";
			return "";
		}

		pass.run(*currentModule);
		dest.flush();

		outs() << "Object file generated successfully\n";

		return "";
	}

	Function* HGenerator::GenerateFunction(LLVMContext* context, Module* llvmModule, std::shared_ptr<AST::HAstFuncDeclNode> func) const {
		// Get the name of the function
		std::string funcName = func->Name;

		// Get the parameters of the function(For now, we only support primitive types)
		// TODO: Add support for complex types, pointers, etc.
		std::vector<Type*> funcArgTypes;

		// Create a function type: ReturnType funcName
		// Get the return type of the function(For now, we only support primitive types)
		// TODO: Add support for complex types, pointers, etc.

		auto returnType = GetType(context, func->ReturnType);

		FunctionType* type = FunctionType::get(returnType, false);

		// Create the main function: int main()
		Function* function = Function::Create(type, Function::ExternalLinkage, func->Name, *llvmModule);

		// Create a basic block and attach it to the main function
		BasicBlock* block = BasicBlock::Create(*context, "entry", function);

		// Now parse each statement of the function one by one and attach it to the block
		IRBuilder<> builder(block);

		// The first children is the block of the function, so we take its children
		for (auto& stmt : func->Children.front()->Children) {
			// Check the type of the statement
			if (stmt->Type == HAstNodeType::ReturnStatement) {
				auto returnStmt = std::dynamic_pointer_cast<HAstReturnNode>(stmt);

				// Check what kind of expression is being returned
				if (returnStmt->Value->ExpressionType == ExpressionType::Literal) {
					// Add the return statement to the block
					builder.CreateRet(GetConstantData(context, returnStmt->Value));
				}
				else if (returnStmt->Value->ExpressionType == ExpressionType::UnaryOperation) {
					auto unaryOp = std::dynamic_pointer_cast<HAstUnaryExpressionNode>(returnStmt->Value);

					// Check the operator
					if (unaryOp->Operator == HAstOperatorType::NEGATE) {
						// Get the value of the expression
						auto value = GetConstantData(context, unaryOp->Operand);

						// Negate the value
						auto negatedValue = builder.CreateNeg(value);

						// Add the return statement to the block
						builder.CreateRet(negatedValue);
					}
				}
				else if (returnStmt->Value->ExpressionType == ExpressionType::BinaryOperation) {

				}
			}
		}

		// Add the function to the module
		llvmModule->getOrInsertFunction(func->Name, type);

		return function;
	}

	llvm::Type* HGenerator::GetType(llvm::LLVMContext* context, std::shared_ptr<AST::HAstTypeNode> type) const {
		// Check for primitive types
		if (type->Kind == HAstTypeKind::Primitive) {
			if (type->Name == "Int") {
				return Type::getInt32Ty(*context);
			}
			else if (type->Name == "Int8") {
				return Type::getInt8Ty(*context);
			}
			else if (type->Name == "Int16") {
				return Type::getInt16Ty(*context);
			}
			else if (type->Name == "Int32") {
				return Type::getInt32Ty(*context);
			}
			else if (type->Name == "Int64") {
				return Type::getInt64Ty(*context);
			}
			else if (type->Name == "UInt") {
				return Type::getInt32Ty(*context);
			}
			else if (type->Name == "UInt8") {
				return Type::getInt8Ty(*context);
			}
			else if (type->Name == "UInt16") {
				return Type::getInt16Ty(*context);
			}
			else if (type->Name == "UInt32") {
				return Type::getInt32Ty(*context);
			}
			else if (type->Name == "UInt64") {
				return Type::getInt64Ty(*context);
			}
			else if (type->Name == "Float") {
				return Type::getFloatTy(*context);
			}
			else if (type->Name == "Double") {
				return Type::getDoubleTy(*context);
			}
			else if (type->Name == "Char") {
				return Type::getInt8Ty(*context);
			}
			else if (type->Name == "Bool") {
				return Type::getInt1Ty(*context);
			}
		}

		return nullptr;
	}

	ConstantData* HGenerator::GetConstantData(llvm::LLVMContext* context, std::shared_ptr<AST::HAstExpressionNode> node) const {
		if (node->ExpressionType == ExpressionType::Literal) {
			auto literal = std::dynamic_pointer_cast<AST::HAstLiteralNode>(node);

			if (literal->LiteralType == HAstLiteralType::Integer) {
				return ConstantInt::get(*context, APInt(32, std::stoi(literal->Value)));
			}
			else if (literal->LiteralType == HAstLiteralType::Float) {
				return ConstantFP::get(*context, APFloat(std::stof(literal->Value)));
			}
			else if (literal->LiteralType == HAstLiteralType::Boolean) {
				return ConstantInt::get(*context, APInt(1, std::stoi(literal->Value)));
			}
		}

		return nullptr;
	}
}