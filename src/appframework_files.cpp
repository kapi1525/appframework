#include "appframework_files.hpp"



std::filesystem::path files::get_appdata_path(std::string name) {
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

std::filesystem::path files::get_executable_path() {
    #ifdef _WIN32
    TCHAR Path[MAX_PATH];
    GetModuleFileName(NULL, Path, MAX_PATH);
    return std::filesystem::path(Path).parent_path();
    #elif __linux__
    return std::filesystem::read_symlink("/proc/self/exe").parent_path();
    #endif
}

std::string files::get_executable_name() {
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