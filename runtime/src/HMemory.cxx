#include "runtime/HMemory.hxx"

namespace Hyve::Runtime {
	void* HMemory::Allocate(size_t size) {
		return nullptr;
	}

	void HMemory::Free(void* ptr) {

	}

	void* HMemory::Reallocate(void* ptr, size_t size) {
		return nullptr;
	}

	void* HMemory::Memory() const {
		return nullptr;
	}

	size_t HMemory::Size() const {
		return 0;
	}
}