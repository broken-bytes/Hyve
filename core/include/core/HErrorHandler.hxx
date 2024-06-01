#pragma once

#include "core/HCompilerError.hxx"
#include <vector>

namespace Hyve::Core {
	class HErrorHandler {
	public:
		HErrorHandler() = default;
		~HErrorHandler() = default;

		void AddError(
			HCompilerError::ErrorCode code, 
			std::string file, 
			uint64_t line
		) {
			_errors.emplace_back(code, file, line);
		}

		std::vector<HCompilerError> GetErrors() const {
			return _errors;
		}

	private:
		std::vector<HCompilerError> _errors;
	};
}