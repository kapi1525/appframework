#include "apf/all.hpp"
#include <thread>
#include <chrono>

using namespace std::chrono_literals;



class sandbox : public apf::app {
public:
    void start() {
        apf::log::note("test");
        apf::log::info("test");
        apf::log::warn("test");
        apf::log::error("test");
        apf::log::fatal("test");
        std::cout << "end" << std::endl;
    }

    int run() {
        return 1;
    }

    void end() {
        apf::term::reset();
        std::cout << "\n";
    }


private:
    version sandbox_version = {1,2,3};
};



APF_MAIN(sandbox)