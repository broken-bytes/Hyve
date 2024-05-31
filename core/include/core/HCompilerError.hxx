#pragma once

#include <cstdint>
#include <string>
#include <string_view>
#include <sstream>
#include <stdexcept>

namespace Hyve::Core {
    class HCompilerError : public std::runtime_error {
    public:
        enum class ErrorCode: uint16_t {
            // Syntax Errors (1xxx)
            UnexpectedToken = 1000,
            UnexpectedEndOfFile = 1001,
            UnexpectedCharacter = 1002,

            // Type Errors (2xxx)
            TypeMismatch = 2000,
            InvalidCast = 2001,

            // Reference/Assignment Errors (3xxx)
            AssignmentToConstant = 3000, // Assigning to a constant variable
            UnassignedVariableAccess = 3001,    // Reading from an uninitialized variable
            InvalidPointerDereference = 3002,   // Dereferencing a null or invalid pointer

            // Symbol Errors (4xxx)
            UndefinedSymbol = 4000,     // Using a variable/function before declaration
            DuplicateSymbolDeclaration = 4001,  // Declaring the same symbol multiple times

            // Other Runtime Errors (5xxx)
            DivisionByZero = 5000,
            IndexOutOfBounds = 5001,
            StackOverflow = 5002,
        };

        std::string DescriptionForCode(ErrorCode code) const {
			switch (code) {
				using enum Hyve::Core::HCompilerError::ErrorCode;
				case UnexpectedToken:
					return "Unexpected token";
				case UnexpectedEndOfFile:
					return "Unexpected end of file";
				case UnexpectedCharacter:
					return "Unexpected character";
				case TypeMismatch:
					return "Type mismatch";
				case InvalidCast:
					return "Invalid cast";
				case AssignmentToConstant:
					return "Assignment to constant";
				case UnassignedVariableAccess:
					return "Unassigned variable access";
				case InvalidPointerDereference:
					return "Invalid pointer dereference";
				case UndefinedSymbol:
					return "Undefined symbol";
				case DuplicateSymbolDeclaration:
					return "Duplicate symbol declaration";
				case DivisionByZero:
					return "Division by zero";
				case IndexOutOfBounds:
					return "Index out of bounds";
				case StackOverflow:
					return "Stack overflow";
				default:
					return "Unknown error";
			}
		}

        explicit HCompilerError(
            ErrorCode code, 
            std::string_view file, 
            uint64_t line
        ) : std::runtime_error(""), _code(code), _file(file), _line(line) {
        }

        const char* what() const noexcept override {
			std::stringstream ss;
			ss << DescriptionForCode(_code) << " at " << _file << ":" << _line << std::endl;

			return ss.str().c_str();
		}

	private:
		ErrorCode _code;
		std::string _file;
		uint64_t _line;
    };
}