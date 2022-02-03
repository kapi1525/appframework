#pragma once
#include "appframework_common.hpp"



// Simple .ini parser
// TODO: Add better support for comments ";" and "#"
// TODO: Add support for sub groups/sections
// TODO: Trim whitespaces in groups, names and values
// TODO: Remove "" from values and names
class ini {
public:
    ini();
    ini(std::filesystem::path file_path);
    ~ini();


    struct ini_item {
        std::string group, name, value;
    };


    std::vector<ini_item> data;
    

    std::string get_item(std::string item);
    std::string get_item_group(std::string group, std::string item);
};