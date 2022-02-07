#include "files.hpp"



/**
 * @brief Creates folder with passed name where you can save configuration files, its created in %appdata% in windows, home/user/.config in linux, no mac implementation yet.
 * 
 * @param name Name of the folder.
 * @return Path to created folder.
 */
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



/**
 * @brief Returns path to user directory.
 * 
 * @return Path to user directory.
 */
std::filesystem::path files::user::home() {
    #ifdef _WIN32
    return  GetKnownFolderPath(FOLDERID_Profile).make_preferred();
    #elif defined(__unix__) || defined(__APPLE__)
    return std::filesystem::path(getpwuid(getuid())->pw_dir).make_preferred();
    #endif
}


#ifdef __linux__
    ini xdg_user_dirs = std::filesystem::path(files::user::home() / ".config" / "user-dirs.dirs");
#endif // __linux__



/**
 * @brief Returns path to users public folder.
 * 
 * @return Path to users public folder.directory
std::filesystem::path files::user::public_folder() {
    #ifdef _WIN32
    return GetKnownFolderPath(FOLDERID_Public).make_preferred();
    #elif __linux__
    std::string desktop = xdg_user_dirs.get_item("XDG_PUBLICSHARE");
    desktop.replace(desktop.find("$HOME"), 5, home());
    return desktop;
    #elif __APPLE__
    return home()/"Public";
    #endif
}



/**
 * @brief Returns path to users desktop folder.
 * 
 * @return Path to users desktop folder.
 */
std::filesystem::path files::user::desktop() {
    #ifdef _WIN32
    return GetKnownFolderPath(FOLDERID_Desktop).make_preferred();
    #elif __linux__
    std::string desktop = xdg_user_dirs.get_item("XDG_DESKTOP_DIR");
    desktop.replace(desktop.find("$HOME"), 5, home());
    return desktop;
    #elif __APPLE__
    return home()/"Desktop";
    #endif
}



/**
 * @brief Returns path to users documents folder.
 * 
 * @return Path to users documents folder.
 */
std::filesystem::path files::user::documents() {
    #ifdef _WIN32
    return GetKnownFolderPath(FOLDERID_Documents).make_preferred();
    #elif __linux__
    std::string documents = xdg_user_dirs.get_item("XDG_DOCUMENTS_DIR");
    documents.replace(documents.find("$HOME"), 5, home());
    return documents;
    #elif __APPLE__
    return home()/"Documents";
    #endif
}



/**
 * @brief Returns path to users music folder.
 * 
 * @return Path to users music folder.
 */
std::filesystem::path files::user::music() {
    #ifdef _WIN32
    return GetKnownFolderPath(FOLDERID_Music).make_preferred();
    #elif __linux__
    std::string music = xdg_user_dirs.get_item("XDG_MUSIC_DIR");
    music.replace(music.find("$HOME"), 5, home());
    return music;
    #elif __APPLE__
    return home()/"Music";
    #endif
}



/**
 * @brief Returns path to users videos folder.
 * 
 * @return Path to users videos folder.
 */
std::filesystem::path files::user::videos() {
    #ifdef _WIN32
    return GetKnownFolderPath(FOLDERID_Videos).make_preferred();
    #elif __linux__
    std::string videos = xdg_user_dirs.get_item("XDG_VIDEOS_DIR");
    videos.replace(videos.find("$HOME"), 5, home());
    return videos;
    #elif __APPLE__
    return home()/"Movies";
    #endif
}



/**
 * @brief Returns path to users photos folder.
 * 
 * @return Path to users photos folder.
 */
std::filesystem::path files::user::photos() {
    #ifdef _WIN32
    return GetKnownFolderPath(FOLDERID_Pictures).make_preferred();
    #elif __linux__
    std::string photos = xdg_user_dirs.get_item("XDG_PICTURES_DIR");
    photos.replace(photos.find("$HOME"), 5, home());
    return photos;
    #elif __APPLE__
    return home()/"Pictures";
    #endif
}



/**
 * @brief Returns path to users downloads folder.
 * 
 * @return Path to users downloads directory.
 */
std::filesystem::path files::user::downloads() {
    #ifdef _WIN32
    return GetKnownFolderPath(FOLDERID_Downloads).make_preferred();
    #elif __linux__
    std::string downloads = xdg_user_dirs.get_item("XDG_DOWNLOAD_DIR");
    downloads.replace(downloads.find("$HOME"), 5, home());
    return downloads;
    #elif __APPLE__
    return home()/"Downloads";
    #endif
}



/**
 * @brief Returns path to executable (without executable name).
 * 
 * @return Path to executable
 */
std::filesystem::path files::executable_path() {
    #ifdef _WIN32
    TCHAR Path[MAX_PATH];
    GetModuleFileName(NULL, Path, MAX_PATH);
    return std::filesystem::path(Path).parent_path();
    #elif __linux__
    return std::filesystem::read_symlink("/proc/self/exe").parent_path();
    #elif __APPLE__
    std::cerr << "Function: " << __func__ << "() is not implemented for MacOS yet.\n";
    std::cerr << "Calling abort().\n";
    abort();
    #endif
}



/**
 * @brief Returns name of executable.
 * 
 * @return Name of executable.
 */
std::string files::executable_name() {
    #ifdef _WIN32
    TCHAR Path[MAX_PATH];
    GetModuleFileName(NULL, Path, MAX_PATH);
    return std::filesystem::path(Path).filename().string();
    #elif __linux__
    std::string result;
    std::ifstream("/proc/self/comm") >> result;
    return result;
    #elif __APPLE__
    std::cerr << "Function: " << __func__ << "() is not implemented for MacOS yet.\n";
    std::cerr << "Calling abort().\n";
    abort();
    #endif
}