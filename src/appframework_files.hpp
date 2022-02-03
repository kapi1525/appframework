#pragma once
#include "appframework_common.hpp"

#ifdef __linux__
    // In linux to get path to translated versions of Desktop and other default folders i need to parse
    // user-dirs.dirs file which has simmilar syntax to ini so ini parser will do it.
    #include "appframework_ini.hpp"
#endif // __linux__



namespace files {
    namespace user {
        std::filesystem::path appdata(std::string name); // Path where you can save configuration files ( Creates folder in %localappdata% or /home/user/.config for you )
        std::filesystem::path home();                    // User home directory ( /home/user, C:/Users/user )
        
        // TODO: Make linux implementations better.
        std::filesystem::path desktop();   // User desktop folder
        std::filesystem::path documents(); // User documents folder
        std::filesystem::path music();     // User music folder
        std::filesystem::path videos();    // User videos folder
        std::filesystem::path photos();    // User photos folder
        std::filesystem::path downloads(); // User downloads folder

        #ifdef _WIN32
        // If someone uses this framwork you dont wanna use this function sinse its windows only and may be deleted anytime.
        inline std::filesystem::path GetKnownFolderPath(REFKNOWNFOLDERID folderid) {
            PWSTR pwstr;
            assert(SHGetKnownFolderPath(folderid, 0, NULL, &pwstr) == S_OK);
            std::filesystem::path temp(pwstr);
            CoTaskMemFree(pwstr);
            return temp;
        }
        #endif // _WIN32
    }


    std::filesystem::path executable_path(); // Returns path of executable
    std::string executable_name();           // Returns name of executable ( includes file extension )
}