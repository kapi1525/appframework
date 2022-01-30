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


std::filesystem::path app::get_appdata_path(std::string name) {
    std::filesystem::path appdata;
    #ifdef _WIN32
    PWSTR pwstr_localappdata;
    assert(SHGetKnownFolderPath(FOLDERID_LocalAppData, 0, NULL, &pwstr_localappdata) == S_OK);
    std::wstring localappdata = pwstr_localappdata;
    CoTaskMemFree(pwstr_localappdata);
    appdata = std::filesystem::path(localappdata) / name;
    #elif __linux__
    std::string home = getpwuid(getuid())->pw_dir;
    appdata(home / std::string(".config") / name);
    #endif
    appdata.make_preferred();
    std::filesystem::create_directories(appdata);
    return appdata;
}

std::filesystem::path app::get_executable_path() {
    #ifdef _WIN32
    TCHAR Path[MAX_PATH];
    GetModuleFileName(NULL, Path, MAX_PATH);
    return std::filesystem::path(Path).parent_path();
    #elif __linux__
    return std::filesystem::read_symlink("/proc/self/exe").parent_path();
    #endif
}

std::string app::get_executable_name() {
    #ifdef _WIN32
    TCHAR Path[MAX_PATH];
    GetModuleFileName(NULL, Path, MAX_PATH);
    return std::filesystem::path(Path).filename();
    #elif __linux__
    std::string result;
    std::ifstream("/proc/self/comm") >> result;
    return result;
    #endif
}