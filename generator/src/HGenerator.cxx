#pragma once

#include <string>

namespace Hyve::Generator {
	class Generator {
	public:
		Generator() = default;
		~Generator() = default;

		std::string GenerateIR(std::string_view HIR);
	};
}