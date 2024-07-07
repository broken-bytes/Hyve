#pragma once

#include "cli/HCLICommand.hxx"
#include "cli/HCLICommandParameter.hxx"
#include <libhyve/HCompiler.hxx>
#include <libhyve/HCompilerArgument.hxx>
#include <cstdint>
#include <map>
#include <vector>

namespace Hyve::CLI {
    enum class CLIColor: uint8_t {
        RED = 31,
        GREEN = 32,
        YELLOW = 33,
        BLUE = 36,
        PURPLE = 35
    };

    class HCLI {
        public:
        explicit HCLI(std::string  version);
        void SetupCommands();
        [[nodiscard]] std::vector<HCLICommandParameter> CommandParameters() const;
        void ExecuteCommands() const;
        void ProcessCommandParameters(const std::vector<std::string>& arguments);
        void SetAvailableParameters(std::vector<HCLICommand> availableCommands);
        void Write(CLIColor color, const std::string& message) const;

        private:
        std::string _version;
        std::vector<HCLICommand> _availableCommands;
        std::vector<HCLICommandParameter> _providedCommands;
        std::vector<std::string> _sourceFiles;
        std::unique_ptr<Hyve::HCompiler> _compiler;
        std::vector<Hyve::HCompilerArgument> _compilerArguments;

        [[nodiscard]] bool CheckIfCommand(std::string_view str) const;
        [[nodiscard]] HCLICommand GetCommand(std::string_view str) const;

        void PrintHelp() const;
    };
}