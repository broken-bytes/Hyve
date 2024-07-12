#pragma once

#include <cstdint>
#include <cstddef>
#include <memory>
#include <vector>

namespace Hyve::Runtime {
	enum class Color {
		BLACK,	// The object is reachable
		WHITE,	// The object is unreachable
		GRAY	// The object is being processed
	};

	struct HObject {
		/// The type of the object
		uint64_t TypeId;
		/// The offset of the object in the heap it belongs to
		uint64_t Offset;
		/// The size of the object
		size_t Size;
		/// The age of the object
		uint64_t Age;
		/// The color of the object
		Color Color;
	};
}