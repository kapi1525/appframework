#pragma once
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
        static void fatal(std::string_view message);
        static void error(std::string_view message);
        static void warn(std::string_view message);
        static void info(std::string_view message);
        static void note(std::string_view message);

        static void custom(std::string_view log_label, std::string_view message, log_level lvl = log_level::max, apf::rgb label_color = {255, 255, 255}, apf::rgb label_back_color = {0, 0, 0});

        static void set_level(log_level lvl);
        static log_level get_level();

    private:
        log() = default;
        
        static log& get();

        log_level level = log_level::max;
    };
}
