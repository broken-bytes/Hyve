#include "runtime/HStacktrace.hxx"
#include <stacktrace>
#include <Windows.h>
#include <DbgHelp.h>

namespace Hyve::Runtime {
    std::vector<uintptr_t> GetPointersInFrame(HANDLE process, DWORD64 frameInstructionPointer) {
        std::vector<uintptr_t> pointers;

        // Initialize symbol info structure
        SYMBOL_INFO symbolInfo = {};
        symbolInfo.SizeOfStruct = sizeof(SYMBOL_INFO);
        symbolInfo.MaxNameLen = MAX_SYM_NAME;

        if (!SymFromAddr(process, frameInstructionPointer, nullptr, &symbolInfo)) {
            throw std::runtime_error("Failed to get symbol info");
        }

        // Get module information
        IMAGEHLP_MODULE64 moduleInfo = {};
        moduleInfo.SizeOfStruct = sizeof(IMAGEHLP_MODULE64);

        if (!SymGetModuleInfo64(process, symbolInfo.ModBase, &moduleInfo)) {
            throw std::runtime_error("Failed to get module info");
        }

        // Process frame data (e.g., pointers) as needed
        // This part would depend on your specific requirements

        return pointers;
    }

    void WalkStack(HANDLE process, HANDLE thread) {
        std::vector<HStackframe> stackFrames;

        CONTEXT context = {};
        context.ContextFlags = CONTEXT_FULL;
        if (!GetThreadContext(thread, &context)) {
            throw std::runtime_error("Failed to get thread context");
        }

        STACKFRAME64 stackFrame = {};
        DWORD machineType;

#ifdef _M_IX86
        machineType = IMAGE_FILE_MACHINE_I386;
        stackFrame.AddrPC.Offset = context.Eip;
        stackFrame.AddrPC.Mode = AddrModeFlat;
        stackFrame.AddrFrame.Offset = context.Ebp;
        stackFrame.AddrFrame.Mode = AddrModeFlat;
        stackFrame.AddrStack.Offset = context.Esp;
        stackFrame.AddrStack.Mode = AddrModeFlat;
#elif _M_X64
        machineType = IMAGE_FILE_MACHINE_AMD64;
        stackFrame.AddrPC.Offset = context.Rip;
        stackFrame.AddrPC.Mode = AddrModeFlat;
        stackFrame.AddrFrame.Offset = context.Rsp;
        stackFrame.AddrFrame.Mode = AddrModeFlat;
        stackFrame.AddrStack.Offset = context.Rsp;
        stackFrame.AddrStack.Mode = AddrModeFlat;
#elif _M_IA64
        machineType = IMAGE_FILE_MACHINE_IA64;
        stackFrame.AddrPC.Offset = context.StIIP;
        stackFrame.AddrPC.Mode = AddrModeFlat;
        stackFrame.AddrFrame.Offset = context.IntSp;
        stackFrame.AddrFrame.Mode = AddrModeFlat;
        stackFrame.AddrBStore.Offset = context.RsBSP;
        stackFrame.AddrBStore.Mode = AddrModeFlat;
        stackFrame.AddrStack.Offset = context.IntSp;
        stackFrame.AddrStack.Mode = AddrModeFlat;
#else
#error "Platform not supported!"
#endif

        while (StackWalk64(machineType, process, thread, &stackFrame, &context, nullptr, SymFunctionTableAccess64, SymGetModuleBase64, nullptr)) {
            if (stackFrame.AddrPC.Offset == 0) {
                break;
            }

            try {
                auto stack = HStackframe();
                stack.Addresses = GetPointersInFrame(process, stackFrame.AddrPC.Offset);
            }
            catch (const std::exception& ex) {
            }
        }
    }

    HStacktrace::HStacktrace() {
        // Initialize symbol handling (needed to get function names and addresses)
        HANDLE process = GetCurrentProcess();
        HANDLE thread = GetCurrentThread();
        if (!SymInitialize(process, nullptr, true)) {
            throw std::runtime_error("Failed to initialize symbols");
        }

        // Walk the stack for the current thread
        WalkStack(process, thread);
    }
}