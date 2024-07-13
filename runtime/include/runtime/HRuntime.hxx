#pragma once

#include <stdint.h>

#define EXPORT __declspec(dllexport)

#ifdef __cplusplus
extern "C" {
#endif
	/**
	* @brief Registers a new type within the garbage collector.
	* @param name The name of the type.
	* @return The type ID.
	*/
	EXPORT uint64_t GC_RegisterType(const char* name);
	/**
	* @brief Registers a new field within the garbage collector on a given type.
	* @param type The type ID.
	* @param name The name of the field.
	* @param size The size of the field.
	* @return The field ID.
	*/
	EXPORT uint64_t GC_RegisterField(uint64_t type, const char* name, size_t size);
	/**
	* @brief Allocates size bytes of memory and returns a pointer to it.
	* @param size The size of the memory to allocate.
	* @return The pointer to the allocated memory.
	*/
	EXPORT uint64_t GC_Allocate(size_t size);
	/**
	* @brief Starts tracking an object.
	* @param object The object that should track the target.
	* @param target The target object to track.
	* @param isWeak Whether the tracking should be weak or not.
	*/
	EXPORT void GC_Track(uint64_t object, uint64_t target, bool isWeak = false);
	/**
	* @brief Stops tracking an object.
	* @param object The object that should stop tracking the target.
	* @param target The target object to stop tracking.
	*/
	EXPORT void GC_Untrack(uint64_t object, uint64_t target);
	/**
	* @brief Issues a garbage collection cycle.
	*/
	EXPORT void GC_Collect();

	/**
	* @brief Changes the interval between garbage collection cycles.
	* @param interval The interval in milliseconds.
	*/
	EXPORT void GC_SetInterval(uint64_t interval);

#ifdef __cplusplus
}
#endif