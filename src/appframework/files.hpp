#pragma once
#include "common.hpp"
#include "terminal.hpp" // For logs

#ifdef APF_LINUX
    // In linux to get path to translated versions of Desktop and other default folders i need to parse
    // user-dirs.dirs file which has simmilar syntax to ini so ini parser will do it.
    #include "ini.hpp"
#endif // APF_LINUX



namespace files {
    namespace user {
        std::filesystem::path appdata(std::string name); // Path where you can save configuration files ( Creates folder in %localappdata% or /home/user/.config for you )
        std::filesystem::path home();                    // User home directory ( /home/user, C:/Users/user )
        
        // TODO: Make linux implementations better.
        std::filesystem::path public_folder();  // User public folder (i cant name this "public()" cause of "public" keyword)

        std::filesystem::path desktop();        // User desktop folder
        std::filesystem::path documents();      // User documents folder
        std::filesystem::path music();          // User music folder
        std::filesystem::path videos();         // User videos folder
        std::filesystem::path photos();         // User photos folder
        std::filesystem::path downloads();      // User downloads folder

        #ifdef APF_WINDOWS
        // If someone uses this framwork you dont wanna use this function since its windows only and may be deleted anytime.
        inline std::filesystem::path GetKnownFolderPath(REFKNOWNFOLDERID folderid) {
            PWSTR pwstr;
            assert(SHGetKnownFolderPath(folderid, 0, NULL, &pwstr) == S_OK);
            std::filesystem::path temp(pwstr);
            CoTaskMemFree(pwstr);
            return temp;
        }
        #endif // APF_WINDOWS
    }

    std::filesystem::path executable_path(); // Returns path of executable
    std::string executable_name();           // Returns name of executable ( includes file extension )


    class lock {
    public:
        lock();
        lock(logs::loglevel level);
        lock(std::filesystem::path file_path, bool block = false, logs::loglevel level = logs::loglevel::fatal);
        ~lock();

        // Very descriptive errors :)
        enum class lock_error {
            none,
            invalid_file,
            already_locked,
            unknown,
        };

        lock_error error = lock_error::none;
        bool locked = false;

        bool try_lock_file(std::filesystem::path file_path);    // Try to lock file return false if failed
        bool lock_file(std::filesystem::path file_path);        // Lock file wait if already locked
        bool unlock_file();

        void clear_error();

    private:
        logs log;

    #ifdef APF_POSIX
        struct flock file_lock;
        int file_descriptor = 0;
    #endif // APF_POSIX

    };
}