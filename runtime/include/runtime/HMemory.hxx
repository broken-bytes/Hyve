#pragma once

#include <list>

namespace Hyve::Runtime {
	struct HMemoryBlock;

	class HMemory {
	public:
		HMemory() = default;
		~HMemory() = default;

		/**
		* @brief Allocate memory
		* @param size Size of memory to allocate
		* @return The offset of the allocated memory from the start of this heap
		*/
		uint64_t Allocate(size_t size);
		/**
		* @brief Free memory
		* @param offset Offset of the memory to free from the start of this heap
		*/
		void Free(uint64_t offset);

		void* Memory() const;
		size_t Size() const;

	private:
		std::list<HMemoryBlock*> _blocks;
		std::list<HMemoryBlock*> _freeBlocks;

		HMemoryBlock* MakeBlock(size_t size);
		HMemoryBlock* FindBlock(uint64_t offset);
		HMemoryBlock* FindBestFitBlock(size_t size);
	};
}