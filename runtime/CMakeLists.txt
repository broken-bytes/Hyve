SET(
    SRC
    src/HRuntime.cxx
    src/HGarbageCollector.cxx
    src/HMemory.cxx
)

SET(
    HEADERS
    include/runtime/HRuntime.hxx
    include/runtime/HGarbageCollector.hxx
    include/runtime/HObject.hxx
    include/runtime/HAllocation.hxx
    include/runtime/HMemory.hxx
    include/runtime/HMemoryBlock.hxx
)

add_library(Runtime SHARED ${SRC} ${HEADERS})

target_include_directories(Runtime PUBLIC include)
