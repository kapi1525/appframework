#include "files.hpp"



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


#ifdef __linux__
    ini user_dirs = std::filesystem::path(files::user::home() / ".config" / "user-dirs.dirs");
#endif // __linux__


std::filesystem::path files::user::desktop() {
    #ifdef _WIN32
    return  GetKnownFolderPath(FOLDERID_Desktop).make_preferred();
    #elif __linux__
    std::string desktop = user_dirs.get_item("XDG_DESKTOP_DIR");
    desktop.replace(desktop.find("$HOME"), 5, home());
    return desktop;
    #endif
}

std::filesystem::path files::user::documents() {
    #ifdef _WIN32
    return  GetKnownFolderPath(FOLDERID_Documents).make_preferred();
    #elif __linux__
    std::string documents = user_dirs.get_item("XDG_DOCUMENTS_DIR");
    documents.replace(documents.find("$HOME"), 5, home());
    return documents;
    #endif
}

std::filesystem::path files::user::music() {
    #ifdef _WIN32
    return  GetKnownFolderPath(FOLDERID_Music).make_preferred();
    #elif __linux__
    std::string music = user_dirs.get_item("XDG_MUSIC_DIR");
    music.replace(music.find("$HOME"), 5, home());
    return music;
    #endif
}

std::filesystem::path files::user::videos() {
    #ifdef _WIN32
    return  GetKnownFolderPath(FOLDERID_Videos).make_preferred();
    #elif __linux__
    std::string videos = user_dirs.get_item("XDG_VIDEOS_DIR");
    videos.replace(videos.find("$HOME"), 5, home());
    return videos;
    #endif
}

std::filesystem::path files::user::photos() {
    #ifdef _WIN32
    return  GetKnownFolderPath(FOLDERID_Pictures).make_preferred();
    #elif __linux__
    std::string photos = user_dirs.get_item("XDG_PICTURES_DIR");
    photos.replace(photos.find("$HOME"), 5, home());
    return photos;
    #endif
}

std::filesystem::path files::user::downloads() {
    #ifdef _WIN32
    return  GetKnownFolderPath(FOLDERID_Downloads).make_preferred();
    #elif __linux__
    std::string downloads = user_dirs.get_item("XDG_DOWNLOAD_DIR");
    downloads.replace(downloads.find("$HOME"), 5, home());
    return downloads;
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