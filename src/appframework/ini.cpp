#include "ini.hpp"




/**
 * @brief Creates new ini object with optional log level.
 * 
 * @param log_level What errors should be printed (loglevel::fatal by default)
 */
ini::ini(logs::loglevel log_level) {
    log.loging_level = log_level;
}



/**
 * @brief Create ini object and parse specified file.
 * 
 * @param file_path Path to file.
 * @param log_level What errors should be printed (loglevel::fatal by default)
 */
ini::ini(std::filesystem::path file_path, logs::loglevel log_level) {
    log.loging_level = log_level;
    bool return_value = false;
    for (size_t i = 0; i < 10; i++) {
        return_value = parse(file_path);
        if(return_value) {
            return;
        } else {
            //std::this_thread::sleep_for(500ms);
        }
    }
}



/**
 * @brief Destroy the ini object
 */
ini::~ini() {}



/**
 * @brief Parses ini file.
 * 
 * @param file_path Path to file which uses ini format.
 * @return true or false, true if successfuly parsed file, false if failed to open file (Create ini with loglevel::info for better debugging).
 */
bool ini::parse(std::filesystem::path file_path) {
    std::ifstream file(file_path);

    if(!file.good()) {
        log.error("file.good() returned false.");
        //std::abort(); ABORT!!!!!!!!
        return false;
    }

    std::string current_group("");  // Global items are internaly in "" group
    data.clear();
    data.push_back({ current_group, std::vector<ini_item_t>()});    // Add global group

    for (std::string line; std::getline(file, line);) {
        line = remove_whitespace(line);
        line = remove_comments(line);
        
        if(line != "") {            
            if(is_item(line)) {
                for (size_t i = 0; i < data.size(); i++) {
                    if(data[i].first == current_group) {
                        data[data.size()-1].second.push_back(try_parse_item(line));
                        break;
                    }
                    else if(i == data.size()-1) {
                        log.fatal("Failed to find current_group, something went very wrong this should't be possible.");
                        log.fatal("Calling abort().");
                        std::abort(); // 101% sure its should't be possible to get here so ABORT!!!!!!!!
                    }
                }
            } else if(is_group(line)) {
                current_group = try_parse_group(line);

                for (size_t i = 0; i < data.size(); i++) {
                    if(data[i].first == current_group) {
                        break;
                    }
                    else if(i == data.size()-1) {
                        data.push_back({ current_group, std::vector<ini_item_t>()});
                    }
                }
            }
        }

        if(!file.good()) {
            log.error("file.good() returned false.");
            return false;
        }
    }

    file.close();
    
    if(!file.good()) {
        log.error("file.good() returned false.");
        return false;
    }

    return true;
}



/**
 * @brief Saves ini file to specified path.
 * @note This overrides all comments.
 * 
 * @param file_path Path to file.
 * @return true or false, true if successfuly saved file, false if failed to save file (Create ini with loglevel::info for better debugging).
 */
bool ini::save(std::filesystem::path file_path) {
    std::ofstream file(file_path);

    if(!file.good()) {
        log.error("file.good() returned false.");
        return false;
    }

    for (size_t group_i = 0; group_i < data.size(); group_i++) {
        if(data[group_i].first != "") {
            if (has_whitespace(data[group_i].first)) {
                file << "[\"" << data[group_i].first << "\"]\n";
            } else {
                file << "[" << data[group_i].first << "]\n";
            }
        }
        for (size_t item_i = 0; item_i < data[group_i].second.size(); item_i++) {
            if (has_whitespace(data[group_i].second[item_i].first)) {
                file << "\"" << data[group_i].second[item_i].first << "\"=";
            } else {
                file << data[group_i].second[item_i].first << "=";
            }
            if (has_whitespace(data[group_i].second[item_i].second)) {
                file << "\"" << data[group_i].second[item_i].second << "\"\n";
            } else {
                file << data[group_i].second[item_i].second << "\n";
            }
        }

        if(!file.good()) {
            log.error("file.good() returned false.");
            return false;
        }
    }

    if(!file.good()) {
        log.error("file.good() returned false.");
        return false;
    }

    file.close();
    
    return true;
}


bool ini::has_whitespace(std::string_view text) {
    for (size_t i = 0; i < text.size(); i++) {
        if(std::isspace(text[i])) {
            return true;
        }
    }
    return false;
}



/**
 * @brief Get value of global ini item.
 * 
 * @param item Ini item.
 * @return Item value
 */
std::string ini::get_item(std::string_view item) {
    return get_item_group("", item);
}



/**
 * @brief Get value of ini item from specified group.
 * 
 * @param group Ini group.
 * @param item Ini item.
 * @return Item value
 */
std::string ini::get_item_group(std::string_view group, std::string_view item) {
    size_t group_index = 0;
    for (size_t i = 0; i < data.size(); i++) {
        if(data[i].first.compare(group) == 0) {
            group_index = i;
            break;
        } else if(i == data.size()-1) {
            log.warn("No such group exists: "+std::string(group));
            return "";
        }
    }
    
    for (size_t i = 0; i < data[group_index].second.size(); i++) {
        if(data[group_index].second[i].first == item) {
            return data[group_index].second[i].second;
        }
    }
            
    log.warn("No such item exists: "+std::string(item));
    return "";
}



/**
 * @brief Set global ini item value.
 * 
 * @param item Ini item.
 * @param value Value.
 */
void ini::set_item(std::string_view item, std::string_view value) {
    set_item_group("", item, value);
}



/**
 * @brief Set ini item value from specified group.
 * 
 * @param group Ini group.
 * @param item Ini item.
 * @param value Value.
 */
void ini::set_item_group(std::string_view group, std::string_view item, std::string_view value) {
    for (size_t group_i = 0; group_i < data.size(); group_i++) {
        if(data[group_i].first == group) {
            for (size_t item_i = 0; item_i < data[group_i].second.size(); item_i++) {
                if (data[group_i].second[item_i].first == item) {
                    data[group_i].second[item_i].second = value;
                    return;
                }
            }
            data[group_i].second.push_back(ini_item_t{item, value});
            return;
        }
    }

    data.push_back({std::string(group), std::vector<ini_item_t>()});
    data[data.size()-1].second.push_back(ini_item_t{item, value});
}



/**
 * Functions bellow are private and are used for parsing ini.
 */

std::string ini::remove_whitespace(std::string_view line) {
    // Its probably not the best implementation but it will run only once when parsing ini so it dosent matter
    std::string temp;
    temp.reserve(line.size());
    bool quote = false;
    bool group = false;
    for (size_t i = 0; i < line.size(); i++) {
        if(line[i] == '"' || line[i] == '\'') { quote = !quote; }
        if(line[i] == '[') { group = true; }
        if(line[i] == ']') { group = false; }
        if(std::isspace(line[i]) == 0 || quote || group) { temp.push_back(line[i]); }
    }
    return temp;
}

std::string ini::remove_comments(std::string_view line) {
    // Standard ini uses ';' for comments but often '#' is also used so remove both unless in quotes
    bool quote = false;
    for (size_t i = 0; i < line.size(); i++) {
        if(line[i] == '"' || line[i] == '\'') { quote = !quote; }
        if((line[i] == ';' || line[i] == '#') && quote == false) {
            return std::string(line.substr(0, i));
        }
    }
    return std::string(line);
}


ini::ini_item_t ini::try_parse_item(std::string_view line) {
    for (size_t i = 0; i < line.size(); i++) {
        if(line[i]=='=' && i>0 && i<line.size()-1) {
            return {try_remove_quotes(line.substr(0, i)), try_remove_quotes(line.substr(i+1, line.size()-i))};
        }
    }
    return {"", ""};    // returns {"", ""} if failed to parse
}

std::string ini::try_parse_group(std::string_view line) {
    for (size_t i = 0; i < line.size(); i++) {
        if(line[0]=='[' && line[line.size()-1]==']') {
            return try_remove_quotes(line.substr(1, line.size()-2));
        }
    }
    return "";
}


std::string ini::try_remove_quotes(std::string_view line) {
    if((line[0] == '"' && line[line.size()-1] == '"') || (line[0] == '\'' && line[line.size()-1] == '\'')) {
        return std::string(line.substr(1, line.size()-2));
    }
    return std::string(line);
}


bool ini::is_item(std::string_view line) {
    for (size_t i = 0; i < line.size(); i++) {
        if(line[i]=='=' && i>0 && i<line.size()-1) {
            return true;
        }
    }
    return false;
}

bool ini::is_group(std::string_view line) {
    if(line[0] == '[' && line[line.size()-1] == ']') {
        return true;
    }
    return false;
}