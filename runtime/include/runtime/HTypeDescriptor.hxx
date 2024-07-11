#pragma once

#include <string>
#include <vector>

namespace Hyve::Runtime {
	struct HFieldDescriptor {
		std::string Name;
		size_t Size;
	};

	struct HTypeDescriptor {
		std::string Name;
		std::vector<HFieldDescriptor> Fields;
	};
}