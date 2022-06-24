#pragma once
#include <cstdint>
#include <cstddef>



namespace apf {

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


    using u_vec2_t = vector2<unsigned int>;
    using u_vec3_t = vector3<unsigned int>;
    using u_vec4_t = vector4<unsigned int>;

    using um_vec2_t = vector2<uintmax_t>;
    using um_vec3_t = vector3<uintmax_t>;
    using um_vec4_t = vector4<uintmax_t>;

}