#pragma once
// Simple framework to help me with simple terminal programs
// I just add random stuff here that i happen to need, you shouldnt really use it.
// Works on windows (msvc and MingW) and linux (gcc probably clang also but i didnt test it).

#include "common.hpp"
#include "types.hpp"
#include "terminal.hpp"
#include "files.hpp"
#include "ini.hpp"



// Main app class
class app {
public:
    app();
    app(args args);
    virtual void run() = 0;
    virtual ~app();

    void exit(int status);      // Fancy version of exit() that calls destructor of app for you.

    // Framework version
    version appframework_version = {0,2,0};

    // stuff you can use
    logs log;                  // Use to log stuff.
};



void run_app(app* app_ptr);