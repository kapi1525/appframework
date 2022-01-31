#pragma once
// Simple framework to help me with simple terminal programs
// I just add random stuff here that i happen need, you shouldnt really use it.
// Works on windows (msvc and MingW) and linux (gcc probably clang also but i didnt test it).


// Standard C++ stuff
#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <sstream>
#include <array>
#include <vector>
#include <deque>

// Standard C stuff
#include <assert.h>
#include <string.h>


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



typedef std::deque<std::string> args_t;    // Arguments type
args_t create_args(int argc, char const *argv[]);


// Use to store version information. Can be converted to string.
struct version_t {
    int major;
    int minor;
    int patch;

    std::string temp = std::string();

    operator const char*();
};


// Main app class
class app {
public:
    app();
    app(args_t args_f);
    virtual ~app();

    virtual void run() = 0;

    // stuff you can use
    args_t args;

    bool find_arg(std::string arg);              // Checks if specified argument was passed (will check for "-a" "--arg")
    std::string get_arg(std::string arg);        // Return string passed with argument (will check for "-a" "--arg")

    // Returns path where you can save configuration files per user.
    // AppData/Local/Appname in windows and /home/user/.config/Appname in linux
    std::filesystem::path get_appdata_path(std::string name); 
                                                              
    std::filesystem::path get_executable_path(); // Returns path of executable
    std::string get_executable_name();           // Returns name of executable
};

