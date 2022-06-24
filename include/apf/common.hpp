#pragma once
// This header contains includes used by rest of appframework



// TODO: Remove all includes
// Standard C++ stuff
#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <string>
#include <string_view>
#include <vector>
#include <deque>
#include <thread>
#include <chrono>

// Standard C stuff
#include <cassert>



// Platform specific macros that are little bit easier to remember
#ifdef _WIN32
    #define APF_WINDOWS
#endif

#if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
    #define APF_POSIX
#endif

#ifdef __linux__
    #define APF_LINUX
#endif

#ifdef __APPLE__
    #define APF_MAC
#endif


// Compiler macros that are also easier to remember
#ifdef _MSC_VER
    #define APF_MSVC
#endif

#ifdef __GNUC__
    #define APF_GCC
#endif

#ifdef __clang__
    #define APF_CLANG
#endif



// windows stuff
#ifdef APF_WINDOWS
    #define WIN32_LEAN_AND_MEAN
    #include <windows.h>

    #ifdef _MSC_VER
        #include <BaseTsd.h>        // for SSIZE_T
        using ssize_t = SSIZE_T;    // For convenience
    #endif // _MSC_VER

#endif // APF_WINDOWS



// posix stuff
#ifdef APF_POSIX
#endif // APF_POSIX


// linux stuff
#ifdef APF_LINUX
#endif // APF_LINUX


// mac stuff
#ifdef APF_MAC
#endif // APF_MAC
