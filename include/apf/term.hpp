#pragma once
// term.hpp
// This header contains declarations for terminal and loggin functions.
// Terminal functions are inline so their definitions are at the bottom of this file.

#include <iostream>

#include "common.hpp"
#include "color.hpp"
#include "vector.hpp"



namespace apf::term {
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



/////////////////////////////
// Definitions for inline terminal functions
/////////////////////////////

/////////////////////////////
// Cursor control
/////////////////////////////

// TODO: apf::term::cursor::get_pos()
inline apf::u_vec2_t apf::term::cursor::get_pos() {
    return {0,0};
}


inline void apf::term::cursor::go_home(){
    std::cout << "\x1B[H";
}

inline void apf::term::cursor::set_pos(u_vec2_t pos){
    std::cout << "\x1B[" << pos.y << ";" << pos.x << "f";
}

inline void apf::term::cursor::go_up(size_t cells){
    std::cout << "\x1B[" << cells << "A";
}

inline void apf::term::cursor::go_down(size_t cells){
    std::cout << "\x1B[" << cells << "B";
}

inline void apf::term::cursor::go_right(size_t cells){
    std::cout << "\x1B[" << cells << "C";
}

inline void apf::term::cursor::go_left(size_t cells){
    std::cout << "\x1B[" << cells << "D";
}


inline void apf::term::cursor::go_line_begin_up(size_t cells) {
    std::cout << "\x1B[" << cells << "F";
}

inline void apf::term::cursor::go_line_begin_down(size_t cells) {
    std::cout << "\x1B[" << cells << "E";
}

inline void apf::term::cursor::go_to_column(size_t column) {
    std::cout << "\x1B[" << column << "G";
}


inline void apf::term::cursor::save(){
    std::cout << "\x1B 7";
}

inline void apf::term::cursor::restore(){
    std::cout << "\x1B 8";
}



/////////////////////////////
// Erase functions
/////////////////////////////

inline void apf::term::erase() {
    std::cout << "\x1B[2J";
}

inline void apf::term::erase_start_cursor() {
    std::cout << "\x1B[1J";
}

inline void apf::term::erase_cursor_end() {
    std::cout << "\x1B[0J";
}

inline void apf::term::erase_line_start_cursor() {
    std::cout << "\x1B[1K";
}

inline void apf::term::erase_cursor_to_line_end() {
    std::cout << "\x1B[0K";
}

inline void apf::term::erase_line() {
    std::cout << "\x1B[2K";
}



/////////////////////////////
// Text control
/////////////////////////////

inline void apf::term::bold() {
    std::cout << "\x1B[1m";
}

inline void apf::term::faint() {
    std::cout << "\x1B[2m";
}

inline void apf::term::italic() {
    std::cout << "\x1B[3m";
}

inline void apf::term::underline() {
    std::cout << "\x1B[4m";
}

inline void apf::term::blinking() {
    std::cout << "\x1B[5m";
}

inline void apf::term::inverse() {
    std::cout << "\x1B[7m";
}

inline void apf::term::invisible() {
    std::cout << "\x1B[8m";
}

inline void apf::term::strikethrough() {
    std::cout << "\x1B[9m";
}



/////////////////////////////
// Reseting terminal stuff
/////////////////////////////

inline void apf::term::no_bold() {
    std::cout << "\x1B[22m";
}

inline void apf::term::no_faint() {
    std::cout << "\x1B[23m";
}

inline void apf::term::no_italic() {
    std::cout << "\x1B[24m";
}

inline void apf::term::no_underline() {
    std::cout << "\x1B[25m";
}

inline void apf::term::no_blinking() {
    std::cout << "\x1B[26m";
}

inline void apf::term::no_inverse() {
    std::cout << "\x1B[27m";
}

inline void apf::term::no_invisible() {
    std::cout << "\x1B[28m";
}

inline void apf::term::no_strikethrough() {
    std::cout << "\x1B[29m";
}


inline void apf::term::reset() {
    std::cout << "\x1B[0m";
}



/////////////////////////////
// Colors
/////////////////////////////

inline void apf::term::color(rgb color) {
    std::printf("\x1B[38;2;%hhu;%hhu;%hhum", color.red, color.green, color.blue);
}

inline void apf::term::back_color(rgb color) {
    std::printf("\x1B[48;2;%hhu;%hhu;%hhum", color.red, color.green, color.blue);
}


inline void apf::term::default_color() {
    std::printf("\x1B[39m");
}

inline void apf::term::default_back_color() {
    std::printf("\x1B[49m");
}