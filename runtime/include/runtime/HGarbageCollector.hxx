#pragma once

#include "runtime/HRuntime.hxx"
#include "runtime/HMemory.hxx"
#include "runtime/HObject.hxx"
#include "runtime/HReference.hxx"
#include "runtime/HTypeDescriptor.hxx"
#include <thread>
#include <memory>
#include <queue>
#include <string_view>
#include <unordered_map>
#include <vector>

namespace Hyve::Runtime {
	enum class GCAggressiveness {
		Aggresive,
		Normal,
		Conservative
	};

	struct HGarbageCollectorConfig {
	public:
		uint64_t TickIntervalMs = 1000;
		uint64_t AgeThreshold = 10000;
	};

	class HGarbageCollector {
	public:
		explicit HGarbageCollector(HGarbageCollectorConfig config);
		~HGarbageCollector();
		uint64_t RegisterTypeDescriptor(std::string_view name);
		uint64_t RegisterField(uint64_t type, std::string_view name, size_t size);
		void Collect();
		uint64_t Allocate(uint64_t type);
		void TrackRoot(uint64_t object);
		void Track(uint64_t object, uint64_t target, ReferenceType refType);
		void Untrack(uint64_t object, uint64_t target);
		
		// --- Configuration ---
		void SetAggressiveness(GCAggressiveness aggressiveness);
		void SetTickInterval(uint64_t tickIntervalMs);

	private:
		std::vector<HTypeDescriptor> _typeDescriptors;

		// Root to object mapping
		std::vector<RootReference> _rootTable;
		// Object to references mapping
		std::unordered_map<HObject*, std::vector<Reference>> _referenceTable;
		std::vector<HObject*> _youngObjects;
		std::vector<HObject*> _oldObjects;
		uint64_t _lastTick;
		uint64_t _tickIntervalMs;
		uint64_t _ageThreshold;
		std::jthread _garbageCollectorThread;

		// Memory heap for young objects
		HMemory _youngMemory;
		// Memory heap for old objects
		HMemory _oldMemory;

		void ScanRoots();
		void ScanReferences(HObject* object);
		void Mark();
		void Sweep();
		void Promote();
		void CollectYoung();
		void CollectOld();
	};
}