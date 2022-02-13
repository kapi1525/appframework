#include "appframework.hpp"



class test_args : public apf::app {
public:

    // -posix
    // -a argument
    // -b "very long option"
    // --long-option
    // --long-option-with-arg=argument
    // /windows
    // /windows-with-arg:argument

    void start() {
        assert(arguments.has("p"));
        assert(arguments.has("o"));
        assert(arguments.has("s"));
        assert(arguments.has("i"));
        assert(arguments.has("x"));

        assert(arguments.get("a") == "argument");
        assert(arguments.get("b") == "very long option");
        
        assert(arguments.has("long-option"));
        assert(arguments.get("long-option-with-arg") == "argument");

        assert(arguments.has("windows"));
        assert(arguments.get("windows-with-arg") == "argument");
    }

    void run() {
    }

    void end() {
    }
};



APF_MAIN(test_args)