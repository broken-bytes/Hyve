#include "runtime/HStacktrace.hxx"
#include <stacktrace>
#include <Windows.h>
#include <DbgHelp.h>

namespace Hyve::Runtime {
    HStacktrace::HStacktrace() {
        std::stacktrace trace; // Capture the current stack trace
        size_t stackSize = trace.size();

        // Skip last frame - trace constructor (remove if you need to display that info)
        stackSize = stackSize - 1;

        _frames.reserve(stackSize); // Reserve space for efficiency

        // Initialize symbol handling (needed to get function names and addresses)
        HANDLE process = GetCurrentProcess();
        SymInitialize(process, NULL, TRUE); // Load symbols for the current process

        // Iterate over frames and extract information
        for (HStackframe& frame : _frames) {
            DWORD64 displacement = 0;
            SYMBOL_INFO symbolInfo = { 0 };
            if (SymFromAddr(process, frame.InstructionPointer, &displacement, &symbolInfo)) {
                
            }
        }

        SymCleanup(process); // Clean up symbol handling
    }
}