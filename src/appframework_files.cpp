#include "appframework_files.hpp"



std::filesystem::path files::user::appdata(std::string name) {
    std::filesystem::path appdata;
    #ifdef _WIN32
    appdata = GetKnownFolderPath(FOLDERID_LocalAppData);
    #elif __linux__
    appdata = std::filesystem::path(home() / ".config");
    #endif
    appdata.append(name).make_preferred();
    std::filesystem::create_directories(appdata);
    return appdata;
}

std::filesystem::path files::user::home() {
    #ifdef _WIN32
    return  GetKnownFolderPath(FOLDERID_Profile).make_preferred();
    #elif __linux__
    return std::filesystem::path(getpwuid(getuid())->pw_dir).make_preferred();
    #endif
}


std::filesystem::path files::user::desktop() {
    #ifdef _WIN32
    return  GetKnownFolderPath(FOLDERID_Desktop).make_preferred();
    #elif __linux__
    return ""; // TODO: THIS FOR LINUX.
    #endif
}

std::filesystem::path files::user::documents() {
    #ifdef _WIN32
    return  GetKnownFolderPath(FOLDERID_Documents).make_preferred();
    #elif __linux__
    return ""; // TODO: THIS FOR LINUX.
    #endif
}

std::filesystem::path files::user::music() {
    #ifdef _WIN32
    return  GetKnownFolderPath(FOLDERID_Music).make_preferred();
    #elif __linux__
    return ""; // TODO: THIS FOR LINUX.
    #endif
}

std::filesystem::path files::user::videos() {
    #ifdef _WIN32
    return  GetKnownFolderPath(FOLDERID_Videos).make_preferred();
    #elif __linux__
    return ""; // TODO: THIS FOR LINUX.
    #endif
}

std::filesystem::path files::user::photos() {
    #ifdef _WIN32
    return  GetKnownFolderPath(FOLDERID_Pictures).make_preferred();
    #elif __linux__
    return ""; // TODO: THIS FOR LINUX.
    #endif
}

std::filesystem::path files::user::downloads() {
    #ifdef _WIN32
    return  GetKnownFolderPath(FOLDERID_Downloads).make_preferred();
    #elif __linux__
    return ""; // TODO: THIS FOR LINUX.
    #endif
}




std::filesystem::path files::executable_path() {
    #ifdef _WIN32
    TCHAR Path[MAX_PATH];
    GetModuleFileName(NULL, Path, MAX_PATH);
    return std::filesystem::path(Path).parent_path();
    #elif __linux__
    return std::filesystem::read_symlink("/proc/self/exe").parent_path();
    #endif
}

std::string files::executable_name() {
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