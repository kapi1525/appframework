#include "appframework.hpp"

using namespace std::chrono_literals;



class test_args : public app {
public:
    test_args(::args args) {
        std::ofstream file("test_ini.ini");

        
        files::lock lock("test_ini.ini", true, logs::loglevel::info);
        if(lock.error != files::lock::lock_error::none) {
            exit(-1);
        }

        assert(file.good());

        file << "global_item_string_1 = this-is-string\n";
        file << "global_item_string_2 = t  hi  s-i s-st  ring\n";
        file << "\"global item string 3\" = \"this is string\"\n";
        file << "'global item string 4' = 'this is string'\n";
        file << "\n";
        file << "global_item_value_1 = 69420   # comment\n";
        file << "global_item_value_2 = 69  42  0   # comment\n";
        file << "\n";
        file << "global_item_string_with_comment_1 = \"#comment\"\n";
        file << "global_item_string_with_comment_2 = \";comment\"\n";
        file << "global_item_string_with_comment_3 = '#comment'\n";
        file << "global_item_string_with_comment_4 = ';comment'\n";
        file << "\n";
        file << "[group]\n";
        file << "item = abc   \n";
        file << "; item_string = this-is-string\n";
        file << "# item_value = 123\n";
        file << "\n";
        file << "[group with spaces]\n";
        file << "it  em = ab c \n";
        file << "\n";
        file << "[\"group with spaces and quotes\"]\n";
        file << "item = abc\n";
        file << "\n";
        file << "['group with spaces and single quotes']\n";
        file << "item = abc\n";
        file << "\n";
        file << "# [commented group with spaces]\n";
        file << "; item = abc\n";

        //std::cin.get();

        assert(file.good());
        file.flush();

        ini ini_file("test_ini.ini", logs::loglevel::info);

        for (size_t group_i = 0; group_i < ini_file.data.size(); group_i++) {
            std::cout << "group: " << ini_file.data[group_i].first << "\n";

            for (size_t item_i = 0; item_i < ini_file.data[group_i].second.size(); item_i++) {
                std::cout << "  item: " << ini_file.data[group_i].second[item_i].first << " = " << ini_file.data[group_i].second[item_i].second << "\n";
            }
        }
        
        assert(ini_file.get_item("global_item_string_1") == "this-is-string");
        assert(ini_file.get_item("global_item_string_2") == "this-is-string");
        assert(ini_file.get_item("global item string 3") == "this is string");
        assert(ini_file.get_item("global item string 4") == "this is string");

        assert(std::stoi(ini_file.get_item("global_item_value_1")) == 69420);
        assert(std::stoi(ini_file.get_item("global_item_value_2")) == 69420);

        assert(ini_file.get_item("global_item_string_with_comment_1") == "#comment");
        assert(ini_file.get_item("global_item_string_with_comment_2") == ";comment");
        assert(ini_file.get_item("global_item_string_with_comment_3") == "#comment");
        assert(ini_file.get_item("global_item_string_with_comment_4") == ";comment");
        

        assert(ini_file.get_item_group("group", "item") == "abc");
        assert(ini_file.get_item_group("group", "item_string") == "");
        assert(ini_file.get_item_group("group", "item_value") == "");
        
        assert(ini_file.get_item_group("group with spaces", "item") == "abc");
        assert(ini_file.get_item_group("group with spaces and quotes", "item") == "abc");
        assert(ini_file.get_item_group("group with spaces and single quotes", "item") == "abc");

        assert(ini_file.get_item_group("commented group with spaces", "item") == "");
    }

    void run() {
    }

    ~test_args() {
    }
};


int main(int argc, char const *argv[]) {
    run_app(new test_args(args(argc, argv)));
    return 0;
}
