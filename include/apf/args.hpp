#pragma once
#include "common.hpp"



namespace apf {
    class args {
    public:
        args(int argc = 1, char const *argv[] = 0);
        ~args();

        bool has(std::string_view arg);
        std::string_view get(std::string_view arg);

    private:
        std::vector<std::string_view> data;
    };
}



inline apf::args::args(int argc, char const *argv[]) {
    data.reserve(argc - 1);
    for (int i = 1; i < argc; i++) {
        data.push_back(argv[i]);
    }
}

inline apf::args::~args() {
}


inline bool apf::args::has(std::string_view arg) {
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

inline std::string_view apf::args::get(std::string_view arg) {
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
                    // std::string_view sv(data[arg_i].c_str(), data[arg_i].size());
                    std::string_view sv(data[arg_i]);
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
                std::string_view sv(data[arg_i]);
                sv.remove_prefix(arg.size()+2);
                return sv;
            }
        }
    }

    return "";
}