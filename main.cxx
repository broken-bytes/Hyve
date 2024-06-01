#include <cli/HCLI.hxx>
#include <cli/HCLIInvalidCommandException.hxx>
#include <lexer/HLexer.hxx>
#include <parser/HParser.hxx>
#include <typeck/HTypeck.hxx>

#include <cstdio>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <string_view>
#include <utility>

constexpr const char* VERSION = "0.0.1a";

int SetupCli(Hyve::CLI::HCLI& cli, const std::vector<std::string>& arguments) {
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

int main(int argc, char** argv) {
    std::vector<std::string> arguments(argc);

    for(int x = 0; x < argc; x++) {
        arguments.emplace_back(argv[x]);
    }

    Hyve::CLI::HCLI cli(VERSION);

    try {
        SetupCli(cli, arguments);
    } catch(std::exception& error) {
		std::cerr << error.what() << std::endl;
        return 1;
    }

    cli.ExecuteCommands();

    return 0;
}