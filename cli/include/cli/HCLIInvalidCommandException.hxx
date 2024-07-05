#pragma once

#include <exception>
#include <string>

namespace Hyve::CLI {
    class HCLIInvalidCommandException : public std::exception {
        public:
        explicit HCLIInvalidCommandException(std::string_view command) : std::exception(), _command(command) { };
        const std::string& Command() const {
            return _command;
        }

        private:
        std::string _command;
    };
}