#pragma once
// This header contains includes used by rest of appframework


// Standard C++ stuff
#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <string_view>
#include <vector>
#include <thread>
#include <chrono>

using namespace std::chrono_literals;

// Standard C stuff
#include <cassert>



// Platform specific macros that are little bit easier to remember
#ifdef _WIN32
    #define APF_WINDOWS
#endif

#if defined(__unix__) || defined(__APPLE__)
    #define APF_POSIX
#endif

#ifdef __linux__
    #define APF_LINUX
#endif

#ifdef __APPLE__
    #define APF_MAC
#endif



// windows stuff
#ifdef APF_WINDOWS
    #define WIN32_LEAN_AND_MEAN
    #include <windows.h>
    #include <shlobj.h>     // SHGetKnownFolderPath

    #ifdef _MSC_VER
        #include <BaseTsd.h>
    #endif // _MSC_VER

#endif // APF_WINDOWS


// posix stuff
#ifdef APF_POSIX
    #include <stdlib.h>
    #include <unistd.h>
    #include <fcntl.h>
    #include <errno.h>
    #include <stdio.h>
    #include <pwd.h>
    #include <sys/types.h>
#endif // APF_POSIX


// linux stuff
#ifdef APF_LINUX
#endif


// mac stuff
#ifdef APF_MAC
    #include <mach-o/dyld.h>
#endif // APF_MAC