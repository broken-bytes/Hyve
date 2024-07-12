#include "runtime/HStacktrace.hxx"
#include <stacktrace>
#include <Windows.h>
#include <DbgHelp.h>

namespace Hyve::Runtime {
    std::vector<uintptr_t> getPointersInFrame(HANDLE process, DWORD64 frameInstructionPointer) {
        std::vector<uintptr_t> pointers;

        // Get context for the frame
        CONTEXT context;
        RtlCaptureContext(&context);
        context.Rip = frameInstructionPointer; // Set the instruction pointer to the frame's IP

        // Get function information using SymFromAddr (error handling omitted for brevity)
        SYMBOL_INFO symbolInfo = { sizeof(SYMBOL_INFO), MAX_SYM_NAME };
        SymFromAddr(process, frameInstructionPointer, NULL, &symbolInfo);

        // Get FPO data (Frame Pointer Omission) to determine frame boundaries
        IMAGEHLP_MODULE64 imagehlpModuleInfo = { sizeof(IMAGEHLP_MODULE64) };
        IMAGEHLP_STACK_FRAME imagehlpStackFrame = { 0 };
        imagehlpStackFrame.InstructionOffset = context.Rip;
        SymSetContext(process, &imagehlpStackFrame, &context);
        DWORD imageType;
        if (!SymGetModuleInfo64(process, symbolInfo.ModBase, &imagehlpModuleInfo)) {
            // ... (handle error)
        }
        imageType = imagehlpModuleInfo.MachineType;

        // Unwind the stack using StackWalk64
        STACKFRAME64 stackFrame = { 0 };
        while (StackWalk64(imageType, process, GetCurrentThread(), &stackFrame, &context, NULL, SymFunctionTableAccess64, SymGetModuleBase64, NULL)) {
        }

        // ... (Handle possible stack walk errors)

        return pointers;
    }

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