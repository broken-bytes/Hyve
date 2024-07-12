#include "runtime/HMemory.hxx"
#include "runtime/HMemoryBlock.hxx"

namespace Hyve::Runtime {
	uint64_t HMemory::Allocate(size_t size) {
		// Find a free block of memory

		auto block = FindBestFitBlock(size);

		if (block == nullptr) {
			block = MakeBlock(size);	
		} else {
			_freeBlocks.remove(block);
		}

		block->IsFree = false;

		return (uint64_t)block->Address;
	}

	void HMemory::Free(uint64_t offset) {
		auto block = FindBlock(offset);

		if (block == nullptr) {
			return;
		}

		block->IsFree = true;

		_freeBlocks.push_back(block);
	}

	size_t HMemory::Size() const {
		return 0;
	}

	HMemoryBlock* HMemory::MakeBlock(size_t size) {
		auto block = new HMemoryBlock{
			.Size = size,
			.Address = 0,
			.IsFree = false
		};

		block->Address = (uint64_t*)std::malloc(size);


		_blocks.push_back(block);

		return block;
	}

	HMemoryBlock* HMemory::FindBlock(uint64_t offset) {
		for (auto block : _blocks) {
			if ((uint64_t)block->Address == offset) {
				return block;
			}
		}

		return nullptr;
	}

	HMemoryBlock* HMemory::FindBestFitBlock(size_t size) {
		HMemoryBlock* bestFit = nullptr;

		if(_freeBlocks.empty()) {
			return nullptr;
		}

		for (auto block : _freeBlocks) {
			if (block->Size >= size && (bestFit == nullptr || block->Size < bestFit->Size)) {
				bestFit = block;
			}
		}

		return bestFit;
	}
}