#include "apf/all.hpp"
#include <thread>
#include <chrono>

using namespace std::chrono_literals;



class sandbox : public apf::app {
public:
    void start() {
        apf::process p("./test.sh");
        std::cout << "exit code: " << p.join() << "\n";
        std::cout << p.get() << "\n";
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