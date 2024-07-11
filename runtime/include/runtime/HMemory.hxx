#pragma once

#include <forward_list>

namespace Hyve::Runtime {
	struct HMemoryBlock;

	class HMemory {
	public:
		HMemory() = default;
		~HMemory() = default;

		void* Allocate(size_t size);
		void Free(void* ptr);
		void* Reallocate(void* ptr, size_t size);

		void* Memory() const;
		size_t Size() const;

	private:
		std::forward_list<HMemoryBlock*> _blocks;
		std::forward_list<HMemoryBlock*> _freeBlocks;
	};
}