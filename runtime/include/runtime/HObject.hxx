#pragma once

#include <cstdint>
#include <cstddef>
#include <memory>
#include <vector>

namespace Hyve::Runtime {
	enum class Color {
		BLACK,	// The object is reachable
		WHITE,	// The object is unreachable
		GREY	// The object is being processed
	};

	struct HObject {
		/// The references this object holds
		std::vector<HObject*> Refs;
		/// The references to this object
		std::vector<HObject*> BackRefs;
		/// The address of the object
		uint64_t* Address;
		/// The size of the object
		size_t Size;
		/// The age of the object
		uint64_t Age;
		/// The color of the object
		Color Color;
	};

	enum class ReferenceType {
		STRONG,
		WEAK
	};

	struct Reference {
		// Where this reference comes from
		HObject* From;
		// Where this reference goes to
		HObject* To;
		// The type of reference
		ReferenceType Type;
	};
}