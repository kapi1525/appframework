#pragma once
#include "common.hpp"
#include "term.hpp"



namespace apf {

    enum class log_level {
        none,
        fatal,
        error,
        warn,
        info,
        max,
    };


    class log {
    public:
        static void fatal(std::string message);
        static void error(std::string message);
        static void warn(std::string message);
        static void info(std::string message);
        static void note(std::string message);

        static void custom(std::string log_label, std::string message, log_level lvl = log_level::max, rgb label_color = {255, 255, 255}, rgb label_back_color = {0, 0, 0});

        static void set_level(log_level lvl);
        static log_level get_level();


    private:
        log() = default;
        
        static log& get();

        log_level level = log_level::max;
    };
}


inline apf::log& apf::log::get() {
    static apf::log instance;
    return instance;
}


/**
 * @brief Print message.
 * 
 * @param message 
 */
inline void apf::log::fatal(std::string message) {
    custom("fatal", message, log_level::fatal, {0, 0, 0}, {255, 0, 0});
}

/**
 * @brief Print message.
 * 
 * @param message 
 */
inline void apf::log::error(std::string message) {
    custom("error", message, log_level::error, {255, 0, 0});
}

/**
 * @brief Print message.
 * 
 * @param message 
 */
inline void apf::log::warn(std::string message) {
    custom("warn", message, log_level::warn, {255, 255, 0});
}

/**
 * @brief Print message.
 * 
 * @param message 
 */
inline void apf::log::info(std::string message) {
    custom("info", message, log_level::info);
}

/**
 * @brief Print message.
 * 
 * @param message 
 */
inline void apf::log::note(std::string message) {
    custom("note", message, log_level::max);
}


/**
 * @brief Print message with custom label, colors and logging level.
 * 
 * @param log_label 
 * @param message 
 * @param lvl 
 * @param label_color 
 * @param label_back_color 
 */
inline void apf::log::custom(std::string log_label, std::string message, log_level lvl, rgb label_color, rgb label_back_color) {
    if(get_level() < lvl) {
        return;
    }

    apf::term::color(label_color);

    if (label_back_color.red != 0 || label_back_color.green != 0 || label_back_color.blue != 0) {
        apf::term::back_color(label_back_color);
    }

    if(message[message.size()-1] != '.') {
        message.append(".");
    }


    std::printf("[%s] %s", log_label.c_str(), message.c_str());
    apf::term::reset();
    std::printf("\n");
}


/**
 * @brief Set logging level.
 * 
 * @param lvl 
 */
inline void apf::log::set_level(log_level lvl) {
    get().level = lvl;
}


/**
 * @brief Get loggin level.
 * 
 * @return apf::log_level 
 */
inline apf::log_level apf::log::get_level() {
    return get().level;
}