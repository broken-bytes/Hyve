#include "runtime/HRuntime.hxx"
#include "runtime/HGarbageCollector.hxx"

using namespace Hyve::Runtime;

const std::unique_ptr<HGarbageCollector> GC = std::make_unique<HGarbageCollector>(
    HGarbageCollectorConfig {
        .TickIntervalMs = 1000,
        .AgeThreshold = 10000
    }
);

uint64_t GC_RegisterType(const char* name) {
    return GC->RegiserTypeDescriptor(name);
}

uint64_t GC_RegisterField(uint64_t type, const char* name, size_t size) {
    return GC->RegisterField(type, name, size);
}

uint64_t GC_Allocate(size_t size) {
    return GC->Allocate(size);
}

void GC_Track(uint64_t object, uint64_t target, bool isWeak) {
    GC->Track(object, target, isWeak ? ReferenceType::WEAK : ReferenceType::STRONG);
}

void GC_Untrack(uint64_t object, uint64_t target) {
    GC->Untrack(object, target);
}

void GC_Collect() {
    GC->Collect();
}