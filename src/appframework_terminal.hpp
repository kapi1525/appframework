#pragma once
// appframework_terminal.hpp
// This header contains declarations for terminal and loggin functions.
// Terminal functions are inline so their definitions are at the bottom of this file.

#include "appframework_common.hpp"



// RGB colors
struct rgb {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
};


namespace terminal {
    // Note: Some terminals may not support some of thiese:
    // TODO: Add functions to control terminal cursor using ANSI escape codes.
    inline void bold();
    inline void faint();
    inline void italic();
    inline void underline();
    inline void blinking();
    inline void inverse();          // Repleaces Foreground(color) and background(back_color) colors together
    inline void invisible();
    inline void strikethrough();

    inline void no_bold();          // Resets both bold and faint
    inline void no_faint();         // Resets both bold and faint
    inline void no_italic();
    inline void no_underline();
    inline void no_blinking();
    inline void no_inverse();
    inline void no_invisible();
    inline void no_strikethrough();

    // Set terminal output colors using ANSI escape codes
    inline void color(rgb color);
    inline void back_color(rgb color);
    inline void default_color();
    inline void default_back_color();

    // Resets everything
    inline void reset();
}


class logs {
public:
    logs();
    ~logs();

    enum class loglevel {
        fatal,      // Fatal error that program cant recover from.
        error,
        warn,
        info
    };

    loglevel logging_level = loglevel::info;

    void fatal(std::string_view message);
    void error(std::string_view message);
    void  warn(std::string_view message);
    void  info(std::string_view message);
};


class args {
public:
    args();
    args(int argc, char const *argv[]);
    ~args();

    std::vector<std::string> data;
    
    bool has(std::string_view arg);
    std::string_view get(std::string_view arg);
};



/////////////////////////////
// Definitions for inline terminal functions
/////////////////////////////

inline void terminal::bold() {
    std::cout << "\x1B[1m";
}

inline void terminal::faint() {
    std::cout << "\x1B[2m";
}

inline void terminal::italic() {
    std::cout << "\x1B[3m";
}

inline void terminal::underline() {
    std::cout << "\x1B[4m";
}

inline void terminal::blinking() {
    std::cout << "\x1B[5m";
}

inline void terminal::inverse() {
    std::cout << "\x1B[7m";
}

inline void terminal::invisible() {
    std::cout << "\x1B[8m";
}

inline void terminal::strikethrough() {
    std::cout << "\x1B[9m";
}



/////////////////////////////
// Reseting terminal stuff
/////////////////////////////

inline void terminal::no_bold() {
    std::cout << "\x1B[22m";
}

inline void terminal::no_faint() {
    std::cout << "\x1B[23m";
}

inline void terminal::no_italic() {
    std::cout << "\x1B[24m";
}

inline void terminal::no_underline() {
    std::cout << "\x1B[25m";
}

inline void terminal::no_blinking() {
    std::cout << "\x1B[26m";
}

inline void terminal::no_inverse() {
    std::cout << "\x1B[27m";
}

inline void terminal::no_invisible() {
    std::cout << "\x1B[28m";
}

inline void terminal::no_strikethrough() {
    std::cout << "\x1B[29m";
}


inline void terminal::reset() {
    std::cout << "\x1B[0m";
}



/////////////////////////////
// Colors
/////////////////////////////

inline void terminal::color(rgb color) {
    std::cout << "\x1B[38;2;" << static_cast<int>(color.red) << ";" << static_cast<int>(color.green) << ";" << static_cast<int>(color.blue) << "m";
}

inline void terminal::back_color(rgb color) {
    std::cout << "\x1B[48;2;" << static_cast<int>(color.red) << ";" << static_cast<int>(color.green) << ";" << static_cast<int>(color.blue) << "m";
}


inline void terminal::default_color() {
    std::cout << "\x1B[39m";
}

inline void terminal::default_back_color() {
    std::cout << "\x1B[49m";
}