#include "appframework.hpp"



class test_args : public app {
public:

    // -posix
    // -a argument
    // -b "very long option"
    // --long-option
    // --long-option-with-arg=argument
    // /windows
    // /windows-with-arg:argument

    test_args(::args args) {
        assert(args.has("p"));
        assert(args.has("o"));
        assert(args.has("s"));
        assert(args.has("i"));
        assert(args.has("x"));

        assert(args.get("a") == "argument");
        assert(args.get("b") == "very long option");
        
        assert(args.has("long-option"));
        assert(args.get("long-option-with-arg") == "argument");

        assert(args.has("windows"));
        assert(args.get("windows-with-arg") == "argument");
    }

    void run() {
    }

    ~test_args() {
    }
};


int main(int argc, char const *argv[]) {
    run_app(new test_args(args(argc, argv)));
    return 0;
}
