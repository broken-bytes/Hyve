#pragma once

#include <string>

namespace Hyve::Typeck {
	struct HType {
		std::string Name;
		HSymbolType SymbolType;
	};
}