#pragma once
#include <string>
#include <cstdint>


namespace apf {

    /**
     * @brief Holds version information. Can be converted to string.
     */
    struct version {
        uint16_t major;
        uint16_t minor;
        uint16_t patch;

        std::string temp = std::string("v" + std::to_string(major) + "." + std::to_string(minor) + "." + std::to_string(patch));

        // TODO: Get rid of this
        operator const char*() {
            return temp.c_str();
        }
    };
    
}