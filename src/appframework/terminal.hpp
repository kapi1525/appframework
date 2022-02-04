#pragma once
// appframework_terminal.hpp
// This header contains declarations for terminal and loggin functions.
// Terminal functions are inline so their definitions are at the bottom of this file.

#include "common.hpp"
#include "types.hpp"



namespace terminal {
    // Note: Some terminals may not support some of thiese:
    namespace cursor {
        inline u_vec2_t get_pos();

        inline void set_pos(u_vec2_t pos);
        inline void go_home();  // Home aka {0, 0}
        inline void go_up(size_t cells);
        inline void go_down(size_t cells);
        inline void go_right(size_t cells);
        inline void go_left(size_t cells);

        inline void go_line_begin_up(size_t cells);     // moves cursor to beginning of previous line, # lines up
        inline void go_line_begin_down(size_t cells);   // moves cursor to beginning of next line, # lines down
        inline void go_to_column(size_t column);        // moves cursor to column #

        inline void save();
        inline void restore();
    }

    inline void erase();                        // erase entire screen
    inline void erase_start_cursor();           // erase from cursor to beginning of screen
    inline void erase_cursor_end();             // erase from cursor until end of screen
    inline void erase_line_start_cursor();      // erase start of line to the cursor
    inline void erase_cursor_to_line_end();     // erase from cursor to end of line
    inline void erase_line();                   // erase the entire line

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
        none,
        fatal,      // Fatal error that program cant recover from.
        error,
        warn,
        info
    };

    loglevel loging_level = loglevel::info;

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

    std::vector<std::string_view> data;
    
    bool has(std::string_view arg);
    std::string_view get(std::string_view arg);
};




/////////////////////////////
// Definitions for inline terminal functions
/////////////////////////////

/////////////////////////////
// Cursor control
/////////////////////////////

// TODO: terminal::cursor::get_pos()
inline u_vec2_t terminal::cursor::get_pos() {
    return {0,0};
}


inline void terminal::cursor::go_home(){
    std::cout << "\x1B[H";
}

inline void terminal::cursor::set_pos(u_vec2_t pos){
    std::cout << "\x1B[" << pos.y << ";" << pos.x << "f";
}

inline void terminal::cursor::go_up(size_t cells){
    std::cout << "\x1B[" << cells << "A";
}

inline void terminal::cursor::go_down(size_t cells){
    std::cout << "\x1B[" << cells << "B";
}

inline void terminal::cursor::go_right(size_t cells){
    std::cout << "\x1B[" << cells << "C";
}

inline void terminal::cursor::go_left(size_t cells){
    std::cout << "\x1B[" << cells << "D";
}


inline void terminal::cursor::go_line_begin_up(size_t cells) {
    std::cout << "\x1B[" << cells << "F";
}

inline void terminal::cursor::go_line_begin_down(size_t cells) {
    std::cout << "\x1B[" << cells << "E";
}

inline void terminal::cursor::go_to_column(size_t column) {
    std::cout << "\x1B[" << column << "G";
}


inline void terminal::cursor::save(){
    std::cout << "\x1B 7";
}

inline void terminal::cursor::restore(){
    std::cout << "\x1B 8";
}



/////////////////////////////
// Erase functions
/////////////////////////////

inline void terminal::erase() {
    std::cout << "\x1B[2J";
}

inline void terminal::erase_start_cursor() {
    std::cout << "\x1B[1J";
}

inline void terminal::erase_cursor_end() {
    std::cout << "\x1B[0J";
}

inline void terminal::erase_line_start_cursor() {
    std::cout << "\x1B[1K";
}

inline void terminal::erase_cursor_to_line_end() {
    std::cout << "\x1B[0K";
}

inline void terminal::erase_line() {
    std::cout << "\x1B[2K";
}



/////////////////////////////
// Text control
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