#pragma once
#include "common.hpp"
#include "term.hpp"



namespace apf {
    namespace log {
        inline void fatal(std::string_view message);
        inline void error(std::string_view message);
        inline void  warn(std::string_view message);
        inline void  info(std::string_view message);
        inline void  note(std::string_view message);

        inline void custom(std::string_view log_type, std::string_view message);
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
    custom("fatal", message);
}



/**
 * @brief Prints message as error.
 * 
 * @param message
 */
void apf::log::error(std::string_view message) {
    apf::term::color({255,0,0});
    apf::term::bold();
    custom("error", message);
}



/**
 * @brief Prints message as warning.
 * 
 * @param message
 */
void apf::log::warn(std::string_view message) {
    apf::term::color({255,255,0});
    custom("warn", message);
}



/**
 * @brief Prints message.
 * 
 * @param message
 */
void apf::log::info(std::string_view message) {
    custom("info", message);
}



/**
 * @brief Prints message.
 * 
 * @param message
 */
void apf::log::note(std::string_view message) {
    custom("note", message);
}



/**
 * @brief Prints message.
 * 
 * @param log_type
 * @param message
 */
void apf::log::custom(std::string_view log_type, std::string_view message) {
    std::cout << "[" << log_type << "] " << message;
    apf::term::reset();
    std::cout << "\n";
}