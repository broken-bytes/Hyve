#include <runtime/HRuntime.hxx>
#include <catch2/catch_test_macros.hpp>
#include <thread>

TEST_CASE("HRuntime - Allocate", "Allocate an object of size x") {
    auto type = GC_RegisterType("User");
    auto name = GC_RegisterField(type, "name", 8);
    auto age = GC_RegisterField(type, "age", 4);

    auto obj = GC_Allocate(type);
    auto obj2 = GC_Allocate(type);

    GC_Track(obj, obj2);

    GC_Collect();

    while(true) {
        // Wait for a second
        std::this_thread::sleep_for(std::chrono::seconds(1));
        // Check if GC cleared the object
    }

    // Deallocate the object
    int x = 0;
}