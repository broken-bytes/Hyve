@echo off
setlocal EnableDelayedExpansion

clang -emit-llvm -c hyvestd/llvm/low_level.ll -o build/low_level.bc

REM Rebuild the cmake project with the bootstrap flag
cmake -B build -S . -DHYVE_BOOTSTRAP=ON

MSBUILD build/Hyve.sln -p:Configuration=Debug -p:Platform=x64

start "" "build/Debug/hyvec.exe" -c "D/Projects/Hyve/hyvestd/hyve/builtin/Primitives.hyve"

