#include "appframework_ini.hpp"



// Im using this to reduce number of allocations
#if 0
size_t alloc_count = 0;
size_t alloc_size = 0;
void* operator new(size_t size) {
    alloc_count++;
    alloc_size = alloc_size+size;
    std::cout << "Allocating: " << size << " bytes...  Total memory allocated: " << alloc_size <<" bytes.  Total allocations: " << alloc_count << "\n";
    return malloc(size);
}
#endif

ini::ini() {
}

ini::ini(std::filesystem::path file_path, logs::loglevel log_level) {
    log.loging_level = log_level;
    parse(file_path);
}

ini::~ini() {
}


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
            std::cout << "line: " << line << "\n";
            
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
    }
    
    return true;
}

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
    }

    if(!file.good()) {
        log.error("file.good() returned false.");
        return false;
    }

    file.close();
    
    return true;
}


bool ini::has_whitespace(std::string text) {
    for (size_t i = 0; i < text.size(); i++) {
        if(std::isspace(text[i])) {
            return true;
        }
    }
    return false;
}


std::string ini::remove_whitespace(std::string line) {
    // Its probably not the best implementation but it will run only once when parsing ini so it dosent matter
    std::string temp;
    bool quote = false;
    for (size_t i = 0; i < line.size(); i++) {
        if(line[i] == '"' || line[i] == '\'') { quote = !quote; }
        if(!std::isspace(line[i]) || quote == true) { temp.push_back(line[i]); }
    }
    return temp;
}

std::string ini::remove_comments(std::string line) {
    // Standard ini uses ';' for comments but often '#' is also used so remove both unless in quotes
    int comment_start = line.size();
    bool quote = false;
    for (size_t i = 0; i < line.size(); i++) {
        if(line[i] == '"' || line[i] == '\'') { quote = !quote; }
        if((line[i] == ';' || line[i] == '#') && quote == false) {
            comment_start = i;
            break;
        }
    }
    return line.substr(0, comment_start);
}


ini::ini_item_t ini::try_parse_item(std::string line) {
    for (size_t i = 0; i < line.size(); i++) {
        if(line[i]=='=' && i>0 && i<line.size()-1) {
            return {try_remove_quotes(line.substr(0, i)), try_remove_quotes(line.substr(i+1, line.size()-i))};
        }
    }
    return {"", ""};    // returns {"", ""} if failed to parse
}

std::string ini::try_parse_group(std::string line) {
    for (size_t i = 0; i < line.size(); i++) {
        if(line[0]=='[' && line[line.size()-1]==']') {
            return try_remove_quotes(line.substr(1, line.size()-2));
        }
    }
    return "";
}


std::string ini::try_remove_quotes(std::string line) {
    if(line[0] == '"' && line[line.size()-1] == '"') {
        return line.substr(1, line.size()-2);
    }
    return line;
}


bool ini::is_item(std::string line) {
    for (size_t i = 0; i < line.size(); i++) {
        if(line[i]=='=' && i>0 && i<line.size()-1) {
            return true;
        }
    }
    return false;
}

bool ini::is_group(std::string line) {
    if(line[0] == '[' && line[line.size()-1] == ']') {
        return true;
    }
    return false;
}


std::string ini::get_item(std::string item) {
    return get_item_group("", item);
}

std::string ini::get_item_group(std::string group, std::string item) {
    size_t group_index = 0;
    for (size_t i = 0; i < data.size(); i++) {
        if(data[i].first==group) {
            group_index = i;
        } else if(i == data.size()-1) {
            log.warn("No such group exists: "+group);
            return "";
        }
    }
    
    for (size_t i = 0; i < data[group_index].second.size(); i++) {
        if(data[group_index].second[i].first == item) {
            return data[group_index].second[i].second;
        }
    }
            
    log.warn("No such item exists: "+item);
    return "";
}


void ini::set_item(std::string item, std::string value) {
    set_item_group("", item, value);
}

void ini::set_item_group(std::string group, std::string_view item, std::string value) {
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

    data.push_back({group, std::vector<ini_item_t>()});
    data[data.size()-1].second.push_back(ini_item_t{item, value});
}
