#include "runtime/HGarbageCollector.hxx"
#include <algorithm>
#include <chrono>
#include <ranges>

namespace Hyve::Runtime {
	HGarbageCollector::HGarbageCollector(HGarbageCollectorConfig config) {
		_garbageCollectorThread = std::jthread([this, config]() {
			_lastTick = std::chrono::steady_clock::now().time_since_epoch().count();
			_tickIntervalMs = config.TickIntervalMs;
			_ageThreshold = config.AgeThreshold;
			Collect();
			// Sleep for delay
			std::this_thread::sleep_for(std::chrono::milliseconds(config.TickIntervalMs));
		});
	}

	HGarbageCollector::~HGarbageCollector() {
	}

	uint64_t HGarbageCollector::Allocate(size_t size) {
		auto* memory = (uint64_t*)std::malloc(size);
		if (memory == nullptr) {
			throw std::bad_alloc();
		}

		auto object = new HObject {
			.Refs = {},
			.Address = memory,
			.Size = size,
			.Age = 0
		};

		_youngObjects.push_back(object);

		return (uint64_t)object;
	}
	
	void HGarbageCollector::Collect() {
		// Before we start the tick, we need to check if the tick interval has passed at all
		// This way we don't have too many ticks in a short period of time
		auto now = std::chrono::steady_clock::now().time_since_epoch().count();
		
		if (auto elapsed = now - _lastTick; elapsed < _tickIntervalMs) {
			// Sleep for the remaining time
			std::this_thread::sleep_for(std::chrono::milliseconds(_tickIntervalMs - elapsed));
		}

		// Increment the age of all objects
		for (auto* obj : _youngObjects) {
			obj->Age++;
		}

		// Move objects that have reached the threshold to the old generation
		for (auto* obj : _youngObjects) {
			if (obj->Age >= _ageThreshold) {
				_oldObjects.push_back(obj);
				std::erase(_youngObjects, obj);
			}
		}

		// Set the last tick time
		_lastTick = std::chrono::steady_clock::now().time_since_epoch().count();
	}

	void HGarbageCollector::Track(uint64_t object, uint64_t target, ReferenceType refType) {
		Reference ref = { (HObject*)object, (HObject*)target, refType };
		_referenceTable[(HObject*)object].push_back(ref);
	}
	
	void HGarbageCollector::Untrack(uint64_t object, uint64_t target) {
		auto* obj = (HObject*)object;
		const auto* tgt = (HObject*)target;

		// Check if the object has any references in the table
		if (_referenceTable.contains(obj)) {
			return; // No references to remove
		}

		// Get the references associated with the object
		std::vector<Reference>& refs = _referenceTable[obj];

		// Remove references pointing to the target object
		std::erase_if(refs, [tgt](const Reference& ref) {
			return ref.To == tgt;
		});

		// If the object has no more references, remove it from the table
		if (refs.empty()) {
			_referenceTable.erase(obj);
		}
	}
}