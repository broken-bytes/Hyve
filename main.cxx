#include <cli/HCLI.hxx>
#include <cli/HCLIInvalidCommandException.hxx>
#include <lexer/HLexer.hxx>
#include <parser/HParser.hxx>

#include <cstdio>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <string>
#include <utility>

constexpr const char* VERSION = "0.0.1a";

Hyve::CLI::HCLI cli(VERSION);
Hyve::Lexer::HLexer lexer;
Hyve::Parser::HParser parser;
std::vector<std::string> sourceFiles = {};

void SetupCommands() {
    auto help = Hyve::CLI::HCLICommand {
            .ShortName = "-h",
            .LongName = "--help",
            .Alias = "Help",
            .Help = "Displays help for Hyve",
            .Handler = [](const std::string& data) { }
    };

    auto compile = Hyve::CLI::HCLICommand {
            .ShortName = "-c",
            .LongName = "--compile",
            .Alias = "Compile",
            .Help = "Compiles the given file",
            .Handler = [](const std::string& data) { sourceFiles.push_back(data); }
    };

    auto target = Hyve::CLI::HCLICommand {
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

    cli.SetAvailableParameters(commands);
}

int SetupCli(const std::vector<std::string>& arguments) {
    SetupCommands();

    try {
        cli.ProcessCommandParameters(arguments);
    } catch(Hyve::CLI::HCLIInvalidCommandException& cmdError) {
        std::stringstream ss;
        ss << "Failed running Hyve: Unknown Command ";
        ss << cmdError.Command().c_str();
        cli.Write(Hyve::CLI::CLIColor::RED, ss.str());
        throw std::runtime_error(ss.str());
        return 1;
    } catch(std::exception& error) {
        std::stringstream ss;
        ss << "Failed running Hyve: Unknown Error\n";
        cli.Write(Hyve::CLI::CLIColor::RED, ss.str());
        throw std::runtime_error(ss.str());
    }

    return 0;
}

std::string LoadSourceFile(const std::string& location) {
    std::ifstream fileStream(location, std::ios::binary | std::ios::ate);

    if (!fileStream) {
        throw std::runtime_error("Cannot open file: " + location);
    }

    auto fileSize = fileStream.tellg();
    std::string fileContent(fileSize, '\0');
    fileStream.seekg(0);
    fileStream.read(&fileContent[0], fileSize);

    return fileContent;
}

int main(int argc, char** argv) {
    std::vector<std::string> arguments(argc);

    for(int x = 0; x < argc; x++) {
        arguments.emplace_back(argv[x]);
    }

    try {
        SetupCli(arguments);
    } catch(std::exception& error) {
        return 1;
    }

    cli.ExecuteCommands();

    std::queue<Hyve::Lexer::HToken> combinedTokes = {};

    for(auto& file: sourceFiles) {
        auto tokens = lexer.Tokenize(LoadSourceFile(file), file);

        while(!tokens.empty()) {
            combinedTokes.push(tokens.front());
            tokens.pop();
        }
    }

    int x = 0;

}