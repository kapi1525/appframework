#include "appframework.hpp"


app::app() {
}

app::app(args_t args_f) {
    args = args_f;
}

app::~app() {
}

void app::exit(int status) {
    delete this;        // Delete app to call destructor on everything
    ::exit(status);     // Exit
}



args_t create_args(int argc, char const *argv[]) {
    args_t args;
    for (int i = 0; i < argc; i++) {
        args.push_back(std::string(argv[i]));
    }
    return args;
}

void run_appframework(app* app_ptr) {
    app_ptr->run();
    delete app_ptr;
}



version::operator const char*() {
    if (temp == "") {
        temp = "v" + std::to_string(major) + "." + std::to_string(minor) + "." + std::to_string(patch);
    }
    return temp.c_str();
}


terminal::terminal() {
    #ifdef _WIN32
    // Configure windows terminal to handle ANSI escape sequences
    /*HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    assert(hOut != INVALID_HANDLE_VALUE);
    DWORD dwMode = 0;
    assert(GetConsoleMode(hOut, &dwMode));
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    assert(SetConsoleMode(hOut, dwMode));*/

    // Set output mode to handle virtual terminal sequences
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
    assert(hOut != INVALID_HANDLE_VALUE);
    assert(hIn != INVALID_HANDLE_VALUE);

    DWORD dwOriginalOutMode = 0;
    DWORD dwOriginalInMode = 0;
    assert(GetConsoleMode(hOut, &dwOriginalOutMode));
    assert(GetConsoleMode(hIn, &dwOriginalInMode));

    DWORD dwRequestedOutModes = ENABLE_VIRTUAL_TERMINAL_PROCESSING | DISABLE_NEWLINE_AUTO_RETURN;
    // DWORD dwRequestedInModes = ENABLE_VIRTUAL_TERMINAL_INPUT;

    DWORD dwOutMode = dwOriginalOutMode | dwRequestedOutModes;
    DWORD dwInMode = dwOriginalInMode | ENABLE_VIRTUAL_TERMINAL_INPUT;

    if (!SetConsoleMode(hOut, dwOutMode)) {
        // we failed to set both modes, try to step down mode gracefully.
        dwRequestedOutModes = ENABLE_VIRTUAL_TERMINAL_PROCESSING;
        dwOutMode = dwOriginalOutMode | dwRequestedOutModes;
        assert(SetConsoleMode(hOut, dwOutMode));
    }

    assert(SetConsoleMode(hIn, dwInMode));
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



void terminal::set_color(rgb color) {
    std::cout << "\x1B[38;2;" << static_cast<int>(color.red) << ";" << static_cast<int>(color.green) << ";" << static_cast<int>(color.blue) << "m";
}

void terminal::set_back_color(rgb color) {
    std::cout << "\x1B[48;2;" << static_cast<int>(color.red) << ";" << static_cast<int>(color.green) << ";" << static_cast<int>(color.blue) << "m";
}


void terminal::reset_color() {
    std::cout << "\x1B[39m";
}

void terminal::reset_back_color() {
    std::cout << "\x1B[49m";
}


void terminal::reset() {
    /* :)
    reset_bold();
    reset_faint();
    reset_italic();
    reset_underline();
    reset_blinking();
    reset_inverse();
    reset_invisible();
    reset_strikethrough();
    reset_color();
    reset_back_color();
    */
    std::cout << "\x1B[0m";
}


void terminal::fatal(std::string message) {
    if(logging_level >= loglevel::fatal) {
        set_color({0,0,0});
        set_back_color({255,0,0});
        set_bold();
        std::cout << "[FATAL] " << message;
        reset();
        std::cout << std::endl;                 // endl to make sure buffer is flushed. After reseting to fix color glitches in gnome terminal.
    }
}

void terminal::error(std::string message) {
    if(logging_level >= loglevel::error) {
        set_color({255,0,0});
        set_bold();
        std::cout << "[ERROR] " << message;
        reset();
        std::cout << std::endl;                 // endl to make sure buffer is flushed. After reseting to fix color glitches in gnome terminal.
    }
}

void terminal::warn(std::string message) {
    if(logging_level >= loglevel::warn) {
        set_color({255,255,0});
        std::cout << "[WARN ] " << message;
        reset();
        std::cout << "\n";                      // After reseting to fix color glitches in gnome terminal.
    }
}

void terminal::info(std::string message) {
    if(logging_level >= loglevel::info) {
        std::cout << "[info ] " << message << "\n";
    }
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