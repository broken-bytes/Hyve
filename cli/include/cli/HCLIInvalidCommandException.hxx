#pragma once

#include <exception>
#include <string>

namespace Hyve::CLI {
    class HCLIInvalidCommandException : std::exception {
        public:
        HCLIInvalidCommandException(std::string command) : std::exception(), _command(command) { };
        const std::string& Command() const {
            return _command;
        }

        private:
        std::string _command;
    };
}