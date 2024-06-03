:: Get the LLVM project binaries and extract them
curl -L "https://github.com/llvm/llvm-project/releases/download/llvmorg-18.1.6/clang+llvm-18.1.6-x86_64-pc-windows-msvc.tar.xz" --output llvm.tar.xz
tar -xf llvm.tar.xz

:: Create the deps/llvm directory if it doesn't exist
mkdir deps\llvm

:: Move the extracted files into deps/llvm
robocopy clang+llvm-18.1.6-x86_64-pc-windows-msvc deps\llvm /E /MOVE

:: Remove the tar file
del llvm.tar.xz

:: Get libuv and extract it
curl -L "https://dist.libuv.org/dist/v1.48.0/libuv-v1.48.0-dist.tar.gz" --output libuv.tar.gz
tar -xf libuv.tar.gz

:: Create the deps/libuv directory if it doesn't exist
mkdir deps\libuv

:: Move the extracted files into deps/libuv
robocopy libuv-1.48.0 deps\libuv /E /MOVE

:: Remove the tar file
del libuv.tar.gz

:: Get libsodium and extract it
curl -L "https://download.libsodium.org/libsodium/releases/libsodium-1.0.20-stable.tar.gz" --output libsodium.tar.gz
tar -xf libsodium.tar.gz

:: Create the deps/libsodium directory if it doesn't exist
mkdir deps\libsodium

:: Move the extracted files into deps/libsodium
robocopy libsodium-stable deps\libsodium /E /MOVE

:: Remove the tar file
del libsodium.tar.gz

:: Get lib-icu
curl -L "https://github.com/unicode-org/icu/releases/download/release-75-1/icu4c-75_1-Win64-MSVC2022.zip" --output icu.zip

:: Create the deps/icu directory if it doesn't exist
mkdir deps\icu

:: Extract the zip file in place
tar -xf icu.zip -C deps\icu

:: Remove the zip file
del icu.zip