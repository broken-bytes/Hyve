#include "generator/HGenerator.hxx"
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
#include <llvm/Object/ObjectFile.h>
#include <llvm/IR/PassManager.h>
#include <llvm/Passes/PassBuilder.h>
#include <llvm/TargetParser/Host.h>
#include <llvm/Support/InitLLVM.h>
#include <optional>

using namespace llvm;

namespace Hyve::Generator {
	std::string HGenerator::GenerateIR(std::string_view HIR) {
        // Initialize the target registry etc.
        InitializeNativeTarget();
        InitializeNativeTargetAsmPrinter();
        InitializeNativeTargetAsmParser();

        // Create a context to hold the LLVM constructs
        LLVMContext Context;

        // Create a new module
        std::unique_ptr<Module> Module = std::make_unique<llvm::Module>("hello", Context);

        // Create a function type: int main()
        FunctionType* MainType = FunctionType::get(Type::getInt32Ty(Context), false);

        // Create the main function: int main()
        Function* MainFunction = Function::Create(MainType, Function::ExternalLinkage, "main", *Module);

        // Create a basic block and attach it to the main function
        BasicBlock* EntryBlock = BasicBlock::Create(Context, "entry", MainFunction);

        // Create an IR builder and set the insertion point to the entry block
        IRBuilder<> Builder(EntryBlock);

        // Get the type for printf: int printf(const char *format, ...)
        PointerType* PrintfArgType = PointerType::get(Type::getInt8Ty(Context), 0);
        FunctionType* PrintfType = FunctionType::get(Builder.getInt32Ty(), PrintfArgType, true);

        // Create the printf function and add it to the module
        FunctionCallee Printf = Module->getOrInsertFunction("printf", PrintfType);

        // Create a global string: const char *str = "Hello, World!\n"
        Value* HelloWorld = Builder.CreateGlobalStringPtr("Hello, World!");

        std::vector<Type*> FuncArgTypes(2, Type::getInt32Ty(Context));
        FunctionType* ExternCFuncType = FunctionType::get(Type::getInt32Ty(Context), FuncArgTypes, false);

        // Create the main function: int main()
        Function* ExternCFunc = Function::Create(ExternCFuncType, Function::ExternalLinkage, "CFunc", *Module);
        ExternCFunc->setCallingConv(CallingConv::C);

        Value* Arg1 = Builder.getInt32(2);
        Value* Arg2 = Builder.getInt32(0);
        // Call the function: myFunc(10, 20)
        Value* CallResult = Builder.CreateCall(ExternCFunc, { Arg1, Arg2 });

        // We want to check if the CFunc returned an even number, if yes we print 'even' else 'odd'. 
        // We create two basic blocks for this
        BasicBlock* EvenBlock = BasicBlock::Create(Context, "even", MainFunction);
        BasicBlock* OddBlock = BasicBlock::Create(Context, "odd", MainFunction);

        // Create the conditional branch
        Value* ModResult = Builder.CreateSRem(CallResult, Builder.getInt32(2));
        Value* IsOdd = Builder.CreateICmpNE(ModResult, Builder.getInt32(0));
        Builder.CreateCondBr(IsOdd, OddBlock, EvenBlock);

        // Set the insertion point to the even block
        Builder.SetInsertPoint(EvenBlock);

        // Create a global string: const char *str = "Even\n"
        Value* EvenString = Builder.CreateGlobalStringPtr("Even\n");

        // Call printf with the even string
        Builder.CreateCall(Printf, { EvenString });

        // Return 0 from the main function
        Builder.CreateRet(Builder.getInt32(0));

        // Set the insertion point to the odd block

        Builder.SetInsertPoint(OddBlock);

        // Create a global string: const char *str = "Odd\n"

        Value* OddString = Builder.CreateGlobalStringPtr("Odd\n");

        // Call printf with the odd string
        Builder.CreateCall(Printf, { OddString });

        // Return 0 from the main function

        Builder.CreateRet(Builder.getInt32(0));

        // Print the module to stdout
        Module->print(outs(), nullptr);

        // Set up the target machine
        std::string TargetTriple = sys::getDefaultTargetTriple();
        Module->setTargetTriple(TargetTriple);
        std::string Error;
        const Target* Target = TargetRegistry::lookupTarget(TargetTriple, Error);

        if (!Target) {
            errs() << "Error: " << Error;
            return "";
        }

        TargetOptions opt;
        auto RM = std::optional<Reloc::Model>();
        std::unique_ptr<TargetMachine> TargetMachine(Target->createTargetMachine(TargetTriple, "generic", "", opt, RM));

        Module->setDataLayout(TargetMachine->createDataLayout());

        std::error_code EC;
        raw_fd_ostream dest("hello.o", EC, sys::fs::OF_None);

        if (EC) {
            errs() << "Could not open file: " << EC.message();
            return "";
        }

        legacy::PassManager pass;
        if (TargetMachine->addPassesToEmitFile(pass, dest, nullptr, CodeGenFileType::ObjectFile)) {
            errs() << "TargetMachine can't emit a file of this type";
            return "";
        }

        pass.run(*Module);
        dest.flush();

        outs() << "Object file generated successfully\n";
        return "";
	}
}