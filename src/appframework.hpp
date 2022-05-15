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
        virtual void end() = 0;

        virtual int run() = 0;


        args arguments;

        // Framework version
        version appframework_version = {0,4,1};
    };
}



// Beautiful macros
#define APF_RUN(app_class)                                      \
    apf::app* app_ptr = (apf::app*)new app_class;               \
    app_ptr->arguments = apf::args(argc, argv);                 \
    app_ptr->start();                                           \
    while(app_ptr->run() == 0) {}                               \
    app_ptr->end();                                             \
    delete app_ptr;


#define APF_TEST_RUN(app_class)                                 \
    apf::app* app_ptr = (apf::app*)new app_class;               \
    apf::log::info("apf" + app_ptr->appframework_version.temp); \
    app_ptr->arguments = apf::args(argc, argv);                 \
    app_ptr->start();                                           \
    while(app_ptr->run() == 0) {}                               \
    app_ptr->end();                                             \
    delete app_ptr;


#define APF_MAIN(app_class) int main(int argc, char const *argv[]) { APF_RUN(app_class) }
#define APF_TEST_MAIN(app_class) int main(int argc, char const *argv[]) { APF_TEST_RUN(app_class) }
