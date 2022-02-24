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
        virtual ~app() {};

        virtual void start() = 0;
        virtual void run() = 0;
        virtual void end() = 0;

        args arguments;

        // Framework version
        version appframework_version = {0,3,0};
    };
}



// Beautiful macros
#define APF_RUN(app_class)                          \
    apf::app* app_ptr = new app_class;              \
    app_ptr->arguments = apf::args(argc, argv);     \
    app_ptr->start();                               \
    app_ptr->run();                                 \
    app_ptr->end();                                 \
    delete app_ptr;


#define APF_MAIN(app_class)                         \
    int main(int argc, char const *argv[]) {        \
        APF_RUN(app_class)                          \
    }
