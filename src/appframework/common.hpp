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


// unix stuff
#ifdef __unix__
    #include <unistd.h>
    #include <pwd.h>
    #include <sys/types.h>
#endif // __unix__


// Dont mind this.
#if 0
size_t alloc_count = 0;
size_t alloc_size = 0;
void* operator new(size_t size) {
    alloc_count++;
    alloc_size = alloc_size+size;
    std::cout << "Allocating: " << size << " bytes...  Total memory allocated: " << alloc_size <<" bytes.  Total allocations: " << alloc_count << "\n";
    return malloc(size);
}
#endif