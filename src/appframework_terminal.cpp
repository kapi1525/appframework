#include "appframework_terminal.hpp"
// Definitions for terminal functions are at the bottom of appframework_terminal.hpp header.
// Those functions are inline so they need to be in header file.



/////////////////////////////
// Logging stuff
/////////////////////////////

logs::logs() {}
logs::~logs() {}


void logs::fatal(std::string_view message) {
    if(loging_level >= loglevel::fatal) {
        terminal::color({0,0,0});
        terminal::back_color({255,0,0});
        terminal::bold();
        std::cout << "[FATAL] " << message;
        terminal::reset();
        std::cout << std::endl;                 // endl to make sure buffer is flushed. After reseting to fix color glitches in gnome terminal.
    }
}

void logs::error(std::string_view message) {
    if(loging_level >= loglevel::error) {
        terminal::color({255,0,0});
        terminal::bold();
        std::cout << "[ERROR] " << message;
        terminal::reset();
        std::cout << std::endl;                 // endl to make sure buffer is flushed. After reseting to fix color glitches in gnome terminal.
    }
}

void logs::warn(std::string_view message) {
    if(loging_level >= loglevel::warn) {
        terminal::color({255,255,0});
        std::cout << "[WARN ] " << message;
        terminal::reset();
        std::cout << "\n";                      // After reseting to fix color glitches in gnome terminal.
    }
}

void logs::info(std::string_view message) {
    if(loging_level >= loglevel::info) {
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
    }
}

args::~args() {
}


bool args::has(std::string_view arg) {
    // POSIX options style ( single charachter options that start with "-", can have argument and can be joined together )
    if (arg.size() == 1) {
        for (size_t arg_i = 0; arg_i < data.size(); arg_i++) {
            if (data[arg_i][0] == '-' && data[arg_i][1] != '-') {
                for (size_t i = 1; i < data[arg_i].size(); i++) {
                    if (data[arg_i][i] == arg[0]) {
                        // std::cout << "Found arg " << arg << " in " << data[arg_i] << "\n";
                        return true;
                    }
                }
            }
        }
    }
    

    // GNU options style ( GNU adds long options they start with "--" )
    if (arg.size() != 1) {
        for (size_t arg_i = 0; arg_i < data.size(); arg_i++) {
            if((!data[arg_i].compare(0, 2, "--") && !data[arg_i].compare(2, arg.size(), arg)) && (data[arg_i].size() == arg.size()+2 || data[arg_i][arg.size()+2] == '=')) {
                // std::cout << "Found arg " << arg << " in " << data[arg_i] << "\n";
                return true;
            }
        }
    }


    // Windows options style ( starts with "/" options can be longer than 1 character and have arguments by adding ":" )
    for (size_t arg_i = 0; arg_i < data.size(); arg_i++) {
        if((!data[arg_i].compare(0, 1, "/") && !data[arg_i].compare(1, arg.size(), arg)) && (data[arg_i].size() == arg.size()+1 || data[arg_i][arg.size()+1] == ':')) {
            // std::cout << "Found arg " << arg << " in " << data[arg_i] << "\n";
            return true;
        }
    }

    return false;
}

std::string_view args::get(std::string_view arg) {
    // POSIX options style ( single charachter options that start with "-", can have argument and can be joined together )
    if (arg.size() == 1) {
        for (size_t arg_i = 0; arg_i < data.size(); arg_i++) {
            if (data[arg_i][0] == '-' && data[arg_i][1] != '-') {
                for (size_t i = 1; i < data[arg_i].size(); i++) {
                    if (data[arg_i][i] == arg[0]) {
                        if (data[arg_i+1][0] != '-' && data[arg_i+1][0] != '/') {
                            return data[arg_i+1];
                        }
                    }
                }
            }
        }
    }
    

    // GNU options style ( GNU adds long options they start with "--" )
    if (arg.size() != 1) {
        for (size_t arg_i = 0; arg_i < data.size(); arg_i++) {
            if((!data[arg_i].compare(0, 2, "--") && !data[arg_i].compare(2, arg.size(), arg)) && (data[arg_i].size() == arg.size()+2 || data[arg_i][arg.size()+2] == '=')) {
                if(data[arg_i][arg.size()+2] == '=') {
                    std::string_view sv(data[arg_i].c_str(), data[arg_i].size());
                    sv.remove_prefix(arg.size()+3);
                    return sv;
                }
            }
        }
    }


    // Windows options style ( starts with "/" options can be longer than 1 character and have arguments by adding ":" )
    for (size_t arg_i = 0; arg_i < data.size(); arg_i++) {
        if((!data[arg_i].compare(0, 1, "/") && !data[arg_i].compare(1, arg.size(), arg)) && (data[arg_i].size() == arg.size()+1 || data[arg_i][arg.size()+1] == ':')) {
            if(data[arg_i][arg.size()+1] == ':') {
                std::string_view sv(data[arg_i].c_str(), data[arg_i].size());
                sv.remove_prefix(arg.size()+2);
                return sv;
            }
        }
    }

    return "";
}