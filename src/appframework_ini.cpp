#include "appframework_ini.hpp"



ini::ini() {
}

ini::ini(std::filesystem::path file_path) {
    std::string current_group = "";
    std::ifstream file(file_path);

    assert(file.good() == true);

    for (std::string line; std::getline(file, line); ) {
        if (line[0] != ';' && line[0] != '#') {
            // Check if group
            size_t group_start = 0;
            size_t group_end = 0;

            for (size_t i = 0; i < line.size(); i++) {
                if (line[i] == '[') {
                    group_start = i+1;
                }
                if (line[i] == ']') {
                    group_end = i;
                }
            }
            
            if (group_start < group_end) {
                current_group = line.substr(group_start, group_end-group_start);
                //std::cout << "current_group = " << current_group << "\n";
            }
            

            // Chech if item
            size_t item_name_start = 0;
            size_t item_name_end = 0;
            size_t item_value_start = 0;
            size_t item_value_end = 0;

            for (size_t i = 0; i < line.size(); i++) {
                if (line[i] == '=') {
                    item_name_end = i;
                    item_value_start = i+1;
                    item_value_end = line.size();

                    data.push_back({
                        current_group,
                        line.substr(item_name_start, item_name_end-item_name_start),
                        line.substr(item_value_start, item_value_end-item_value_start)
                    });
                    //std::cout << "[" << current_group << "] " << line.substr(item_name_start, item_name_end-item_name_start) << "=" << line.substr(item_value_start, item_value_end-item_value_start) << "\n";
                    break;
                }
            }
        }
    }
}

ini::~ini() {
}


std::string ini::get_item(std::string item) {
    for (size_t i = 0; i < data.size(); i++) {
        if (data[i].group == "" && data[i].name == item) {
            return data[i].value;
        }
    }
    return "";
}

std::string ini::get_item_group(std::string group, std::string item) {
    for (size_t i = 0; i < data.size(); i++) {
        if (data[i].group == group && data[i].name == item) {
            return data[i].value;
        }
    }
    return "";
}
