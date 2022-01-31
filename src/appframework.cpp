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


version_t::operator const char*() {
    if (temp == "") {
        temp = "v" + std::to_string(major) + "." + std::to_string(minor) + "." + std::to_string(patch);
    }
    return temp.c_str();
}


terminal::terminal() {
    #ifdef _WIN32
    // Configure windows terminal to handle ANSI escape sequences
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    assert(hOut != INVALID_HANDLE_VALUE);
    DWORD dwMode = 0;
    assert(GetConsoleMode(hOut, &dwMode));
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    assert(SetConsoleMode(hOut, dwMode));
    #endif // _WIN32
}

terminal::~terminal() {
    // Reset terminal at the end.
    reset();
}


void terminal::set_bold() {
    std::cout << "\x1B[1m";
}

void terminal::set_faint() {
    std::cout << "\x1B[2m";
}

void terminal::set_italic() {
    std::cout << "\x1B[3m";
}

void terminal::set_underline() {
    std::cout << "\x1B[4m";
}

void terminal::set_blinking() {
    std::cout << "\x1B[5m";
}

void terminal::set_inverse() {
    std::cout << "\x1B[7m";
}

void terminal::set_invisible() {
    std::cout << "\x1B[8m";
}

void terminal::set_strikethrough() {
    std::cout << "\x1B[9m";
}


void terminal::reset_bold() {
    std::cout << "\x1B[22m";
}

void terminal::reset_faint() {
    std::cout << "\x1B[23m";
}

void terminal::reset_italic() {
    std::cout << "\x1B[24m";
}

void terminal::reset_underline() {
    std::cout << "\x1B[25m";
}

void terminal::reset_blinking() {
    std::cout << "\x1B[26m";
}

void terminal::reset_inverse() {
    std::cout << "\x1B[27m";
}

void terminal::reset_invisible() {
    std::cout << "\x1B[28m";
}

void terminal::reset_strikethrough() {
    std::cout << "\x1B[29m";
}



void terminal::set_color(rgb_t color) {
    std::cout << "\x1B[38;2;" << color.red << ";" << color.green << ";" << color.blue << "m";
}

void terminal::set_back_color(rgb_t color) {
    std::cout << "\x1B[48;2;" << color.red << ";" << color.green << ";" << color.blue << "m";
}


void terminal::reset_color() {
    std::cout << "\x1B[39m";
}

void terminal::reset_back_color() {
    std::cout << "\x1B[49m";
}


void terminal::reset() {
    /*reset_bold();
    reset_faint();
    reset_italic();
    reset_underline();
    reset_blinking();
    reset_inverse();
    reset_invisible();
    reset_strikethrough();
    reset_color();
    reset_back_color();*/
    std::cout << "\x1B[0m";
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
    std::filesystem::path home(getpwuid(getuid())->pw_dir);
    appdata = std::filesystem::path(home / ".config" / name);
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
    return std::filesystem::path(Path).filename().string();
    #elif __linux__
    std::string result;
    std::ifstream("/proc/self/comm") >> result;
    return result;
    #endif
}