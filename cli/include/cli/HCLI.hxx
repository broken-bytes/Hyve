#pragma once

#include "cli/HCLICommand.hxx"
#include "cli/HCLICommandParameter.hxx"
#include <cstdint>
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
        HCLI(std::string  version);
        [[nodiscard]] std::vector<HCLICommandParameter> CommandParameters() const;
        void ExecuteCommands() const;
        void ProcessCommandParameters(const std::vector<std::string>& arguments);
        void SetAvailableParameters(std::vector<HCLICommand> availableCommands);
        void Write(CLIColor color, const std::string& message);

        private:
        std::string _version;
        std::vector<HCLICommand> _availableCommands;
        std::vector<HCLICommandParameter> _providedCommands;

        [[nodiscard]] bool CheckIfCommand(const std::string& str) const;
        [[nodiscard]] HCLICommand GetCommand(const std::string& str) const;
    };
}