#pragma once


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
template<typename _T>
struct vector2 {
    _T x;
    _T y;
};

template<typename _T>
struct vector3 {
    _T x;
    _T y;
    _T z;
};

template<typename _T>
struct vector4 {
    _T x;
    _T y;
    _T z;
    _T w;
};


// vector types
typedef vector2<float> vec2_t;
typedef vector3<float> vec3_t;
typedef vector4<float> vec4_t;

typedef vector2<double> d_vec2_t;
typedef vector3<double> d_vec3_t;
typedef vector4<double> d_vec4_t;

typedef vector2<size_t> u_vec2_t;
typedef vector3<size_t> u_vec3_t;
typedef vector4<size_t> u_vec4_t;

#ifdef _MSC_VER
    // ssize_t is non standard and it isnt defined if using MSVC
    typedef SSIZE_T ssize_t;
#endif

typedef vector2<ssize_t> i_vec2_t;
typedef vector3<ssize_t> i_vec3_t;
typedef vector4<ssize_t> i_vec4_t;