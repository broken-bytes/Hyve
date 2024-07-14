#include "runtime/HGarbageCollector.hxx"
#include "runtime/HStacktrace.hxx"
#include <algorithm>
#include <chrono>
#include <iostream>
#include <ranges>

namespace Hyve::Runtime {
	HGarbageCollector::HGarbageCollector(
		HGarbageCollectorConfig config
	) : _tickIntervalMs(config.TickIntervalMs), _ageThreshold(config.AgeThreshold) {
		_lastTick = std::chrono::steady_clock::now().time_since_epoch().count();

		_garbageCollectorThread = std::jthread([this, config]() {
			Collect();
			// Sleep for delay
			std::this_thread::sleep_for(std::chrono::milliseconds(_tickIntervalMs));
		});
	}

	HGarbageCollector::~HGarbageCollector() {
	}

	uint64_t HGarbageCollector::RegisterTypeDescriptor(std::string_view name) {
		auto id = _typeDescriptors.size();
		auto descriptor = HTypeDescriptor {
			.Name = std::string(name),
			.Fields = {}
		};
		_typeDescriptors.push_back(descriptor);

		return id;
	}

	uint64_t HGarbageCollector::RegisterField(uint64_t type, std::string_view name, size_t size) {
		auto id = _typeDescriptors[type].Fields.size();
		auto field = HFieldDescriptor {
			.Name = std::string(name),
			.Size = size
		};
		_typeDescriptors[type].Fields.push_back(field);

		return id;
	}

	uint64_t HGarbageCollector::Allocate(uint64_t type) {
		// Get the size of the type
		size_t size = 0;
		for (const auto& field : _typeDescriptors[type].Fields) {
			size += field.Size;
		}

		auto memory = _youngMemory.Allocate(size);

		if (memory == 0) {
			throw std::bad_alloc();
		}

		auto object = new HObject {
			.Offset = memory,
			.Size = size,
			.Age = 0
		};

		_youngObjects.push_back(object);

		return (uint64_t)object;
	}
	
	void HGarbageCollector::Collect() {
		// Increment the age of all objects
		for (auto* obj : _youngObjects) {
			obj->Age++;
		}

		// Promote objects that have reached the age threshold
		Promote();

		// Mark all objects
		Mark();
		
		// Sweep the young generation
		Sweep();
	}

	void HGarbageCollector::TrackRoot(uint64_t object) {
		auto reference = RootReference {
			.Object = (HObject*)object
		};

		_rootTable.push_back(reference);
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

	void HGarbageCollector::SetAggressiveness(GCAggressiveness aggressiveness) {
		// TODO: Implement
	}

	void HGarbageCollector::SetTickInterval(uint64_t tickIntervalMs) {
		_tickIntervalMs = tickIntervalMs;
	}

	void HGarbageCollector::ScanRoots() {
		using enum Color;

		// Fill the roottable with the contents of the call stack
		auto stack = HStacktrace();
		// Get each frame on the stack
		for (const auto& frame : stack) {
			 // For each frame check if each address is a root(points to an object)
			for (const auto& address : frame.Addresses) {
				// Check if the address is a root
				auto potentialPointer = (uintptr_t*)address;

				std::cout << "Potential pointer: " << potentialPointer << std::endl;

				// Check if the value is a valid pointer to an allocated object
				/*if (std::any_of(_youngObjects.begin(), _youngObjects.end(), [potentialPointer](HObject* obj) { return obj == potentialPointer; }) ||
					std::any_of(_oldObjects.begin(), _oldObjects.end(), [potentialPointer](HObject* obj) { return obj == potentialPointer; })) {
					_rootTable.push_back( RootReference{ .Object = potentialPointer });
				}*/
			}
		} 

		// Mark all objects reachable from the roots on the queue
		for (const auto& root : _rootTable) {
			// Mark the object as in progress(gray)
			root.Object->Color = GRAY;

			// Iterate over the references
			for (const auto& refs = _referenceTable[root.Object]; const auto & objcRef : refs) {
				// If the reference is not marked, mark it
				if (objcRef.To->Color == WHITE) {
					// Mark the object as reachable(black)
					objcRef.To->Color = BLACK;
				}
			}

			// Mark the object as reachable(black)
			root.Object->Color = BLACK;
		}
	}

	void HGarbageCollector::ScanReferences(HObject* object) {
		using enum Color;
		// Mark all objects reachable from the references
		for (const auto& refs = _referenceTable[object]; const auto& objcRef : refs) {
			// If the reference is not marked, mark it
			if (objcRef.To->Color == WHITE) {
				// Mark the object as reachable(black)
				objcRef.To->Color = BLACK;

				// Recursively scan the references of the object
				ScanReferences(objcRef.To);
			}
		}
	}


	void HGarbageCollector::Mark() {
		using enum Color;
		// Mark all objects white first
		for (auto* obj : _youngObjects) {
			obj->Color = WHITE;
		}

		// Mark all objects reachable from the roots
		ScanRoots();
		
		// For each object in the young generation that is reachable, scan its references
		// These will be all objects referenced by obejcts reachable from the roots
		for(auto* obj : _youngObjects) {
			if (obj->Color == BLACK) {
				ScanReferences(obj);
			}
		}
	}

	void HGarbageCollector::Sweep() {
		using enum Color;

		// Sweep the young generation
		for (const auto* obj : _youngObjects) {
			if (obj->Color == WHITE) {
				_youngMemory.Free(obj->Offset);
			}
		}
	}

	void HGarbageCollector::Promote() {
		// Move objects that have reached the threshold to the old generation
		for (auto* obj : _youngObjects) {
			if (obj->Age >= _ageThreshold) {
				_oldObjects.push_back(obj);
				std::erase(_youngObjects, obj);
			}
		}
	}

	void HGarbageCollector::CollectYoung() {

	}

	void HGarbageCollector::CollectOld() {

	}
}