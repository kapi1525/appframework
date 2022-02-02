#pragma once
#include "appframework_common.hpp"



namespace files {
    // TODO: get_user_path() C:/Users/user - /home/user
    // TODO: create_desktop_link()
    // TODO: add more functions

    // Returns path where you can save configuration files per user.
    // AppData/Local/Appname in windows and /home/user/.config/Appname in linux
    std::filesystem::path get_appdata_path(std::string name);

    std::filesystem::path get_executable_path(); // Returns path of executable
    std::string get_executable_name();           // Returns name of executable
}