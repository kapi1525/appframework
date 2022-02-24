#pragma once
#include "common.hpp"
#include "term.hpp"



namespace apf {
    namespace log {
        inline void fatal(std::string_view message);
        inline void error(std::string_view message);
        inline void  warn(std::string_view message);
        inline void  info(std::string_view message);
    }
}



/**
 * @brief Prints message as fatal error, fatal error is error from which program cant recover.
 * 
 * @param message 
 */
void apf::log::fatal(std::string_view message) {
    apf::term::color({0,0,0});
    apf::term::back_color({255,0,0});
    apf::term::bold();
    std::cout << "[FATAL] " << message;
    apf::term::reset();
    std::cout << std::endl;                 // endl to make sure buffer is flushed. After reseting to fix color glitches in gnome terminal.
}



/**
 * @brief Prints message as error.
 * 
 * @param message 
 */
void apf::log::error(std::string_view message) {
    apf::term::color({255,0,0});
    apf::term::bold();
    std::cout << "[ERROR] " << message;
    apf::term::reset();
    std::cout << std::endl;                 // endl to make sure buffer is flushed. After reseting to fix color glitches in gnome terminal.
}



/**
 * @brief Prints message as warning.
 * 
 * @param message 
 */
void apf::log::warn(std::string_view message) {
    apf::term::color({255,255,0});
    std::cout << "[WARN ] " << message;
    apf::term::reset();
    std::cout << "\n";                      // After reseting to fix color glitches in gnome terminal.
}



/**
 * @brief Prints message.
 * 
 * @param message 
 */
void apf::log::info(std::string_view message) {
    std::cout << "[info ] " << message << "\n";
}