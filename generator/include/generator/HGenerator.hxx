#pragma once

#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/Target/TargetMachine.h>
#include <string>

namespace Hyve::Generator {
	class HGenerator {
	public:
		HGenerator() = default;
		~HGenerator() = default;

		std::string GenerateIR(std::string_view HIR);

	private:
		std::unique_ptr<llvm::TargetMachine> targetMachine;

#ifdef HYVE_BOOTSTRAP
		void LinkStandardLibrary(llvm::LLVMContext& context, llvm::Module* currentModule);
		std::unique_ptr<llvm::Module> LoadLowLevelStandardLibrary(llvm::LLVMContext& context);
#endif
	};
}