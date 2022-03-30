#include "appframework.hpp"
#include "apf/logs.hpp"
#include "apf/file.hpp"


class test : public apf::app {
public:
    void start() {
        std::filesystem::path path = "test_file";
        std::string str = "Hello World!";

        apf::file::write(path, str);
        assert(apf::file::read(path) == str);
    }

    void run() {
    }

    void end() {
    }
};



APF_TEST_MAIN(test)