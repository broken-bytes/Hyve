#pragma once

#include <array>
#include <string_view>

namespace Hyve::Typeck {
	constexpr const std::array<std::string_view, 13> HPrimitiveTypes {
		"Int",
		"Int8",
		"Int16",
		"Int32",
		"Int64",
		"UInt",
		"UInt8",
		"UInt16",
		"UInt32",
		"UInt64",
		"Float",
		"Double",
		"Bool",
	};
}