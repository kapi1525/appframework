#include "appframework.hpp"


app::app() {
}

app::app(args_t args_f) {
    args = args_f;
}

app::~app() {
}



args_t create_args(int argc, char const *argv[]) {
    args_t args;
    for (int i = 0; i < argc; i++) {
        args.push_back(std::string(argv[i]));
    }
    return args;
}



bool app::find_arg(std::string arg) {
    if (arg.size() == 1) {
        for (size_t i = 0; i < args.size(); i++) {
            if (!args[i].compare("-"+arg)) {
                return true;
            }
        }
    } else {
        for (size_t i = 0; i < args.size(); i++) {
            if (!args[i].compare("--"+arg)) {
                return true;
            }
        }
    }
    return false;
}

std::string app::get_arg(std::string arg) {
    if (arg.size() == 1) {
        for (size_t i = 0; i < args.size(); i++) {
            if(!args[i].substr(0, arg.size()+1).compare("-"+arg)) {
                return args[i].substr(arg.size()+1, args[i].size());
            }
        }
    } else {
        for (size_t i = 0; i < args.size(); i++) {
            if(!args[i].substr(0, arg.size()+2).compare("--"+arg)) {
                return args[i].substr(arg.size()+2, args[i].size());
            }
        }
    }
    return "";
}


std::string app::get_appdata_path() {
    #ifdef _WIN32
    return ".";
    #elif __linux__
    return std::string(getpwuid(getuid())->pw_dir) + "/.config";
    #endif
}

std::string app::get_executable_path() {
    #ifdef _WIN32
    TCHAR Path[MAX_PATH];
    GetModuleFileName(NULL, Path, MAX_PATH);
    return std::filesystem::path(Path).parent_path().c_str();
    #elif __linux__
    return std::filesystem::read_symlink("/proc/self/exe").parent_path().c_str();
    #endif
}

std::string app::get_executable_name() {
    #ifdef _WIN32
    return ".";
    #elif __linux__
    std::string result;
    std::ifstream("/proc/self/comm") >> result;
    return result;
    #endif
}