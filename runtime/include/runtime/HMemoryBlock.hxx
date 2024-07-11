#pragma once

#include <cstdint>

namespace Hyve::Runtime {
	struct HMemoryBlock {
		uint64_t Size;
		uint64_t* Address;
		HMemoryBlock* Next;
		bool IsFree;
	};
}