#pragma once
#include "common.hpp"
#include "logs.hpp"



namespace apf::file {
    // Simple functions for safe text file reading and writing.
    // On error reports error and calls abort();
    inline std::string_view read(std::filesystem::path file_path);
    inline void write(std::filesystem::path file_path,  std::string_view text);
}



inline std::string_view apf::file::read(std::filesystem::path file_path) {
    file_path = std::filesystem::absolute(file_path).make_preferred();

    if(!std::filesystem::exists(file_path)) {
        apf::log::fatal("Specified file or directory dosent exist: \"" + file_path.string() + "\".");
        abort();
    }

    if(!std::filesystem::is_regular_file(file_path)) {
        apf::log::fatal("Specified path is not a file: \"" + file_path.string() + "\".");
        abort();
    }


    std::ifstream file(file_path);
    if(file.is_open()) {
        std::stringstream ss;
        ss << file.rdbuf();
        if(!file.good()) {
            apf::log::fatal("Failed read specified file: \"" + file_path.string() + "\", (file corrupted?).");
            abort();
        }
        return ss.str();
    } else {
        apf::log::fatal("Failed to open and/or read specified file: \"" + file_path.string() + "\", (file corrupted?).");
        abort();
    }
}


inline void apf::file::write(std::filesystem::path file_path,  std::string_view text) {
    file_path = std::filesystem::absolute(file_path).make_preferred();

    if(!std::filesystem::exists(file_path)) {
        apf::log::fatal("Specified file or directory dosent exist: \"" + file_path.string() + "\".");
        abort();
    }

    if(!std::filesystem::is_regular_file(file_path)) {
        apf::log::fatal("Specified path is not a file: \"" + file_path.string() + "\".");
        abort();
    }


    std::ofstream file(file_path);
    if(file.is_open()) {
        file << text;
        if(!file.good()) {
            apf::log::fatal("Failed write to specified file: \"" + file_path.string() + "\", (file corrupted?).");
            abort();
        }
        return;
    } else {
        apf::log::fatal("Failed to open and/or write to specified file: \"" + file_path.string() + "\", (file corrupted?).");
        abort();
    }
}