#pragma once
// Simple framework to help me with simple terminal programs
// I just add random stuff here that i happen to need, you shouldnt really use it.
// Works on windows (msvc and MingW) and linux (gcc probably clang also but i didnt test it).

#include "apf/common.hpp"
#include "apf/args.hpp"



namespace apf {

    // Main app class
    class app {
    public:
        app() {}
        app(args args) {}
        virtual void run() = 0;
        virtual ~app() {};


        // Fancy version of exit() that calls destructor of app for you.
        void exit(int status) {
            delete this;        // Delete app to call destructor on everything
            ::exit(status);     // Exit
        }


        // Framework version
        version appframework_version = {0,3,0};
    };


    inline void run_app(app* app_ptr) {
        app_ptr->run();
        delete app_ptr;
    }

};