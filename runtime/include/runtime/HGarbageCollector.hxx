#pragma once

#include "runtime/HRuntime.hxx"
#include "runtime/HMemory.hxx"
#include "runtime/HObject.hxx"
#include <thread>
#include <memory>
#include <unordered_map>
#include <vector>

namespace Hyve::Runtime {
	struct HGarbageCollectorConfig {
	public:
		uint64_t TickIntervalMs = 1000;
		uint64_t AgeThreshold = 10000;
	};

	class HGarbageCollector {
	public:
		explicit HGarbageCollector(HGarbageCollectorConfig config);
		~HGarbageCollector();
		void Collect();
		uint64_t Allocate(size_t size);
		void Track(uint64_t object, uint64_t target, ReferenceType refType);
		void Untrack(uint64_t object, uint64_t target);

	private:
		std::unordered_map<HObject*, std::vector<Reference>> _referenceTable;
		std::vector<HObject*> _youngObjects;
		std::vector<HObject*> _oldObjects;
		uint64_t _lastTick;
		uint64_t _tickIntervalMs;
		uint64_t _lastNumAllocs;
		uint64_t _ageThreshold;
		std::jthread _garbageCollectorThread;

		// Memory heap for young objects
		HMemory _youngMemory;
		// Memory heap for old objects
		HMemory _oldMemory;
	};
}