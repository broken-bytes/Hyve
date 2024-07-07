#pragma once

#include <memory>
#include <string>
#include <string_view>

namespace Hyve::AST {
	struct HAstNode;
}

namespace Hyve::Generator {
	class HGenerator {
	public:
		HGenerator() = default;
		~HGenerator() = default;

		std::string GenerateIR(std::string_view fileName, std::shared_ptr<AST::HAstNode> nodes) const;
	};
}