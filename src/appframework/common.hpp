#pragma once
// This header contains includes used by rest of appframework


// Standard C++ stuff
#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <string_view>
#include <vector>

// Standard C stuff
#include <cassert>


// windows stuff
#ifdef _WIN32
    #define WIN32_LEAN_AND_MEAN
    #include <windows.h>
    #include <shlobj.h>     // SHGetKnownFolderPath

    #ifdef _MSC_VER
        #include <BaseTsd.h>
    #endif // _MSC_VER

#endif // _WIN32

// linux stuff
#ifdef __linux__
    #include <unistd.h>
    #include <pwd.h>
    #include <sys/types.h>
#endif // __linux__