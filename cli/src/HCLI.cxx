#include "cli/HCLI.hxx"
#include "cli/HCLIInvalidCommandException.hxx"
#include <algorithm>
#include <cstdio>
#include <ranges>
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
        _compiler = std::make_unique<Hyve::HCompiler>();

        SetupCommands();
    }

    void HCLI::SetupCommands() {
        auto help = Hyve::CLI::HCLICommand{
                .ShortName = "-h",
                .LongName = "--help",
                .Alias = "Help",
                .Help = "Displays help for Hyve",
                .Handler = []([[maybe_unused]] const std::string_view data) {
                    printf("hyvec is the compiler for the Hyve language\n");
					printf("Usage: hyvec [options]\n\n");
					printf("Options:\n");
					printf("  -h, --help\t\tDisplays this help message\n");
					printf("  -c, --compile\t\tCompiles the given file\n");
					printf("  -t, --target\t\tSets the compile target. Possible values are debug|release\n");

                    exit(0);
            }
        };

        auto compile = Hyve::CLI::HCLICommand{
                .ShortName = "-c",
                .LongName = "--compile",
                .Alias = "Compile",
                .Help = "Compiles the given file",
                .Handler = [this](const std::string& data) { _sourceFiles.push_back(data); }
        };

        auto target = Hyve::CLI::HCLICommand{
                .ShortName = "-t",
                .LongName = "--target",
                .Alias = "Target",
                .Help = "Sets the compile target. Possible values are debug|release"
        };

        std::vector<Hyve::CLI::HCLICommand> commands = {
                help,
                compile,
                target
        };

        SetAvailableParameters(commands);
    }

    std::vector<HCLICommandParameter> HCLI::CommandParameters() const {
        return _providedCommands;
    }

    void HCLI::ExecuteCommands() const {
        for (auto& param : _providedCommands) {
            auto command = std::ranges::find_if(
                _availableCommands,
                [&param](const auto& cmd) {
                    return cmd.Alias == param.Name;
                }
            );

            if (command != _availableCommands.end()) {
                command->Handler(param.Value);
            }
        }

        // If the help command is provided, we skip any other command
        if(std::ranges::find_if(
			_providedCommands.begin(), 
			_providedCommands.end(), 
			[](const auto& cmd) { return cmd.Name == "Help"; }) != _providedCommands.end()
		) {
			return;
		}

        if(std::ranges::find_if(
            _providedCommands.begin(), 
            _providedCommands.end(), 
            [](const auto& cmd) { return cmd.Name == "Compile"; }) == _providedCommands.end()
        ) {
			Write(CLIColor::RED, "No compile command provided. Exiting...\n");
			exit(1);
		}

        // If no source files are provided, we can't compile anything
        if(_sourceFiles.empty()) {
			Write(CLIColor::RED, "No source files provided. Exiting...\n");
			exit(1);
		}

        _compiler->Compile(_sourceFiles);
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
                params.emplace_back(command, str);
                command.clear();
            }
        }

        Write(Hyve::CLI::CLIColor::YELLOW, "Compiler options used:\n");

        for(const auto& arg: params) {
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

    void HCLI::Write(CLIColor color, const std::string& message) const {
        printf("\033[1;%im%s\033[0m", (int)color, message.c_str());
    }

    bool HCLI::CheckIfCommand(std::string_view str) const {
        return str.starts_with("-") || str.starts_with("--");
    }

    HCLICommand HCLI::GetCommand(std::string_view str) const {
        for (auto &cmd: this->_availableCommands) {
            if (str.contains(cmd.ShortName) || str.contains(cmd.LongName)) {
                return cmd;
            }
        }

        throw HCLIInvalidCommandException(std::string(str));
    }
}