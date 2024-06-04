#pragma once

#include <string>

namespace Hyve::Generator {
	class HGenerator {
	public:
		HGenerator() = default;
		~HGenerator() = default;

		std::string GenerateIR(std::string_view HIR);
	};
}