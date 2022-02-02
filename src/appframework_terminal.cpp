#include "appframework_terminal.hpp"
// Definitions for terminal functions are at the bottom of appframework_terminal.hpp header.
// Those functions are inline so they need to be in header file.



/////////////////////////////
// Logging stuff
/////////////////////////////

logs::logs() {}
logs::~logs() {}


void logs::fatal(std::string_view message) {
    if(logging_level >= loglevel::fatal) {
        terminal::color({0,0,0});
        terminal::back_color({255,0,0});
        terminal::bold();
        std::cout << "[FATAL] " << message;
        terminal::reset();
        std::cout << std::endl;                 // endl to make sure buffer is flushed. After reseting to fix color glitches in gnome terminal.
    }
}

void logs::error(std::string_view message) {
    if(logging_level >= loglevel::error) {
        terminal::color({255,0,0});
        terminal::bold();
        std::cout << "[ERROR] " << message;
        terminal::reset();
        std::cout << std::endl;                 // endl to make sure buffer is flushed. After reseting to fix color glitches in gnome terminal.
    }
}

void logs::warn(std::string_view message) {
    if(logging_level >= loglevel::warn) {
        terminal::color({255,255,0});
        std::cout << "[WARN ] " << message;
        terminal::reset();
        std::cout << "\n";                      // After reseting to fix color glitches in gnome terminal.
    }
}

void logs::info(std::string_view message) {
    if(logging_level >= loglevel::info) {
        std::cout << "[info ] " << message << "\n";
    }
}



/////////////////////////////
// Args stuff
/////////////////////////////

args::args() {
}

args::args(int argc, char const *argv[]) {
    data.reserve(argc);
    for (int i = 0; i < argc; i++) {
        data.push_back(argv[i]);
        std::cout << data[i] << "\n";
    }
}


args::~args() {
}

// POSIX
// has("b")   -a     false
// has("b")   -b     true
// has("b")   -abc   true

// GNU
// has("abc") -abc   false
// has("abc") --abc  true
bool args::has(std::string_view arg_) {
    std::string arg(arg_);
    if (arg.size() == 1) {
        for (size_t i = 0; i < data.size(); i++) {
            if (!data[i].compare("-"+arg)) {
                return true;
            }
        }
    } else {
        for (size_t i = 0; i < data.size(); i++) {
            if (!data[i].compare("--"+arg)) {
                return true;
            }
        }
    }
    return false;
    /*
    if (posix_option_style && arg.size() == 1) {
        for (size_t i = 0; i < data.size(); i++) {
            if(data[i].at(0) == '-' && data[i].at(1) != '-') {
                std::cout << data[i][1] << "\n";
                for (size_t c = 1; c < data[i].size(); c++) {
                    if(data[i][c] == arg[0]) {
                        std::cout << "found posix arg " << arg << " in " << data[i] << "\n";
                        return true;
                    }
                }
            }
        }
    }
    
    if (gnu_option_style && arg.size() != 1) {
        for (size_t i = 0; i < data.size(); i++) {
            if(data[i][0] == '-' && data[i][1] == '-') {
                if(data[i].substr(2, data.size()) == arg) {
                    std::cout << "found gnu arg " << arg << " in " << data[i] << "\n";
                    return true;
                }
            }
        }
    }

    return false;*/
}

// get("o")   -a        ""
// get("o")   -o        ""
// get("o")   -oabc     ""
// get("o")   -o abc    "abc"
// get("out") -out      ""
// get("out") --out     ""
// get("out") --out=abc "abc"
// get("out") --out abc "abc"
std::string_view args::get(std::string_view arg_) {
    std::string arg(arg_);
    if (arg.size() == 1) {
        for (size_t i = 0; i < data.size(); i++) {
            if(!data[i].substr(0, arg.size()+1).compare("-"+arg)) {
                return data[i].substr(arg.size()+1, data[i].size());
            }
        }
    } else {
        for (size_t i = 0; i < data.size(); i++) {
            if(!data[i].substr(0, arg.size()+2).compare("--"+arg)) {
                return data[i].substr(arg.size()+2, data[i].size());
            }
        }
    }
    return "";
}