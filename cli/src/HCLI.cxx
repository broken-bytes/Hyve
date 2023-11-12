#include "cli/HCLI.hxx"
#include "cli/HCLIInvalidCommandException.hxx"
#include <algorithm>
#include <cstdio>
#include <sstream>
#include <utility>

namespace Hyve::CLI {
    HCLI::HCLI(std::string version) : _version(std::move(version)) {
        std::stringstream vsString;
        vsString <<R"(
    ______
  /        \
 /          \
/    Hyve    \
)";
        vsString << "\\   " << _version << "   /";
        vsString << R"(
 \          /
  \________/

)";
        Write(Hyve::CLI::CLIColor::PURPLE, vsString.str());
        Write(Hyve::CLI::CLIColor::BLUE, "Welcome to Hyve \n\n");
    }

    std::vector<HCLICommandParameter> HCLI::CommandParameters() const {
        return _providedCommands;
    }

    void HCLI::ExecuteCommands() const {
        for(auto& param: _providedCommands) {
            auto command = std::find_if(
                    _availableCommands.begin(),
                    _availableCommands.end(),
                    [param](const auto& command) {
                        return command.Alias == param.Name;
                    }
            );

            if(command != _availableCommands.end()) {
                command->Handler(param.Value);
            }
        }
    }

    void HCLI::ProcessCommandParameters(const std::vector<std::string>& arguments) {
        std::string command;

        std::vector<HCLICommandParameter> params {};
        
        for(auto& str: arguments) {
            // Pre-check: If the string is empty skip it
            if(str.empty()) {
                continue;
            }
            // We don't have a command yet
            if(command.empty()) {
                if(CheckIfCommand(str)) {
                    command = GetCommand(str).Alias;
                }
            } else {
                params.push_back(HCLICommandParameter { .Name = command, .Value = str});
                command.clear();
            }
        }

        Write(Hyve::CLI::CLIColor::YELLOW, "Compiler options used:\n");

        for(auto& arg: params) {
            Write(Hyve::CLI::CLIColor::YELLOW, "  - ");
            Write(Hyve::CLI::CLIColor::YELLOW, arg.Name);
            Write(Hyve::CLI::CLIColor::YELLOW, " ");
            Write(Hyve::CLI::CLIColor::YELLOW, arg.Value);
            Write(Hyve::CLI::CLIColor::YELLOW, "\n");
        }

        _providedCommands = params;
    }

    void HCLI::SetAvailableParameters(std::vector<HCLICommand> availableCommands) {
        this->_availableCommands = std::move(availableCommands);
    }

    void HCLI::Write(CLIColor color, const std::string& message) {
        printf("\033[1;%im%s\033[0m", (int)color, message.c_str());
    }

    bool HCLI::CheckIfCommand(const std::string& str) const {
        return str.starts_with("-") || str.starts_with("--");
    }

    HCLICommand HCLI::GetCommand(const std::string& str) const {
        for (auto &cmd: this->_availableCommands) {
            if (str.contains(cmd.ShortName) || str.contains(cmd.LongName)) {
                return cmd;
            }
        }

        throw HCLIInvalidCommandException(str);
    }
}