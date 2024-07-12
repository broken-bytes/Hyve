SET(
    SRC
    src/HRuntime.cxx
    src/HGarbageCollector.cxx
    src/HMemory.cxx
    src/windows/HStacktrace.cxx
)

SET(
    HEADERS
    include/runtime/HRuntime.hxx
    include/runtime/HGarbageCollector.hxx
    include/runtime/HObject.hxx
    include/runtime/HAllocation.hxx
    include/runtime/HMemory.hxx
    include/runtime/HMemoryBlock.hxx
    include/runtime/HReference.hxx
    include/runtime/HStackframe.hxx
    include/runtime/HStacktrace.hxx
    include/runtime/HTypeDescriptor.hxx
    include/runtime/HVariable.hxx
)

add_library(Runtime SHARED ${SRC} ${HEADERS})

target_include_directories(Runtime PUBLIC include)

if(WIN32)
    target_link_libraries(Runtime PUBLIC DbgHelp Kernel32)
else()
    if(NOT DEFINED ENV{TARGET})
        set(ENV{TARGET} "x86_64-linux-gnu")
    endif()

    Include(FetchContent)

    FetchContent_Declare(
        libunwind
        GIT_REPOSITORY https://github.com/libunwind/libunwind.git
        GIT_TAG        v1.8.1 # or a later release
    )

    FetchContent_MakeAvailable(libunwind)

    target_link_libraries(Runtime PUBLIC libunwind)
endif()
