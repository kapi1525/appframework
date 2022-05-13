#pragma once
// This header contains includes used by rest of appframework



// Standard C++ stuff
#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <string>
#include <string_view>
#include <vector>
#include <thread>
#include <chrono>

// Standard C stuff
#include <cassert>



// Platform specific macros that are little bit easier to remember
#ifdef _WIN32
    #define APF_WINDOWS
#endif

#if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
    #define APF_POSIX
#endif

#ifdef __linux__
    #define APF_LINUX
#endif

#ifdef __APPLE__
    #define APF_MAC
#endif


// Compiler macros that are also easier to remember
#ifdef _MSC_VER
    #define APF_MSVC
#endif

#ifdef __GNUC__
    #define APF_GCC
#endif

#ifdef __clang__
    #define APF_CLANG
#endif



// windows stuff
#ifdef APF_WINDOWS
    #define WIN32_LEAN_AND_MEAN
    #include <windows.h>

    #ifdef _MSC_VER
        #include <BaseTsd.h>        // for SSIZE_T
        using ssize_t = SSIZE_T;    // For convenience
    #endif // _MSC_VER

#endif // APF_WINDOWS



// posix stuff
#ifdef APF_POSIX
#endif // APF_POSIX


// linux stuff
#ifdef APF_LINUX
#endif // APF_LINUX


// mac stuff
#ifdef APF_MAC
#endif // APF_MAC



/////////////////////////////
// Common types
/////////////////////////////



/**
 * @brief Holds version information. Can be converted to string.
 */
struct version {
    uint16_t major;
    uint16_t minor;
    uint16_t patch;

    std::string temp = std::string("v" + std::to_string(major) + "." + std::to_string(minor) + "." + std::to_string(patch));

    operator const char*() {
        return temp.c_str();
    }
};



/**
 * @brief Holds rgb colors in uint8_t, since uint8_t is unsigned char use static_cast<int>() while printing to not get garbage.
 */
struct rgb {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
};



/**
 * @brief Holds rgb colors and alpha in uint8_t, since uint8_t is unsigned char use static_cast<int>() while printing to not get garbage.
 */
struct rgba {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
    uint8_t alpha;
};



// Vector templates
template<typename type = float>
struct vector2 {
    type x, y;
};

template<typename type = float>
struct vector3 {
    type x, y, z;
};

template<typename type = float>
struct vector4 {
    type x, y, z, w;
};



// vector types
template<typename type = float> using vec2_t = vector2<type>;
template<typename type = float> using vec3_t = vector3<type>;
template<typename type = float> using vec4_t = vector4<type>;


using f_vec2_t = vector2<float>;
using f_vec3_t = vector3<float>;
using f_vec4_t = vector4<float>;

using d_vec2_t = vector2<double>;
using d_vec3_t = vector3<double>;
using d_vec4_t = vector4<double>;


using i_vec2_t = vector2<int>;
using i_vec3_t = vector3<int>;
using i_vec4_t = vector4<int>;

using im_vec2_t = vector2<intmax_t>;
using im_vec3_t = vector3<intmax_t>;
using im_vec4_t = vector4<intmax_t>;

using iz_vec2_t = vector2<ssize_t>;
using iz_vec3_t = vector3<ssize_t>;
using iz_vec4_t = vector4<ssize_t>;


using u_vec2_t = vector2<unsigned int>;
using u_vec3_t = vector3<unsigned int>;
using u_vec4_t = vector4<unsigned int>;

using um_vec2_t = vector2<uintmax_t>;
using um_vec3_t = vector3<uintmax_t>;
using um_vec4_t = vector4<uintmax_t>;

using uz_vec2_t = vector2<size_t>;
using uz_vec3_t = vector3<size_t>;
using uz_vec4_t = vector4<size_t>;


/////////////////////////////
// Common functions
/////////////////////////////

// Nothing ;)