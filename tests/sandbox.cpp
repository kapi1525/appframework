#include "apf/all.hpp"
#include <thread>
#include <chrono>

using namespace std::chrono_literals;



class sandbox : public apf::app {
public:
    void start() {
        apf::log::fatal("test");
        apf::log::error("test");
        apf::log::warn("test");
    }

    int run() {
        return 1;
    }

    void end() {
        apf::term::reset();
        std::cout << "\n";
    }


private:
    apf::version sandbox_version = {1,2,3};
};



APF_MAIN(sandbox)