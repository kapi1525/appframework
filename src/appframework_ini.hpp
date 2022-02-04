#pragma once
#include "appframework_common.hpp"
#include "appframework_terminal.hpp"    // For logging



// Simple .ini parser
class ini {
public:
    ini();
    ini(std::filesystem::path file_path, logs::loglevel log_level = logs::loglevel::error);
    ~ini();


    typedef std::pair<std::string, std::string> ini_item_t;
    typedef std::pair<std::string, std::vector<ini_item_t>> ini_group_t;


    std::vector<ini_group_t> data;


    bool parse(std::filesystem::path file_path);        // Loads ini from file and parses it
    // TODO: Make ini::save() and ini::parse() not override all comments
    bool save(std::filesystem::path file_path);         // Saves ini to file (currently saving ini removes all comments)

    bool has_whitespace(std::string text);              // True if has whitespace
    std::string remove_whitespace(std::string line);    // Removes whitespaces at start and end
    std::string remove_comments(std::string line);      // Removes comments

    ini_item_t try_parse_item(std::string line);        // If passed line is item returns ini_item_t
    std::string try_parse_group(std::string line);      // If passed line is group returns group name
    std::string try_remove_quotes(std::string line);    // If string has quotes at start and end removes them else returns string unmodified

    bool is_item(std::string line);                     // True if passed string is item declaration in ini format
    bool is_group(std::string line);                    // True if passed string is group declaration in ini format

    std::string get_item(std::string item);             // Gets item value from global group
    std::string get_item_group(std::string group, std::string item);

    void set_item(std::string item, std::string value); // Sets item value in global group
    void set_item_group(std::string group, std::string_view item, std::string value);

    logs log;
};