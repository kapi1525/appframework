#include "apf/all.hpp"
#include <thread>
#include <chrono>

using namespace std::chrono_literals;



class sandbox : public apf::app {
public:
    void start() {
        apf::log::set_level(apf::log_level::error);
        apf::log::fatal("fghjkghj");
        apf::log::error("fdgjghjk");
        apf::log::warn("fdgjghjk");
        apf::log::info("fdgjghjk");
        apf::log::note("fdgjghjk");
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