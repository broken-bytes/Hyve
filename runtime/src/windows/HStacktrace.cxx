#include "runtime/HStacktrace.hxx"
#include <iostream>
#include <vector>
#include <Windows.h>
#include <DbgHelp.h>

namespace Hyve::Runtime {
#include <windows.h>
#include <dbghelp.h>
#include <stdio.h>

#pragma comment(lib, "dbghelp.lib")

#define MAX_OBJECTS 1024 // Example maximum number of allocated objects
    std::vector<uintptr_t> TraverseStackFrame(DWORD64 stackAddr, DWORD64 frameAddr) {
        DWORD64* stackPtr = (DWORD64*)stackAddr;
        DWORD64* framePtr = (DWORD64*)frameAddr;

        std::vector<uintptr_t> pointers;

        // Assuming stack variables are DWORD64 integers for simplicity
        for (int i = 0; i < 10; i++) { // Adjust the range according to your stack depth
            DWORD64 potentialPointer = *(stackPtr + i);
               pointers.push_back(potentialPointer);
        }

        for (int i = 0; i < 10; i++) { // Adjust the range according to your frame depth
            DWORD64 potentialPointer = *(framePtr + i);
            pointers.push_back(potentialPointer);
        }

        return pointers;
    }

    std::vector<HStackframe> TraverseStackTrace(CONTEXT* context) {
        HANDLE process = GetCurrentProcess();
        HANDLE thread = GetCurrentThread();

        std::vector<HStackframe> pointers;

        SymInitialize(process, NULL, TRUE);

        STACKFRAME64 stackFrame;
        memset(&stackFrame, 0, sizeof(STACKFRAME64));

        DWORD imageType;
#ifdef _M_IX86
        imageType = IMAGE_FILE_MACHINE_I386;
        stackFrame.AddrPC.Offset = context->Eip;
        stackFrame.AddrPC.Mode = AddrModeFlat;
        stackFrame.AddrFrame.Offset = context->Ebp;
        stackFrame.AddrFrame.Mode = AddrModeFlat;
        stackFrame.AddrStack.Offset = context->Esp;
        stackFrame.AddrStack.Mode = AddrModeFlat;
#elif _M_X64
        imageType = IMAGE_FILE_MACHINE_AMD64;
        stackFrame.AddrPC.Offset = context->Rip;
        stackFrame.AddrPC.Mode = AddrModeFlat;
        stackFrame.AddrFrame.Offset = context->Rbp;
        stackFrame.AddrFrame.Mode = AddrModeFlat;
        stackFrame.AddrStack.Offset = context->Rsp;
        stackFrame.AddrStack.Mode = AddrModeFlat;
#elif _M_IA64
        imageType = IMAGE_FILE_MACHINE_IA64;
        stackFrame.AddrPC.Offset = context->StIIP;
        stackFrame.AddrPC.Mode = AddrModeFlat;
        stackFrame.AddrFrame.Offset = context->IntSp;
        stackFrame.AddrFrame.Mode = AddrModeFlat;
        stackFrame.AddrBStore.Offset = context->RsBSP;
        stackFrame.AddrBStore.Mode = AddrModeFlat;
        stackFrame.AddrStack.Offset = context->IntSp;
        stackFrame.AddrStack.Mode = AddrModeFlat;
#else
#error "Unsupported platform"
#endif

        for (int frame = 0; frame < 64; frame++) {
            if (!StackWalk64(imageType, process, thread, &stackFrame, context, NULL, SymFunctionTableAccess64, SymGetModuleBase64, NULL)) {
                break;
            }

            printf("Frame %d: PC = %p, Frame = %p, Stack = %p\n", frame, (void*)stackFrame.AddrPC.Offset, (void*)stackFrame.AddrFrame.Offset, (void*)stackFrame.AddrStack.Offset);

            if (stackFrame.AddrPC.Offset == 0) {
                break;
            }

            HStackframe hStackFrame;
            hStackFrame.Addresses = TraverseStackFrame(stackFrame.AddrStack.Offset, stackFrame.AddrFrame.Offset);

            pointers.push_back(hStackFrame);
        }

        SymCleanup(process);

        return pointers;
    }

    std::vector<HStackframe> CaptureStackTrace() {
        CONTEXT context;
        RtlCaptureContext(&context);

        return TraverseStackTrace(&context);
    }

    HStacktrace::HStacktrace() {
        _frames = CaptureStackTrace();
    }
}
