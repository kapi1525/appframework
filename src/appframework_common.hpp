#pragma once
// This header contains includes used by rest of appframework


// Standard C++ stuff
#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <string_view>
#include <vector>
#include <deque>

// Standard C stuff
#include <cassert>


// windows stuff
#ifdef _WIN32
    #define WIN32_LEAN_AND_MEAN
    #include <windows.h>
    #include <shlobj.h>     // SHGetKnownFolderPath
#endif // _WIN32

// linux stuff
#ifdef __linux__
    #include <unistd.h>
    #include <sys/types.h>
    #include <pwd.h>
#endif // __linux__