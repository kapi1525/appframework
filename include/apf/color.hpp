#pragma once
#include <cstdint>


namespace apf {

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


    namespace color {

        static rgb black    = {  0,   0,   0};
        static rgb white    = {255, 255, 255};

        static rgb red      = {255,   0,   0};
        static rgb green    = {  0, 255,   0};
        static rgb blue     = {  0,   0, 255};
        static rgb yellow   = {255, 255,   0};
    }

}