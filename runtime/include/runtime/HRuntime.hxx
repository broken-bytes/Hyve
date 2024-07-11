#pragma once

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif
	uint64_t GC_Allocate(size_t size);
	void GC_Track(uint64_t object, uint64_t target, bool isWeak = false);
	void GC_Untrack(uint64_t object, uint64_t target);
	void GC_Collect();

#ifdef __cplusplus
}
#endif