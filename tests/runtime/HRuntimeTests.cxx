#include <runtime/HRuntime.hxx>
#include <runtime/HObject.hxx>
#include <catch2/catch_test_macros.hpp>
#include <iostream>
#include <thread>

TEST_CASE("HRuntime - Allocate", "Allocate an object of size x") {
    int counter = 0;
    auto type = GC_RegisterType("User");
    auto name = GC_RegisterField(type, "name", 8);
    auto age = GC_RegisterField(type, "age", 4);

    GC_SetInterval(100);

    auto obj = GC_Allocate(type);
    auto obj2 = GC_Allocate(type);

    auto objectRef = (Hyve::Runtime::HObject*)obj;

    std::cout << "Object 1: " << objectRef->Age << std::endl;

    GC_Collect();

    while(true) {
        // Wait for a second
        std::this_thread::sleep_for(std::chrono::seconds(1));
        counter += 1;

        if(counter == 5) {
			break;
		}
    }

    // Check if GC cleared the object
    REQUIRE(objectRef == nullptr);
         
}