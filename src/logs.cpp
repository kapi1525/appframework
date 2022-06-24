#include "apf/logs.hpp"



apf::log& apf::log::get() {
    static apf::log instance;
    return instance;
}


/**
 * @brief Print message.
 * 
 * @param message 
 */
void apf::log::fatal(std::string_view message) {
    custom("fatal", message, log_level::fatal, apf::color::black, apf::color::red);
}

/**
 * @brief Print message.
 * 
 * @param message 
 */
void apf::log::error(std::string_view message) {
    custom("error", message, log_level::error, apf::color::red);
}

/**
 * @brief Print message.
 * 
 * @param message 
 */
void apf::log::warn(std::string_view message) {
    custom("warn", message, log_level::warn, apf::color::yellow);
}

/**
 * @brief Print message.
 * 
 * @param message 
 */
void apf::log::info(std::string_view message) {
    custom("info", message, log_level::info);
}

/**
 * @brief Print message.
 * 
 * @param message 
 */
void apf::log::note(std::string_view message) {
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
void apf::log::custom(std::string_view log_label, std::string_view message, log_level lvl, rgb label_color, rgb label_back_color) {
    if(get_level() < lvl) {
        return;
    }

    apf::term::color(label_color);

    if(label_back_color.red != 0 || label_back_color.green != 0 || label_back_color.blue != 0) {
        apf::term::back_color(label_back_color);
    }

    if(message[message.size()-1] != '.') {
        std::printf("[%s] %s.", log_label.data(), message.data());
    } else {
        std::printf("[%s] %s", log_label.data(), message.data());
    }

    apf::term::reset();
    std::printf("\n");
}


/**
 * @brief Set logging level.
 * 
 * @param lvl 
 */
void apf::log::set_level(log_level lvl) {
    get().level = lvl;
}


/**
 * @brief Get loggin level.
 * 
 * @return apf::log_level 
 */
apf::log_level apf::log::get_level() {
    return get().level;
}