#include "files.hpp"



/**
 * @brief Creates folder with passed name where you can save configuration files, its created in %appdata% in windows, home/user/.config in linux, no mac implementation yet.
 * 
 * @param name Name of the folder.
 * @return Path to created folder.
 */
std::filesystem::path files::user::appdata(std::string name) {
    std::filesystem::path appdata;
    #ifdef APF_WINDOWS
    appdata = GetKnownFolderPath(FOLDERID_LocalAppData);
    #elif defined(APF_LINUX)
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
    #ifdef APF_WINDOWS
    return  GetKnownFolderPath(FOLDERID_Profile).make_preferred();
    #elif defined(APF_POSIX)
    return std::filesystem::path(getpwuid(getuid())->pw_dir).make_preferred();
    #endif
}


#ifdef APF_LINUX
    ini xdg_user_dirs = std::filesystem::path(files::user::home() / ".config" / "user-dirs.dirs");
#endif // APF_LINUX



/**
 * @brief Returns path to users public folder.
 * 
 * @return Path to users public folder.directory
 */
std::filesystem::path files::user::public_folder() {
    #ifdef APF_WINDOWS
    return GetKnownFolderPath(FOLDERID_Public).make_preferred();
    #elif defined(APF_LINUX)
    std::string desktop = xdg_user_dirs.get_item("XDG_PUBLICSHARE");
    desktop.replace(desktop.find("$HOME"), 5, home());
    return desktop;
    #elif defined(APF_MAC)
    return home()/"Public";
    #endif
}



/**
 * @brief Returns path to users desktop folder.
 * 
 * @return Path to users desktop folder.
 */
std::filesystem::path files::user::desktop() {
    #ifdef APF_WINDOWS
    return GetKnownFolderPath(FOLDERID_Desktop).make_preferred();
    #elif defined(APF_LINUX)
    std::string desktop = xdg_user_dirs.get_item("XDG_DESKTOP_DIR");
    desktop.replace(desktop.find("$HOME"), 5, home());
    return desktop;
    #elif defined(APF_MAC)
    return home()/"Desktop";
    #endif
}



/**
 * @brief Returns path to users documents folder.
 * 
 * @return Path to users documents folder.
 */
std::filesystem::path files::user::documents() {
    #ifdef APF_WINDOWS
    return GetKnownFolderPath(FOLDERID_Documents).make_preferred();
    #elif defined(APF_LINUX)
    std::string documents = xdg_user_dirs.get_item("XDG_DOCUMENTS_DIR");
    documents.replace(documents.find("$HOME"), 5, home());
    return documents;
    #elif defined(APF_MAC)
    return home()/"Documents";
    #endif
}



/**
 * @brief Returns path to users music folder.
 * 
 * @return Path to users music folder.
 */
std::filesystem::path files::user::music() {
    #ifdef APF_WINDOWS
    return GetKnownFolderPath(FOLDERID_Music).make_preferred();
    #elif defined(APF_LINUX)
    std::string music = xdg_user_dirs.get_item("XDG_MUSIC_DIR");
    music.replace(music.find("$HOME"), 5, home());
    return music;
    #elif defined(APF_MAC)
    return home()/"Music";
    #endif
}



/**
 * @brief Returns path to users videos folder.
 * 
 * @return Path to users videos folder.
 */
std::filesystem::path files::user::videos() {
    #ifdef APF_WINDOWS
    return GetKnownFolderPath(FOLDERID_Videos).make_preferred();
    #elif defined(APF_LINUX)
    std::string videos = xdg_user_dirs.get_item("XDG_VIDEOS_DIR");
    videos.replace(videos.find("$HOME"), 5, home());
    return videos;
    #elif defined(APF_MAC)
    return home()/"Movies";
    #endif
}



/**
 * @brief Returns path to users photos folder.
 * 
 * @return Path to users photos folder.
 */
std::filesystem::path files::user::photos() {
    #ifdef APF_WINDOWS
    return GetKnownFolderPath(FOLDERID_Pictures).make_preferred();
    #elif defined(APF_LINUX)
    std::string photos = xdg_user_dirs.get_item("XDG_PICTURES_DIR");
    photos.replace(photos.find("$HOME"), 5, home());
    return photos;
    #elif defined(APF_MAC)
    return home()/"Pictures";
    #endif
}



/**
 * @brief Returns path to users downloads folder.
 * 
 * @return Path to users downloads directory.
 */
std::filesystem::path files::user::downloads() {
    #ifdef APF_WINDOWS
    return GetKnownFolderPath(FOLDERID_Downloads).make_preferred();
    #elif defined(APF_LINUX)
    std::string downloads = xdg_user_dirs.get_item("XDG_DOWNLOAD_DIR");
    downloads.replace(downloads.find("$HOME"), 5, home());
    return downloads;
    #elif defined(APF_MAC)
    return home()/"Downloads";
    #endif
}



/**
 * @brief Returns path to executable (without executable name).
 * 
 * @return Path to executable
 */
std::filesystem::path files::executable_path() {
    #ifdef APF_WINDOWS
    TCHAR Path[MAX_PATH];
    GetModuleFileName(NULL, Path, MAX_PATH);
    return std::filesystem::path(Path).parent_path();
    #elif defined(APF_LINUX)
    return std::filesystem::read_symlink("/proc/self/exe").parent_path();
    #elif defined(APF_MAC)
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
    #ifdef APF_WINDOWS
    TCHAR Path[MAX_PATH];
    GetModuleFileName(NULL, Path, MAX_PATH);
    return std::filesystem::path(Path).filename().string();
    #elif defined(APF_LINUX)
    std::string result;
    std::ifstream("/proc/self/comm") >> result;
    return result;
    #elif defined(APF_MAC)
    std::cerr << "Function: " << __func__ << "() is not implemented for MacOS yet.\n";
    std::cerr << "Calling abort().\n";
    abort();
    #endif
}




files::lock::lock() {
    clear_error();
}

files::lock::lock(logs::loglevel level) {
    log.loging_level = level;
}

files::lock::lock(std::filesystem::path file_path, bool block, logs::loglevel level) {
    log.loging_level = level;

    if(block) {
        lock_file(file_path);
    } else {
        try_lock_file(file_path);
    }
}

files::lock::~lock() {
    unlock_file();
}


bool files::lock::try_lock_file(std::filesystem::path file_path) {
    #ifdef APF_POSIX
    if(locked) {
        log.warn("File already locked, unlocking...");
        unlock_file();
    }

    error = lock_error::none;

    _open(file_path);

    file_lock.l_type = F_WRLCK;
    file_lock.l_whence = SEEK_SET;
    file_lock.l_start = 0;
    file_lock.l_len = 0;

    if(fcntl(file_descriptor, F_SETLK, &file_lock) == -1) {
        if (errno == EACCES || errno == EAGAIN) {
            log.info("Failed to lock file: File is already locked by other process.");
            error = lock_error::already_locked;
        } else {
            log.error("Failed to lock file: Unknown error.");
            error = lock_error::unknown;
        }
        
        _close();
        return false;
    }

    locked = true;

    log.info("Locked file.");
    return true;
    #else // APF_POSIX
    return true;
    #endif
}


bool files::lock::lock_file(std::filesystem::path file_path) {
    bool return_value;
    while (true) {
        return_value = try_lock_file(file_path);
        if(locked) {
            break;
        } else if(error == lock_error::already_locked) {
            log.info("File is already locked, going to sleep and trying again...");
            std::this_thread::sleep_for(100ms);
        }
    }
    return return_value;
}


bool files::lock::unlock_file() {
    #ifdef APF_POSIX
    if(!locked) {
        log.warn("File is not locked, no need for unlock_file().");
        return false;
    }

    file_lock.l_type = F_UNLCK;
    file_lock.l_whence = SEEK_SET;
    file_lock.l_start = 0;
    file_lock.l_len = 0;

    if(fcntl(file_descriptor, F_SETLK, &file_lock) == -1) {        
        log.error("Failed to unlock file: Unknown error.");

        _close();

        error = lock_error::unknown;
        return false;
    }

    _close();

    log.info("Unlocked file");

    locked = false;
    return true;
    
    #else // APF_POSIX
    return true;
    #endif
}


void files::lock::clear_error() {
    error = lock_error::none;
}